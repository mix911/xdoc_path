#include "json_utils.h"
#include <gtest/gtest.h>

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

static const wchar_t* sc_json = LR"(
{ 
    "field1" : 1,
    "field2" : "2",
    "field3" : [1, 2, 3],
    "field4" : false,
    "field5" : {}
})";

using Types = ::testing::Types<json_spirit::Value, json_spirit::mValue, json_spirit::wValue, json_spirit::wmValue>;

template<typename T>
class RequestByJPathOneInOneLevelObjectTest : public ::testing::Test
{
};
TYPED_TEST_SUITE(RequestByJPathOneInOneLevelObjectTest, Types);
TYPED_TEST(RequestByJPathOneInOneLevelObjectTest, Types)
{
    auto json = make_json<TypeParam>(t2s<TypeParam::String_type>(sc_json));
    const auto& cjson = json;
    auto t = cjson.type();
    auto v = request_by_jpath(t2s<TypeParam::String_type>(L"$"), cjson);
    ASSERT_EQ(v.size(), 1);
    ASSERT_EQ(v.back()->type(), json_spirit::obj_type);
}

template<typename T>
class RequestByJPathAllInOneLevelObjectTest : public ::testing::Test
{
};
TYPED_TEST_SUITE(RequestByJPathAllInOneLevelObjectTest, Types);
TYPED_TEST(RequestByJPathAllInOneLevelObjectTest, Types)
{
    auto json = make_json<TypeParam>(t2s<TypeParam::String_type>(sc_json));
    const auto& cjson = json;
    auto t = cjson.type();
    auto v = request_by_jpath(t2s<TypeParam::String_type>(L"*"), cjson);
    ASSERT_EQ(v.size(), 5);
    ASSERT_EQ(v[0]->type(), json_spirit::int_type   );  ASSERT_EQ(v[0]->get_int()           , 1                                 );
    ASSERT_EQ(v[1]->type(), json_spirit::str_type   );  ASSERT_EQ(v[1]->get_str()           , t2s<TypeParam::String_type>(L"2") );
    ASSERT_EQ(v[2]->type(), json_spirit::array_type );  ASSERT_EQ(v[2]->get_array().size()  , 3                                 );
    ASSERT_EQ(v[3]->type(), json_spirit::bool_type  );  ASSERT_EQ(v[3]->get_bool()          , false                             );
    ASSERT_EQ(v[4]->type(), json_spirit::obj_type   );  ASSERT_EQ(v[4]->get_obj().size()    , 0                                 );
}

#undef STR_JSON