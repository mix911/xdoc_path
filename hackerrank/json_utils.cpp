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

template<typename Value_t>
struct ResultType<std::string, Value_t>
{
    using type = const std::string&;
    static type get_value(Value_t& v)
    {
        return v.get_str();
    }
};

template<typename Value_t>
struct ResultType<std::wstring, Value_t>
{
    using type = const std::wstring&;
    static type get_value(Value_t& v)
    {
        return v.get_str();
    }
};

template<typename Value_t>
struct ResultType<bool, Value_t>
{
    using type = bool;
    static type get_value(Value_t& v)
    {
        return v.get_bool();
    }
};

template<typename Value_t>
struct ResultType<int, Value_t>
{
    using type = int;
    static type get_value(Value_t& v)
    {
        return v.get_int();
    }
};

template<typename Value_t>
struct ResultType<std::int64_t, Value_t>
{
    using type = std::int64_t;
    static type get_value(Value_t& v)
    {
        return v.get_int64();
    }
};

template<typename Value_t>
struct ResultType<std::uint64_t, Value_t>
{
    using type = std::uint64_t;
    static type get_value(Value_t& v)
    {
        return v.get_uint64();
    }
};

template<typename Value_t>
struct ResultType<double, Value_t>
{
    using type = double;
    static type get_value(Value_t& v)
    {
        return v.get_real();
    }
};

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

template<typename String_t, typename Value_t>
void request_by_jpath_impl(size_t beginIndex,
                           const String_t& jpath,
                           Value_t& value,
                           std::vector<Value_t*>& values)
{
    //
    // Types.
    //
    using tchar_t = typename String_t::value_type;
    //
    // Exit point.
    //
    if (beginIndex >= jpath.size())
    {
        values.push_back(&value);
        return;
    }
    //
    //
    //
    switch (widest(jpath[0]))
    {
        case '$':
            throw std::exception("Not implemented.");
        case '.':
            if (jpath.size() < 2)
            {
                return;
            }
            throw std::exception("Not implemented.");
        default:
            break;
    }

    //
    // Checking arguments.
    //
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
        //return { value };
    }
    auto current_value = &value;
    //
    // List of states.
    //
    enum class estate_t
    {
        dot_or_sq_of_root,
        reading_field_name_or_dot_of_root,
        reading_field_name_of_root,
        recursive_descent_of_root,
    } state = estate_t::dot_or_sq_of_root;
    //
    // For each symbol in jpath except first one.
    //
    String_t field_name;
    for (size_t i = 1; i < jpath.size(); ++i)
    {
        wchar_t ch = widest(jpath[i]);
        switch (state)
        {
            case estate_t::dot_or_sq_of_root:
                switch (ch)
                {
                    case L'.':
                    {
                        if (current_value->type() != json_spirit::obj_type)
                        {
                            throw std::exception(("Subpath [0.." + std::to_string(i) + ") isn't an object.").c_str());
                        }
                        state = estate_t::reading_field_name_or_dot_of_root;
                        break;
                    }
                    case L'[':
                        throw std::exception("Not implemented.");
                    case L'*':
                        throw std::exception("Not implemented.");
                    default:
                        throw std::exception("Second symbol of jpath has to be '.' or '['.");
                }
                break;
            case estate_t::reading_field_name_or_dot_of_root:
                switch (ch)
                {
                    case L'.':
                        state = estate_t::recursive_descent_of_root;
                        break;
                    default:
                        field_name += static_cast<tchar_t>(ch);
                        state = estate_t::reading_field_name_of_root;
                        break;
                }
                break;
            case estate_t::recursive_descent_of_root:
                throw std::exception("Not implemented.");
            case estate_t::reading_field_name_of_root:
                switch (ch)
                {
                    case L'.':
                        throw std::exception("Not implemented.");
                    case L'[':
                        throw std::exception("Not implemented.");
                    default:
                        throw std::exception("Not implemented.");
                }
                break;
            default:
                throw std::exception("Not implemented.");
        }
    }
    throw "Not implemented.";
}

inline auto& get_second(json_spirit::Pair& p)
{
    return p.value_;
}
inline const auto& get_second(const json_spirit::Pair& p)
{
    return p.value_;
}
inline auto& get_second(json_spirit::wPair& p)
{
    return p.value_;
}
inline const auto& get_second(const json_spirit::wPair& p)
{
    return p.value_;
}

inline auto& get_second(json_spirit::mObject::value_type& p)
{
    return p.second;
}
inline const auto& get_second(const json_spirit::mObject::value_type& p)
{
    return p.second;
}
inline auto& get_second(json_spirit::wmObject::value_type& p)
{
    return p.second;
}
inline const auto& get_second(const json_spirit::wmObject::value_type& p)
{
    return p.second;
}

