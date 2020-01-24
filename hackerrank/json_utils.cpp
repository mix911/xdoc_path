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

const json_spirit::mValue& get_field(const std::string& jpath, const std::string& fieldName, const json_spirit::mObject& obj)
{
    auto it = obj.find(fieldName);
    if (it == obj.end())
    {
        throw "Can't find field by '" + jpath, "'";
    }
    return it->second;
}

json_spirit::mValue& get_field(const std::string& jpath, const std::string& fieldName, json_spirit::mObject& obj)
{
    auto it = obj.find(fieldName);
    if (it == obj.end())
    {
        throw "Can't find field by '" + jpath, "'";
    }
    return it->second;
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

const json_spirit::wmValue& get_field(const std::wstring& jpath, const std::wstring& fieldName, const json_spirit::wmObject& obj)
{
    auto it = obj.find(fieldName);
    if (it == obj.end())
    {
        throw L"Can't find field by '" + jpath, L"'";
    }
    return it->second;
}

json_spirit::wmValue& get_field(const std::wstring& jpath, const std::wstring& fieldName, json_spirit::wmObject& obj)
{
    auto it = obj.find(fieldName);
    if (it == obj.end())
    {
        throw L"Can't find field by '" + jpath, L"'";
    }
    return it->second;
}

template<typename Result_t, typename Value_t>
struct ResultType
{
    using type = Value_t&;
    static type get_value(Value_t& v)
    {
        return v;
    }
};

template<typename Value_t>
struct ResultType<json_spirit::Object, Value_t>
{
    using type = std::conditional_t<std::is_const_v<Value_t>, const json_spirit::Object&, json_spirit::Object&>;
    static type get_value(Value_t& v)
    {
        return v.get_obj();
    }
};

template<typename Value_t>
struct ResultType<json_spirit::wObject, Value_t>
{
    using type = std::conditional_t<std::is_const_v<Value_t>, const json_spirit::wObject&, json_spirit::wObject&>;
    static type get_value(Value_t& v)
    {
        return v.get_obj();
    }
};

template<typename Value_t>
struct ResultType<json_spirit::mObject, Value_t>
{
    using type = std::conditional_t<std::is_const_v<Value_t>, const json_spirit::mObject&, json_spirit::mObject&>;
    static type get_value(Value_t& v)
    {
        return v.get_obj();
    }
};

template<typename Value_t>
struct ResultType<json_spirit::wmObject, Value_t>
{
    using type = std::conditional_t<std::is_const_v<Value_t>, const json_spirit::wmObject&, json_spirit::wmObject&>;
    static type get_value(Value_t& v)
    {
        return v.get_obj();
    }
};

/*********************/
template<typename Value_t>
struct ResultType<json_spirit::Array, Value_t>
{
    using type = std::conditional_t<std::is_const_v<Value_t>, const json_spirit::Array&, json_spirit::Array&>;
    static type get_value(Value_t& v)
    {
        return v.get_array();
    }
};

template<typename Value_t>
struct ResultType<json_spirit::wArray, Value_t>
{
    using type = std::conditional_t<std::is_const_v<Value_t>, const json_spirit::wArray&, json_spirit::wArray&>;
    static type get_value(Value_t& v)
    {
        return v.get_array();
    }
};

template<typename Value_t>
struct ResultType<json_spirit::mArray, Value_t>
{
    using type = std::conditional_t<std::is_const_v<Value_t>, const json_spirit::mArray&, json_spirit::mArray&>;
    static type get_value(Value_t& v)
    {
        return v.get_array();
    }
};

template<typename Value_t>
struct ResultType<json_spirit::wmArray, Value_t>
{
    using type = std::conditional_t<std::is_const_v<Value_t>, const json_spirit::wmArray&, json_spirit::wmArray&>;
    static type get_value(Value_t& v)
    {
        return v.get_array();
    }
};
/*********************/

template<typename Result_t, typename Value_t>
using ResultType_t = typename ResultType<Result_t, Value_t>::type;

inline wchar_t widest(char ch)
{
    return static_cast<wchar_t>(ch);
}

inline wchar_t widest(wchar_t ch)
{
    return ch;
}

template<typename Result_t, typename Value_t, typename String_t>
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
        return ResultType<Result_t, Value_t>::get_value(value);
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

const json_spirit::mValue& get_value(const std::string& jpath, const json_spirit::mValue& value)
{
    return get_value<json_spirit::mValue>(jpath, value);
}

json_spirit::mValue& get_value(const std::string& jpath, json_spirit::mValue& value)
{
    return get_value<json_spirit::mValue>(jpath, value);
}

json_spirit::Value& get_value(const std::string& jpath, json_spirit::Value& value)
{
    return get_value<json_spirit::Value>(jpath, value);
}

const json_spirit::wValue& get_value(const std::wstring& jpath, const json_spirit::wValue& value)
{
    return get_value<json_spirit::wValue>(jpath, value);
}

const json_spirit::wmValue& get_value(const std::wstring& jpath, const json_spirit::wmValue& value)
{
    return get_value<json_spirit::wmValue>(jpath, value);
}

json_spirit::wmValue& get_value(const std::wstring& jpath, json_spirit::wmValue& value)
{
    return get_value<json_spirit::wmValue>(jpath, value);
}

json_spirit::wValue& get_value(const std::wstring& jpath, json_spirit::wValue& value)
{
    return get_value<json_spirit::wValue>(jpath, value);
}

const json_spirit::Object& get_obj(const std::string& jpath, const json_spirit::Value& value)
{
    return get_value<json_spirit::Object>(jpath, value);
}

json_spirit::Object& get_obj(const std::string& jpath, json_spirit::Value& value)
{
    return get_value<json_spirit::Object>(jpath, value);
}

const json_spirit::wObject& get_obj(const std::wstring& jpath, const json_spirit::wValue& value)
{
    return get_value<json_spirit::wObject>(jpath, value);
}

json_spirit::wObject& get_obj(const std::wstring& jpath, json_spirit::wValue& value)
{
    return get_value<json_spirit::wObject>(jpath, value);
}

const json_spirit::mObject& get_obj(const std::string& jpath, const json_spirit::mValue& value)
{
    return get_value<json_spirit::mObject>(jpath, value);
}

json_spirit::mObject& get_obj(const std::string& jpath, json_spirit::mValue& value)
{
    return get_value<json_spirit::mObject>(jpath, value);
}

const json_spirit::wmObject& get_obj(const std::wstring& jpath, const json_spirit::wmValue& value)
{
    return get_value<json_spirit::wmObject>(jpath, value);
}

json_spirit::wmObject& get_obj(const std::wstring& jpath, json_spirit::wmValue& value)
{
    return get_value<json_spirit::wmObject>(jpath, value);
}

const json_spirit::Array& get_array(const std::string& jpath, const json_spirit::Value& value)
{
    return get_value<json_spirit::Array>(jpath, value);
}
const json_spirit::mArray& get_array(const std::string& jpath, const json_spirit::mValue& value)
{
    return get_value<json_spirit::mArray>(jpath, value);
}
const json_spirit::wArray& get_array(const std::wstring& jpath, const json_spirit::wValue& value)
{
    return get_value<json_spirit::wArray>(jpath, value);
}
const json_spirit::wmArray& get_array(const std::wstring& jpath, const json_spirit::wmValue& value)
{
    return get_value<json_spirit::wmArray>(jpath, value);
}
json_spirit::Array& get_array(const std::string& jpath, json_spirit::Value& value)
{
    return get_value<json_spirit::Array>(jpath, value);
}
json_spirit::mArray& get_array(const std::string& jpath, json_spirit::mValue& value)
{
    return get_value<json_spirit::mArray>(jpath, value);
}
json_spirit::wArray& get_array(const std::wstring& jpath, json_spirit::wValue& value)
{
    return get_value<json_spirit::wArray>(jpath, value);
}
json_spirit::wmArray& get_array(const std::wstring& jpath, json_spirit::wmValue& value)
{
    return get_value<json_spirit::wmArray>(jpath, value);
}
