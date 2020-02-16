#include "jspirit_path.h"
#include <gtest/gtest.h>

using namespace th::json;

template<typename Result_t>
Result_t make_json(const std::string& s)
{
    Result_t json;
    json_spirit::read(s, json);
    return json;
}

template<typename Result_t>
Result_t make_json(const std::wstring& s)
{
    Result_t json;
    json_spirit::read(s, json);
    return json;
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

using Types = ::testing::Types<json_spirit::Value, json_spirit::mValue, json_spirit::wValue, json_spirit::wmValue>;

template<typename T>
class RequestByJPathOneInOneLevelObjectTest : public ::testing::Test
{
};
TYPED_TEST_CASE(RequestByJPathOneInOneLevelObjectTest, Types);
TYPED_TEST(RequestByJPathOneInOneLevelObjectTest, Types)
{
    static const wchar_t* sc_json = LR"(
{ 
    "field1" : 1,
    "field2" : "2",
    "field3" : [1, [ { "inside_two_arrays" : "you_ll_find_me" } ], 3],
    "field4" : false,
    "field5" : {
        "field6" : "field6_field",
        "\"complicataed\"\\\\__\"name" : [{
            "field" : true
        }]
    },
    "field6" : [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
})";
    using string_t = typename TypeParam::String_type;
    {
        auto json = make_json<TypeParam>(t2s<string_t>(sc_json));
        const auto& cjson = json;
        auto t = cjson.type();
        auto v = request_by_jpath(t2s<string_t>(L"$"), cjson);
        ASSERT_EQ(v.size(), 1);
        ASSERT_EQ(v.back()->type(), json_spirit::obj_type);
    }
    {
        auto json = make_json<TypeParam>(t2s<string_t>(sc_json));
        const auto& cjson = json;
        auto t = cjson.type();
        auto v = request_by_jpath(t2s<string_t>(L"$."), cjson);
        ASSERT_EQ(v.size(), 1);
        ASSERT_EQ(v.back()->type(), json_spirit::obj_type);
    }
    {
        auto json = make_json<TypeParam>(t2s<string_t>(sc_json));
        const auto& cjson = json;
        auto t = cjson.type();
        auto v = request_by_jpath(t2s<string_t>(L"$.field1"), cjson);
        ASSERT_EQ(v.size(), 1);
        ASSERT_EQ(v.back()->type(), json_spirit::int_type);
        ASSERT_EQ(v.back()->get_int(), 1);
        v = request_by_jpath(t2s<string_t>(L"$.field3"), cjson);
        ASSERT_EQ(v.size(), 1);
        ASSERT_EQ(v.back()->type(), json_spirit::array_type);
        v = request_by_jpath(t2s<string_t>(L"$.field5.field6"), cjson);
        ASSERT_EQ(v.size(), 1);
        ASSERT_EQ(v.back()->type(), json_spirit::str_type);
        ASSERT_EQ(v.back()->get_str(), t2s<string_t>(L"field6_field"));
        v = request_by_jpath(t2s<string_t>(L"$.field5.field6."), cjson);
        ASSERT_EQ(v.size(), 1);
        ASSERT_EQ(v.back()->type(), json_spirit::str_type);
        ASSERT_EQ(v.back()->get_str(), t2s<string_t>(L"field6_field"));
        v = request_by_jpath(t2s<string_t>(L"$.$.$.$.field5.field6."), cjson);
        ASSERT_EQ(v.size(), 1);
        ASSERT_EQ(v.back()->type(), json_spirit::str_type);
        ASSERT_EQ(v.back()->get_str(), t2s<string_t>(L"field6_field"));
        v = request_by_jpath(t2s<string_t>(L"$.field3[2]"), cjson);
        ASSERT_EQ(v.size(), 1);
        ASSERT_EQ(v.back()->type(), json_spirit::int_type);
        ASSERT_EQ(v.back()->get_int(), 3);
        v = request_by_jpath(t2s<string_t>(L"$.field3[1][0].inside_two_arrays"), cjson);
        ASSERT_EQ(v.size(), 1);
        ASSERT_EQ(v.back()->type(), json_spirit::str_type);
        ASSERT_EQ(v.back()->get_str(), t2s<string_t>(L"you_ll_find_me"));
        v = request_by_jpath(t2s<string_t>(L"$[\"field3\"][1][0][\"inside_two_arrays\"]"), cjson);
        ASSERT_EQ(v.size(), 1);
        ASSERT_EQ(v.back()->type(), json_spirit::str_type);
        ASSERT_EQ(v.back()->get_str(), t2s<string_t>(L"you_ll_find_me"));
        v = request_by_jpath(
            t2s<string_t>(LR"($["field5"]["\"complicataed\"\\\\__\"name"][0].field)"), 
            cjson);
        ASSERT_EQ(v.size(), 1);
        ASSERT_EQ(v.back()->type(), json_spirit::bool_type);
        ASSERT_EQ(v.back()->get_bool(), true);
        v = request_by_jpath(t2s<string_t>(LR"($.field3[*])"), cjson);
        ASSERT_EQ(v.size(), 3);
        v = request_by_jpath(t2s<string_t>(L"$[*]"), cjson);
        ASSERT_EQ(v.size(), 6);
        v = request_by_jpath(t2s<string_t>(LR"($.field6[0:3])"), cjson);
        ASSERT_EQ(v.size(), 3);
        ASSERT_EQ(v[0]->get_int(), 0);
        ASSERT_EQ(v[1]->get_int(), 1);
        ASSERT_EQ(v[2]->get_int(), 2);
        v = request_by_jpath(t2s<string_t>(LR"($.field6[3:7])"), cjson);
        ASSERT_EQ(v.size(), 4);
        ASSERT_EQ(v[0]->get_int(), 3);
        ASSERT_EQ(v[1]->get_int(), 4);
        ASSERT_EQ(v[2]->get_int(), 5);
        ASSERT_EQ(v[3]->get_int(), 6);
        v = request_by_jpath(t2s<string_t>(LR"($.field6[3:7:2])"), cjson);
        ASSERT_EQ(v.size(), 2);
        ASSERT_EQ(v[0]->get_int(), 3);
        ASSERT_EQ(v[1]->get_int(), 5);
    }
}

