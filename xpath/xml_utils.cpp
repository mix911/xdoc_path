#include "xml_utils.h"
#include <algorithm>

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

void request_by_xpath_impl(estate_t state,
                           std::string::const_iterator beg,
                           std::string::const_iterator end,
                           TiXmlNode* node,
                           std::vector<TiXmlBase*>& nodes)
{
    switch (state)
    {
        case estate_t::node:
        {
            if (beg == end)
            {
                request_by_xpath_impl(estate_t::exit, beg, end, node, nodes);
                break;
            }
            switch (*beg)
            {
                case '/':
                {
                    request_by_xpath_impl(estate_t::name_or_attribute, beg + 1, end, node, nodes);
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
            if (beg == end)
            {
                request_by_xpath_impl(estate_t::exit, beg, end, node, nodes);
                break;
            }
            switch (*beg)
            {
                case '@':
                {
                    request_by_xpath_impl(estate_t::attr, beg + 1, end, node, nodes);
                    break;
                }
                case '.':
                {
                    request_by_xpath_impl(estate_t::parent_or_current, beg + 1, end, node, nodes);
                    break;
                }
                default:
                {
                    request_by_xpath_impl(estate_t::name, beg, end, node, nodes);
                    break;
                }
            }
            break;
        }
        case estate_t::name:
        {
            auto it = std::find_if(beg, end, [](char ch)
            {
                return ch == '[' || ch == '/';
            });
            std::string name(beg, it);
            if (name == "text()")
            {
                request_by_xpath_impl(estate_t::text, it, end, node, nodes);
                break;
            }
            for (auto child = node->FirstChild(name.c_str());
                 child != nullptr;
                 child = child->NextSibling(name.c_str()))
            {
                request_by_xpath_impl(estate_t::node, it, end, child, nodes);
            }
            break;
        }
        case estate_t::attr:
        {
            if (node->Type() != TiXmlNode::TINYXML_ELEMENT)
            {
                break;
            }
            auto it = std::find_if(beg, end, [](char ch)
            {
                return ch == '/';
            });
            std::string name(beg, it);
            for (auto attr = ((TiXmlElement*)node)->FirstAttribute(); attr != nullptr; attr = attr->Next())
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
            if (beg == end)
            {
                request_by_xpath_impl(estate_t::exit, beg, end, node, nodes);
                break;
            }
            switch (*beg)
            {
                case '.':
                {
                    request_by_xpath_impl(estate_t::parent, beg + 1, end, node, nodes);
                    break;
                }
                case '/':
                {
                    request_by_xpath_impl(estate_t::node, beg, end, node, nodes);
                    break;
                }
            }
            break;
        }
        case estate_t::text:
        {
            if (node->Type() != TiXmlNode::TINYXML_ELEMENT)
            {
                break;
            }
            for (auto child = node->FirstChild(); child != nullptr; child = child->NextSibling())
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
            nodes.push_back(node);
            break;
        }
        default:
        {
            break;
        }
    }
}

std::vector<TiXmlBase*> request_by_xpath(const std::string& xpath, TiXmlNode* node)
{
    std::vector<TiXmlBase*> nodes;
    request_by_xpath_impl(estate_t::node, xpath.begin(), xpath.end(), node, nodes);
    return nodes;
}
std::vector<const TiXmlBase*> request_by_xpath(const std::string& xpath, const TiXmlNode* node)
{
    std::vector<TiXmlBase*> nodes;
    request_by_xpath_impl(estate_t::node, xpath.begin(), xpath.end(), const_cast<TiXmlNode*>(node), nodes);
    std::vector<const TiXmlBase*> cnodes;
    std::transform(nodes.begin(), nodes.end(), std::back_inserter(cnodes), [](TiXmlBase* base)
    {
        return const_cast<const TiXmlBase*>(base);
    });
    return cnodes;
}