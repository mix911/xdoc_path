#include "json_utils.h"

#include <algorithm>

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

template<typename Json_t, typename Value_t>
struct JsonResultType
{
    using type = const Json_t&;
};

template<>
struct JsonResultType<int, json_spirit::Value>
{
    using type = int;
};

template<>
struct JsonResultType<bool, json_spirit::Value>
{
    using type = bool;
};

template<>
struct JsonResultType<std::int64_t, json_spirit::Value>
{
    using type = std::int64_t;
};

template<>
struct JsonResultType<std::uint64_t, json_spirit::Value>
{
    using type = std::uint64_t;
};

template<>
struct JsonResultType<double, json_spirit::Value>
{
    using type = double;
};

template<>
struct JsonResultType<std::wstring, json_spirit::wValue>
{
    using type = const std::wstring&;
};

template<typename Result_t, typename Value_t>
typename JsonResultType<Result_t, Value_t>::type value_2_result(const Value_t& value)
{
    Result_t res;
    std::remove_cv_t<std::remove_reference_t<typename JsonResultType<Result_t, Value_t>::type>> t;
    throw "Not implemented.";
}

template<>
inline typename JsonResultType<json_spirit::Value,
    json_spirit::Value>::type value_2_result<json_spirit::Value>(const json_spirit::Value& value)
{
    return value;
}

template<>
inline typename JsonResultType<json_spirit::Object,
    json_spirit::Value>::type value_2_result<json_spirit::Object>(const json_spirit::Value& value)
{
    return value.get_obj();
}

template<>
inline typename JsonResultType<json_spirit::Array,
    json_spirit::Value>::type value_2_result<json_spirit::Array>(const json_spirit::Value& value)
{
    return value.get_array();
}

template<>
inline typename JsonResultType<std::string,
    json_spirit::Value>::type value_2_result<std::string>(const json_spirit::Value& value)
{
    return value.get_str();
}

template<>
inline typename JsonResultType<int,
    json_spirit::Value>::type value_2_result<int>(const json_spirit::Value& value)
{
    return value.get_int();
}

template<>
inline typename JsonResultType<std::int64_t,
    json_spirit::Value>::type value_2_result<std::int64_t>(const json_spirit::Value& value)
{
    return value.get_int64();
}

template<>
inline typename JsonResultType<std::uint64_t,
    json_spirit::Value>::type value_2_result<std::uint64_t>(const json_spirit::Value& value)
{
    return value.get_uint64();
}

template<>
inline typename JsonResultType<bool,
    json_spirit::Value>::type value_2_result<bool>(const json_spirit::Value& value)
{
    return value.get_bool();
}

template<>
inline typename JsonResultType<double,
    json_spirit::Value>::type value_2_result<double>(const json_spirit::Value& value)
{
    return value.get_real();
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
typename JsonResultType<Result_t,
    json_spirit::Value>::type get_value(const String_t& jpath, const Value_t& value)
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

const json_spirit::wObject& get_obj(const std::wstring& jpath, const json_spirit::wValue& value)
{
    return get_value<json_spirit::wObject>(jpath, value);
}

const json_spirit::Array& get_array(const std::string& jpath, const json_spirit::Value& value)
{
    return get_value<json_spirit::Array>(jpath, value);
}

const json_spirit::wArray& get_array(const std::wstring& jpath, const json_spirit::wValue& value)
{
    return get_value<json_spirit::wArray>(jpath, value);
}

const std::string& get_str(const std::string& jpath, const json_spirit::Value& value)
{
    return get_value<std::string>(jpath, value);
}

bool get_bool(const std::wstring& jpath, const json_spirit::wValue& value)
{
    return get_value<bool>(jpath, value);
}

int get_int(const std::string& jpath, const json_spirit::Value& value)
{
    return get_value<int>(jpath, value);
}

int get_int(const std::wstring& jpath, const json_spirit::wValue& value)
{
    return get_value<int>(jpath, value);
}

std::int64_t get_int64(const std::string& jpath, const json_spirit::Value& value)
{
    return get_value<std::int64_t>(jpath, value);
}

std::int64_t get_int64(const std::wstring& jpath, const json_spirit::wValue& value)
{
    return get_value<std::int64_t>(jpath, value);
}

std::uint64_t get_uint64(const std::string& jpath, const json_spirit::Value& value)
{
    return get_value<std::uint64_t>(jpath, value);
}

std::uint64_t get_uint64(const std::wstring& jpath, const json_spirit::wValue& value)
{
    return get_value<std::uint64_t>(jpath, value);
}

double get_real(const std::string& jpath, const json_spirit::Value& value)
{
    return get_value<double>(jpath, value);
}

double get_real(const std::wstring& jpath, const json_spirit::wValue& value)
{
    return get_value<double>(jpath, value);
}