template<typename T>
class RequestByJPathAllInOneLevelObjectTest : public ::testing::Test
{
};
TYPED_TEST_CASE(RequestByJPathAllInOneLevelObjectTest, Types);
TYPED_TEST(RequestByJPathAllInOneLevelObjectTest, Types)
{
    static const wchar_t* sc_json = LR"(
{ 
    "field1" : 1,
    "field2" : "2",
    "field3" : [1, 2, 3],
    "field4" : false,
    "field5" : { },
    "field6" : { "x" : 1 },
    "field7" : { "x" : 2 },
    "field8" : { "x" : 3 }
})";
    using string_t = typename TypeParam::String_type;
    auto json = make_json<TypeParam>(t2s<TypeParam::String_type>(sc_json));
    const auto& cjson = json;
    auto t = cjson.type();
    auto v = request_by_jpath(t2s<TypeParam::String_type>(L"*"), cjson);
    ASSERT_EQ(v.size(), 8);
    ASSERT_EQ(v[0]->type(), json_spirit::int_type   );  ASSERT_EQ(v[0]->get_int()           , 1                                 );
    ASSERT_EQ(v[1]->type(), json_spirit::str_type   );  ASSERT_EQ(v[1]->get_str()           , t2s<TypeParam::String_type>(L"2") );
    ASSERT_EQ(v[2]->type(), json_spirit::array_type );  ASSERT_EQ(v[2]->get_array().size()  , 3                                 );
    ASSERT_EQ(v[3]->type(), json_spirit::bool_type  );  ASSERT_EQ(v[3]->get_bool()          , false                             );
    ASSERT_EQ(v[4]->type(), json_spirit::obj_type   );  ASSERT_EQ(v[4]->get_obj().size()    , 0                                 );
    v = request_by_jpath(t2s<string_t>(L"*.x"), cjson);
    ASSERT_EQ(v.size(), 3);
    ASSERT_EQ(v[0]->get_int(), 1);
    ASSERT_EQ(v[1]->get_int(), 2);
    ASSERT_EQ(v[2]->get_int(), 3);
    v = request_by_jpath(t2s<string_t>(L"*[\"x\"]"), cjson);
    ASSERT_EQ(v.size(), 3);
    ASSERT_EQ(v[0]->get_int(), 1);
    ASSERT_EQ(v[1]->get_int(), 2);
    ASSERT_EQ(v[2]->get_int(), 3);
    v = request_by_jpath(t2s<string_t>(L"*.[\"x\"]"), cjson);
    ASSERT_EQ(v.size(), 3);
    ASSERT_EQ(v[0]->get_int(), 1);
    ASSERT_EQ(v[1]->get_int(), 2);
    ASSERT_EQ(v[2]->get_int(), 3);
    v = request_by_jpath(t2s<string_t>(L"$.*.[\"x\"]"), cjson);
    ASSERT_EQ(v.size(), 3);
    ASSERT_EQ(v[0]->get_int(), 1);
    ASSERT_EQ(v[1]->get_int(), 2);
    ASSERT_EQ(v[2]->get_int(), 3);
    v = request_by_jpath(t2s<string_t>(L"$.field3[*]"), cjson);
    ASSERT_EQ(v.size(), 3);
    ASSERT_EQ(v[0]->get_int(), 1);
    ASSERT_EQ(v[1]->get_int(), 2);
    ASSERT_EQ(v[2]->get_int(), 3);
    v = request_by_jpath(t2s<string_t>(L"$.field3.*"), cjson);
    ASSERT_EQ(v.size(), 3);
    ASSERT_EQ(v[0]->get_int(), 1);
    ASSERT_EQ(v[1]->get_int(), 2);
    ASSERT_EQ(v[2]->get_int(), 3);
}
