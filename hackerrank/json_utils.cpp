#include "json_utils.h"

#include <algorithm>
#include <type_traits>
#include <stack>

inline json_spirit::Object::iterator find_field(const std::string& n, json_spirit::Object& o)
{
    return std::find_if(o.begin(), o.end(), [&n](const json_spirit::Pair& p)
    {
        return p.name_ == n;
    });
}
inline json_spirit::Object::const_iterator find_field(const std::string& n, const json_spirit::Object& o)
{
    return std::find_if(o.begin(), o.end(), [&n](const json_spirit::Pair& p)
    {
        return p.name_ == n;
    });
}
inline json_spirit::mObject::iterator find_field(const std::string& n, json_spirit::mObject& o)
{
    return o.find(n);
}
inline json_spirit::mObject::const_iterator find_field(const std::string& n, const json_spirit::mObject& o)
{
    return o.find(n);
}

inline json_spirit::wObject::iterator find_field(const std::wstring& n, json_spirit::wObject& o)
{
    return std::find_if(o.begin(), o.end(), [&n](const json_spirit::wPair& p)
    {
        return p.name_ == n;
    });
}
inline json_spirit::wObject::const_iterator find_field(const std::wstring& n, const json_spirit::wObject& o)
{
    return std::find_if(o.begin(), o.end(), [&n](const json_spirit::wPair& p)
    {
        return p.name_ == n;
    });
}
inline json_spirit::wmObject::iterator find_field(const std::wstring& n, json_spirit::wmObject& o)
{
    return o.find(n);
}
inline json_spirit::wmObject::const_iterator find_field(const std::wstring& n, const json_spirit::wmObject& o)
{
    return o.find(n);
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

template<typename Result_t>
Result_t t2s(const std::wstring& ws)
{
    Result_t s;
    std::transform(ws.begin(), ws.end(), std::back_inserter(s), [](wchar_t wch)
    {
        return static_cast<typename Result_t::value_type>(wch);
    });
    return s;
}

template<typename Result_t>
Result_t t2s(const std::string& s)
{
    Result_t ts;
    std::transform(s.begin(), s.end(), std::back_inserter(ts), [](char ch)
    {
        return static_cast<typename Result_t::value_type>(ch);
    });
    return ts;
}

enum class estate_t
{
    root,
    star,
    dot_or_sq,
    sq_brackets,
    second_dot,
    expression,
    filter,
    int_index,
    str_index,
    field_name,
    exit,
};

template<typename Iterator_t, typename Value_t>
struct state_t
{
    state_t(Iterator_t beg,
            Iterator_t end,
            Value_t* value,
            estate_t state)
        : beg(beg)
        , end(end)
        , value(value)
        , state(state)
    {
    }
    Iterator_t beg;
    Iterator_t end;
    Value_t* value;
    estate_t   state;
};

template<typename Iterator_t, typename Value_t>
void request_by_jpath_impl(estate_t state,
                           Iterator_t beg,
                           Iterator_t end,
                           Value_t& value,
                           std::vector<Value_t*>& values)
{
    //
    // Types.
    //
    using string_t = typename Value_t::String_type;
    using char_t   = typename string_t::value_type;
    //
    // Finite automata.
    //
    switch (state)
    {
        case estate_t::root:
        {
            switch (widest(*beg))
            {
                //
                // Star as root.
                //
                case L'*':
                {
                    request_by_jpath_impl(estate_t::star,
                                          beg + 1,
                                          end,
                                          value,
                                          values);
                    break;
                }
                //
                // Dollar as rood.
                //
                case L'$':
                {
                    request_by_jpath_impl(estate_t::dot_or_sq,
                                          beg + 1,
                                          end,
                                          value,
                                          values);
                    break;
                }
            }
            break;
        }
        case estate_t::star:
        {
            switch (value.type())
            {
                case json_spirit::obj_type:
                {
                    for (auto& p : value.get_obj())
                    {
                        request_by_jpath_impl(estate_t::dot_or_sq,
                                              beg,
                                              end,
                                              get_second(p),
                                              values);
                    }
                    break;
                }
                case json_spirit::array_type:
                {
                    for (auto& v : value.get_array())
                    {
                        request_by_jpath_impl(estate_t::dot_or_sq,
                                              beg,
                                              end,
                                              v,
                                              values);
                    }
                    break;
                }
                default:
                    break;
            }
            break;
        }
        case estate_t::dot_or_sq:
        {
            if (beg == end)
            {
                request_by_jpath_impl(estate_t::exit,
                                      beg,
                                      end,
                                      value,
                                      values);
                break;
            }
            switch (widest(*beg))
            {
                case L'.':
                {
                    ++beg;
                    //
                    // Nothing after dot.
                    //
                    if (beg == end)
                    {
                        request_by_jpath_impl(estate_t::exit,
                                              beg,
                                              end,
                                              value,
                                              values);
                        break;
                    }
                    //
                    // There is some symbol after dot, let's analize it.
                    //
                    switch (widest(*beg))
                    {
                        //
                        // It's second dot.
                        //
                        case L'.':
                        {
                            request_by_jpath_impl(estate_t::second_dot,
                                                  beg + 1,
                                                  end,
                                                  value,
                                                  values);
                            break;
                        }
                        case L'[':
                        {
                            request_by_jpath_impl(estate_t::sq_brackets,
                                                  beg + 1,
                                                  end,
                                                  value,
                                                  values);
                            break;
                        }
                        case L'*':
                        {
                            request_by_jpath_impl(estate_t::star,
                                                  beg + 1,
                                                  end,
                                                  value,
                                                  values);
                            break;
                        }
                        case L'$':
                        {
                            request_by_jpath_impl(estate_t::root,
                                                  beg,
                                                  end,
                                                  value,
                                                  values);
                            break;
                        }
                        default:
                        {
                            request_by_jpath_impl(estate_t::field_name,
                                                  beg,
                                                  end,
                                                  value,
                                                  values);
                            break;
                        }
                    }
                    break;
                }
                case L'[':
                {
                    request_by_jpath_impl(estate_t::sq_brackets,
                                          beg + 1,
                                          end,
                                          value,
                                          values);
                    break;
                }
                default:
                    break;
            }
            break;
        }
        case estate_t::sq_brackets:
        {
            //
            // Nothing after open square brackets.
            //
            if (beg == end)
            {
                break;
            }
            switch (widest(*beg))
            {
                //
                // Seems we are dealing with an object.
                //
                case L'"':
                {
                    request_by_jpath_impl(estate_t::str_index,
                                          beg + 1,
                                          end,
                                          value,
                                          values);
                    break;
                }
                case L'(':
                {
                    request_by_jpath_impl(estate_t::expression,
                                          beg + 1,
                                          end,
                                          value,
                                          values);
                    break;
                }
                case L'?':
                {
                    request_by_jpath_impl(estate_t::filter,
                                          beg + 1,
                                          end,
                                          value,
                                          values);
                    break;
                }
                //
                // All fields or array elements. It's equivalent to .* syntax.
                //
                case L'*':
                {
                    ++beg;
                    if (beg == end || *beg != static_cast<char_t>(']'))
                    {
                        break;
                    }
                    request_by_jpath_impl(estate_t::star,
                                          beg + 1,
                                          end,
                                          value,
                                          values);
                    break;
                }
                //
                // Seems we are dealing here with arrays.
                //
                default:
                {
                    request_by_jpath_impl(estate_t::int_index,
                                          beg,
                                          end,
                                          value,
                                          values);
                    break;
                }
            }
            break;
        }
        case estate_t::second_dot:
        {
            break;
        }
        case estate_t::expression:
        {
            break;
        }
        case estate_t::filter:
        {
            break;
        }
        case estate_t::int_index:
        {
            if (value.type() != json_spirit::array_type)
            {
                break;
            }
            auto it = std::find_if(beg, end, [](char_t ch)
            {
                return ch < static_cast<char_t>('0') || static_cast<char_t>('9') < ch;
            });
            //
            // If ']' wasn't found or if it goes right after '[', like this: [].
            //
            if (it == beg || it == end || *it != static_cast<char_t>(']'))
            {
                break;
            }
            //
            // According to previour find_if call we know that sequence [beg..it) contains only didits.
            //
            auto index = std::stoul(string_t(beg, it));
            auto& array = value.get_array();
            //
            // If required index is out of range we didn't find anything here.
            //
            if (array.size() <= index)
            {
                break;
            }
            request_by_jpath_impl(estate_t::dot_or_sq,
                                  it + 1,
                                  end,
                                  array[index],
                                  values);
            break;
        }
        case estate_t::str_index:
        {
            //
                    // We are dealing here only with objects.
                    //
            if (value.type() != json_spirit::obj_type)
            {
                break;
            }
            string_t name;
            //
            // Looking for closing '"' symbol.
            //
            char_t previous_ch = static_cast<char_t>('\0');
            auto it = std::find_if(beg, end, [&previous_ch, &name](char_t ch)
            {
                switch (widest(ch))
                {
                    case L'"':
                        switch (widest(previous_ch))
                        {
                            case L'\\':
                                previous_ch = '\0';
                                name.push_back(ch);
                                return false;
                            default:
                                return true;
                        }
                        break;
                    case L'\\':
                        switch (widest(previous_ch))
                        {
                            case L'\\':
                                previous_ch = '\0';
                                name.push_back(ch);
                                return false;
                            default:
                                previous_ch = '\\';
                                return false;
                        }
                        break;
                    default:
                        name.push_back(ch);
                        return false;
                }
            });
            //
            // If '"' wasn't found or if it goes right after opening one, like this "".
            //
            if (it == beg || it == end || *it != static_cast<char_t>('"'))
            {
                break;
            }
            //
            // Let's check if we have closing square bracket.
            //
            if (++it == end || *it != static_cast<char_t>(']'))
            {
                break;
            }
            //
            // Looking for child value.
            //
            auto& obj = value.get_obj();
            auto child_it = find_field(name, obj);
            if (child_it == obj.end())
            {
                break;
            }
            request_by_jpath_impl(estate_t::dot_or_sq,
                                  it + 1,
                                  end,
                                  get_second(*child_it),
                                  values);
            break;
        }
        case estate_t::field_name:
        {
            //
                            // It works only for objects.
                            //
            if (value.type() != json_spirit::obj_type)
            {
                break;
            }
            //
            // Creating field name.
            //
            auto it = std::find_if(beg, end, [](char_t ch)
            {
                return ch == static_cast<char_t>('.') || ch == static_cast<char_t>('[');
            });
            string_t name(beg, it);
            //
            // Looking for field by name.
            //
            auto obj_it = find_field(name, value.get_obj());
            if (obj_it == value.get_obj().end())
            {
                break;
            }
            //
            // Requesting for found by name value.
            //
            request_by_jpath_impl(estate_t::dot_or_sq,
                                  it,
                                  end,
                                  get_second(*obj_it),
                                  values);
            break;
        }
        case estate_t::exit:
        {
            values.push_back(&value);
            break;
        }
        default:
            break;
    }
}


template<typename String_t, typename Value_t>
std::vector<Value_t*> request_by_jpath(const String_t& jpath, Value_t& value)
{
    if (jpath.empty())
    {
        return { };
    }
    std::vector<Value_t*> result_values;
    request_by_jpath_impl(estate_t::root, jpath.begin(), jpath.end(), value, result_values);
    return result_values;
}

template<typename Result_t, typename Value_t, typename String_t>
ResultType_t<Result_t, Value_t> get_value(const String_t& jpath, Value_t& value)
{
    auto values = request_by_jpath(jpath, value);
    if (values.empty())
    {
        throw std::exception(("Can't find any value by JPath '" + t2s<std::string>(jpath) + "'.").c_str());
    }
    if (values.size() != 1)
    {
        throw std::exception(("There are more than one value by JPath '" + t2s<std::string>(jpath) + "'.").c_str());
    }
    return ResultType<Result_t, Value_t>::get_value(*values.back());
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
