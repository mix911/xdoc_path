#include "json_utils.h"

#include <algorithm>
#include <type_traits>

const json_spirit::Value& get_field(const std::string& jpath, const std::string& fieldName, const json_spirit::Object& obj)
{
    auto it = std::find_if(obj.begin(), obj.end(), [&fieldName](const json_spirit::Pair& p)
    {
        return p.name_ == fieldName;
    });
    if (it == obj.end())
    {
        throw "Can't find field by '" + jpath, "'";
    }
    return it->value_;
}

json_spirit::Value& get_field(const std::string& jpath, const std::string& fieldName, json_spirit::Object& obj)
{
    auto it = std::find_if(obj.begin(), obj.end(), [&fieldName](const json_spirit::Pair& p)
    {
        return p.name_ == fieldName;
    });
    if (it == obj.end())
    {
        throw "Can't find field by '" + jpath, "'";
    }
    return it->value_;
}

const json_spirit::wValue& get_field(const std::wstring& jpath, const std::wstring& fieldName, const json_spirit::wObject& obj)
{
    auto it = std::find_if(obj.begin(), obj.end(), [&fieldName](const json_spirit::wPair& p)
    {
        return p.name_ == fieldName;
    });
    if (it == obj.end())
    {
        throw L"Can't find field by '" + jpath, L"'";
    }
    return it->value_;
}

json_spirit::wValue& get_field(const std::wstring& jpath, const std::wstring& fieldName, json_spirit::wObject& obj)
{
    auto it = std::find_if(obj.begin(), obj.end(), [&fieldName](const json_spirit::wPair& p)
    {
        return p.name_ == fieldName;
    });
    if (it == obj.end())
    {
        throw L"Can't find field by '" + jpath, L"'";
    }
    return it->value_;
}

template<typename Result_t, typename Value_t>
struct ResultType
{
    using type = std::remove_reference_t<Value_t>&;
};

template<typename Value_t>
struct ResultType<json_spirit::Object, Value_t>
{
    using type = std::conditional_t<std::is_const_v<Value_t>, const json_spirit::Object&, json_spirit::Object&>;
};

template<typename Result_t, typename Value_t>
using ResultType_t = typename ResultType<Result_t, Value_t>::type;

template<typename Result_t, typename Value_t>
inline ResultType_t<Result_t, Value_t> value_2_result(Value_t& value)
{
    return value;
}

inline wchar_t widest(char ch)
{
    return static_cast<wchar_t>(ch);
}

inline wchar_t widest(wchar_t ch)
{
    return ch;
}

template<typename Result_t, typename String_t, typename Value_t>
ResultType_t<Result_t, Value_t> get_value(const String_t& jpath, Value_t& value)
{
    if (jpath.empty())
    {
        throw std::exception("Empty jpath.");
    }
    if (jpath[0] != widest('$'))
    {
        throw std::exception("JPath must start with '$' symbol.");
    }
    if (jpath.length() == 1)
    {
        return value_2_result<Result_t>(value);
    }
    auto current_value = &value;
    enum class estate_t
    {
        dot_or_sq,
    } state = estate_t::dot_or_sq;
    String_t field_name(static_cast<typename String_t::value_type>('$'), 1);
    for (size_t i = 1; i < jpath.size(); ++i)
    {
        wchar_t ch = widest(jpath[i]);
        switch (state)
        {
            case estate_t::dot_or_sq:
                switch (ch)
                {
                    case L'.':
                    {
                        if (current_value->type() != json_spirit::obj_type)
                        {
                            throw "Subpath [0.." + std::to_string(i) + ") isn't an object.";
                        }
                        current_value = &get_field(jpath.substr(0, i), field_name, current_value->get_obj());
                        field_name.clear();
                        break;
                    }
                    case L'[':
                        break;
                    default:
                        field_name += static_cast<typename String_t::value_type>(ch);
                        break;
                }
                break;
            default:
                break;
        }
    }
    throw "Not implemented.";
}

const json_spirit::Value& get_value(const std::string& jpath, const json_spirit::Value& value)
{
    return get_value<json_spirit::Value>(jpath, value);
}

json_spirit::Value& get_value(const std::string& jpath, json_spirit::Value& value)
{
    return get_value<json_spirit::Value>(jpath, value);
}

const json_spirit::wValue& get_value(const std::wstring& jpath, const json_spirit::wValue& value)
{
    return get_value<json_spirit::wValue>(jpath, value);
}

//const json_spirit::Object& get_obj(const std::string& jpath, const json_spirit::Value& value)
//{
//    return get_value<json_spirit::Object>(jpath, value);
//}
//
//json_spirit::Object& get_obj(const std::string& jpath, json_spirit::Value& value)
//{
//    return get_value<json_spirit::Object>(jpath, value);
//}
