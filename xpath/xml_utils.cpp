#include "xml_utils.h"
#include <algorithm>

enum class estate_t
{
    node,
    name_or_attribute,
    name,
    attr,
    exit,
};

void request_by_xpath_impl(estate_t state,
                           std::string::const_iterator beg,
                           std::string::const_iterator end,
                           TiXmlBase* base,
                           std::vector<TiXmlBase*>& nodes)
{
    switch (state)
    {
        case estate_t::node:
        {
            if (beg == end)
            {
                request_by_xpath_impl(estate_t::exit, beg, end, base, nodes);
                break;
            }
            switch (*beg)
            {
                case '/':
                {
                    request_by_xpath_impl(estate_t::name_or_attribute, beg + 1, end, base, nodes);
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
                request_by_xpath_impl(estate_t::exit, beg, end, base, nodes);
                break;
            }
            switch (*beg)
            {
                case '@':
                {
                    request_by_xpath_impl(estate_t::attr, beg + 1, end, base, nodes);
                    break;
                }
                default:
                {
                    request_by_xpath_impl(estate_t::name, beg, end, base, nodes);
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
            for (auto node = ((TiXmlElement*)base)->FirstChild(name.c_str());
                 node != nullptr;
                 node = node->NextSibling(name.c_str()))
            {
                request_by_xpath_impl(estate_t::node, it, end, node, nodes);
            }
            break;
        }
        case estate_t::attr:
        {
            auto it = std::find_if(beg, end, [](char ch)
            {
                return ch == '/';
            });
            std::string name(beg, it);
            for (auto attr = ((TiXmlElement*)base)->FirstAttribute();
                 attr != nullptr;
                 attr = attr->Next())
            {
                if (::strcmp(attr->Name(), name.c_str()) == 0)
                {
                    request_by_xpath_impl(estate_t::exit, it, end, attr, nodes);
                    break;
                }
            }
            break;
        }
        case estate_t::exit:
        {
            nodes.push_back(base);
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