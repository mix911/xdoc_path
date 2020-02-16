#include "xtiny_path.h"
#include <algorithm>
#include <queue>

namespace th { namespace xml {
    enum class estate_t
    {
        node,
        text,
        name_or_attribute,
        name,
        attr,
        parent_or_current,
        parent,
        exit,
    };

    struct State
    {
        State(estate_t state, std::string::const_iterator beg, std::string::const_iterator end, TiXmlNode* node)
            : state(state)
            , beg(beg)
            , end(end)
            , node(node)
        {
        }
        estate_t                    state;
        std::string::const_iterator beg;
        std::string::const_iterator end;
        TiXmlNode*                  node;
    };

    void request_by_xpath_impl(State s, std::vector<TiXmlBase*>& nodes)
    {
        std::queue<State> states;
        states.push(s);
        while (states.empty() == false)
        {
            s = states.front();
            states.pop();
            switch (s.state)
            {
                case estate_t::node:
                {
                    if (s.beg == s.end)
                    {
                        states.push(State(estate_t::exit, s.beg, s.end, s.node));
                        break;
                    }
                    switch (*s.beg)
                    {
                        case '/':
                        {
                            states.push(State(estate_t::name_or_attribute, s.beg + 1, s.end, s.node));
                            break;
                        }
                        default:
                        {
                            break;
                        }
                    }
                    break;
                }
                case estate_t::name_or_attribute:
                {
                    if (s.beg == s.end)
                    {
                        states.push(State(estate_t::exit, s.beg, s.end, s.node));
                        break;
                    }
                    switch (*s.beg)
                    {
                        case '@':
                        {
                            states.push(State(estate_t::attr, s.beg + 1, s.end, s.node));
                            break;
                        }
                        case '.':
                        {
                            states.push(State(estate_t::parent_or_current, s.beg + 1, s.end, s.node));
                            break;
                        }
                        default:
                        {
                            states.push(State(estate_t::name, s.beg, s.end, s.node));
                            break;
                        }
                    }
                    break;
                }
                case estate_t::name:
                {
                    auto it = std::find_if(s.beg, s.end, [](char ch)
                    {
                        return ch == '[' || ch == '/';
                    });
                    std::string name(s.beg, it);
                    if (name == "text()")
                    {
                        states.push(State(estate_t::text, it, s.end, s.node));
                        break;
                    }
                    for (auto child = s.node->FirstChild(name.c_str());
                         child != nullptr;
                         child = child->NextSibling(name.c_str()))
                    {
                        states.push(State(estate_t::node, it, s.end, child));
                    }
                    break;
                }
                case estate_t::attr:
                {
                    if (s.node->Type() != TiXmlNode::TINYXML_ELEMENT)
                    {
                        break;
                    }
                    auto it = std::find_if(s.beg, s.end, [](char ch)
                    {
                        return ch == '/';
                    });
                    std::string name(s.beg, it);
                    for (auto attr = ((TiXmlElement*)s.node)->FirstAttribute(); attr != nullptr; attr = attr->Next())
                    {
                        if (::strcmp(attr->Name(), name.c_str()) == 0)
                        {
                            nodes.push_back(attr);
                            break;
                        }
                    }
                    break;
                }
                case estate_t::parent_or_current:
                {
                    if (s.beg == s.end)
                    {
                        states.push(State(estate_t::exit, s.beg, s.end, s.node));
                        break;
                    }
                    switch (*s.beg)
                    {
                        case '.':
                        {
                            states.push(State(estate_t::parent, s.beg + 1, s.end, s.node));
                            break;
                        }
                        case '/':
                        {
                            states.push(State(estate_t::node, s.beg, s.end, s.node));
                            break;
                        }
                    }
                    break;
                }
                case estate_t::text:
                {
                    if (s.node->Type() != TiXmlNode::TINYXML_ELEMENT)
                    {
                        break;
                    }
                    for (auto child = s.node->FirstChild(); child != nullptr; child = child->NextSibling())
                    {
                        if (auto text = child->ToText())
                        {
                            nodes.push_back(text);
                        }
                    }
                    break;
                }
                case estate_t::exit:
                {
                    nodes.push_back(s.node);
                    break;
                }
                default:
                {
                    break;
                }
            }
        }
    }

    std::vector<TiXmlBase*> request_by_xpath(const std::string& xpath, TiXmlNode* node)
    {
        std::vector<TiXmlBase*> nodes;
        request_by_xpath_impl(State(estate_t::node, xpath.begin(), xpath.end(), node), nodes);
        return nodes;
    }
    std::vector<const TiXmlBase*> request_by_xpath(const std::string& xpath, const TiXmlNode* node)
    {
        std::vector<TiXmlBase*> nodes;
        request_by_xpath_impl(State(estate_t::node, xpath.begin(), xpath.end(), const_cast<TiXmlNode*>(node)), nodes);
        std::vector<const TiXmlBase*> cnodes;
        std::transform(nodes.begin(), nodes.end(), std::back_inserter(cnodes), [](TiXmlBase* base)
        {
            return const_cast<const TiXmlBase*>(base);
        });
        return cnodes;
    }
} }