template<typename String_t, typename Value_t>
std::vector<Value_t*> request_by_jpath(const String_t& jpath, Value_t& value)
{
    std::vector<Value_t*> result_values;
    if (jpath.empty())
    {
        return { };
    }
    switch (widest(jpath[0]))
    {
        case L'$':
            request_by_jpath_impl(1, jpath, value, result_values);
            break;
        case L'*':
            switch (value.type())
            {
                case json_spirit::obj_type:
                    for (auto& p : value.get_obj())
                    {
                        auto& s = get_second(p);
                        request_by_jpath_impl(1, jpath, s, result_values);
                    }
                    break;
                case json_spirit::array_type:
                    for (auto& v : value.get_array())
                    {
                        request_by_jpath_impl(1, jpath, v, result_values);
                    }
                    break;
                default:
                    break;
            }
            break;
    }
    return result_values;
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
        dot_or_sq_of_root,
        reading_field_name_or_dot_of_root,
    } state = estate_t::dot_or_sq_of_root;
    String_t field_name;
    for (size_t i = 1; i < jpath.size(); ++i)
    {
        wchar_t ch = widest(jpath[i]);
        switch (state)
        {
            case estate_t::dot_or_sq_of_root:
                switch (ch)
                {
                    case L'.':
                    {
                        if (current_value->type() != json_spirit::obj_type)
                        {
                            throw std::exception(("Subpath [0.." + std::to_string(i) + ") isn't an object.").c_str());
                        }
                        state = estate_t::reading_field_name_or_dot_of_root;
                        break;
                    }
                    case L'[':
                        break;
                    default:
                        throw std::exception("Second symbol of jpath has to be '.' or '['.");
                }
                break;
            case estate_t::reading_field_name_or_dot_of_root:
                switch (ch)
                {
                    case L'.':
                        
                        break;
                    default:
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

const std::string& get_str(const std::string& jpath, const json_spirit::Value& value)
{
    return get_value<std::string>(jpath, value);
}
const std::string& get_str(const std::string& jpath, const json_spirit::mValue& value)
{
    return get_value<std::string>(jpath, value);
}
const std::wstring& get_str(const std::wstring& jpath, const json_spirit::wValue& value)
{
    return get_value<std::wstring>(jpath, value);
}
const std::wstring& get_str(const std::wstring& jpath, const json_spirit::wmValue& value)
{
    return get_value<std::wstring>(jpath, value);
}

bool get_bool(const std::string& jpath, const json_spirit::Value& value)
{
    return get_value<bool>(jpath, value);
}
bool get_bool(const std::string& jpath, const json_spirit::mValue& value)
{
    return get_value<bool>(jpath, value);
}
bool get_bool(const std::wstring& jpath, const json_spirit::wValue& value)
{
    return get_value<bool>(jpath, value);
}
bool get_bool(const std::wstring& jpath, const json_spirit::wmValue& value)
{
    return get_value<bool>(jpath, value);
}

int get_int(const std::string& jpath, const json_spirit::Value& value)
{
    return get_value<int>(jpath, value);
}
int get_int(const std::string& jpath, const json_spirit::mValue& value)
{
    return get_value<int>(jpath, value);
}
int get_int(const std::wstring& jpath, const json_spirit::wValue& value)
{
    return get_value<int>(jpath, value);
}
int get_int(const std::wstring& jpath, const json_spirit::wmValue& value)
{
    return get_value<int>(jpath, value);
}

std::int64_t get_int64(const std::string& jpath, const json_spirit::Value& value)
{
    return get_value<std::int64_t>(jpath, value);
}
std::int64_t get_int64(const std::string& jpath, const json_spirit::mValue& value)
{
    return get_value<std::int64_t>(jpath, value);
}
std::int64_t get_int64(const std::wstring& jpath, const json_spirit::wValue& value)
{
    return get_value<std::int64_t>(jpath, value);
}
std::int64_t get_int64(const std::wstring& jpath, const json_spirit::wmValue& value)
{
    return get_value<std::int64_t>(jpath, value);
}

std::uint64_t get_uint64(const std::string& jpath, const json_spirit::Value& value)
{
    return get_value<std::uint64_t>(jpath, value);
}
std::uint64_t get_uint64(const std::string& jpath, const json_spirit::mValue& value)
{
    return get_value<std::uint64_t>(jpath, value);
}
std::uint64_t get_uint64(const std::wstring& jpath, const json_spirit::wValue& value)
{
    return get_value<std::uint64_t>(jpath, value);
}
std::uint64_t get_uint64(const std::wstring& jpath, const json_spirit::wmValue& value)
{
    return get_value<std::uint64_t>(jpath, value);
}

double get_real(const std::string& jpath, const json_spirit::Value& value)
{
    return get_value<double>(jpath, value);
}
double get_real(const std::string& jpath, const json_spirit::mValue& value)
{
    return get_value<double>(jpath, value);
}
double get_real(const std::wstring& jpath, const json_spirit::wValue& value)
{
    return get_value<double>(jpath, value);
}
double get_real(const std::wstring& jpath, const json_spirit::wmValue& value)
{
    return get_value<double>(jpath, value);
}

std::vector<const json_spirit::Value*> request_by_jpath(const std::string& jpath, const json_spirit::Value& value)
{
    return request_by_jpath<>(jpath, value);
}
std::vector<const json_spirit::mValue*> request_by_jpath(const std::string& jpath, const json_spirit::mValue& value)
{
    return request_by_jpath<>(jpath, value);
}
std::vector<const json_spirit::wValue*> request_by_jpath(const std::wstring& jpath, const json_spirit::wValue& value)
{
    return request_by_jpath<>(jpath, value);
}
std::vector<const json_spirit::wmValue*> request_by_jpath(const std::wstring& jpath, const json_spirit::wmValue& value)
{
    return request_by_jpath<>(jpath, value);
}

std::vector<json_spirit::Value*> request_by_jpath(const std::string& jpath, json_spirit::Value& value)
{
    return request_by_jpath<>(jpath, value);
}
std::vector<json_spirit::mValue*> request_by_jpath(const std::string& jpath, json_spirit::mValue& value)
{
    return request_by_jpath<>(jpath, value);
}
std::vector<json_spirit::wValue*> request_by_jpath(const std::wstring& jpath, json_spirit::wValue& value)
{
    return request_by_jpath<>(jpath, value);
}
std::vector<json_spirit::wmValue*> request_by_jpath(const std::wstring& jpath, json_spirit::wmValue& value)
{
    return request_by_jpath<>(jpath, value);
}
