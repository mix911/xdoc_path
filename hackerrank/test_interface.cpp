#include "json_utils.h"

#include <gtest/gtest.h>

using namespace std;

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

TEST(JsonSpiritValueCase, JsonSpiritValueTest)
{
    {
        auto json = make_json<json_spirit::Value>(R"({"Hello" : "field"})");
        const auto& cjson = json;
        auto t = cjson.type();
        const auto& v = get_value("$", cjson);
        ASSERT_EQ(v.type(), json_spirit::obj_type);
    }
    {
        auto json = make_json<json_spirit::mValue>(R"({"Hello" : "field"})");
        const auto& cjson = json;
        auto t = cjson.type();
        const auto& v = get_value("$", cjson);
        ASSERT_EQ(v.type(), json_spirit::obj_type);
    }
    {
        auto json = make_json<json_spirit::wValue>(LR"({"Hello" : "field"})");
        const auto& cjson = json;
        auto t = cjson.type();
        const auto& v = get_value(L"$", cjson);
        ASSERT_EQ(v.type(), json_spirit::obj_type);
    }
    {
        auto json = make_json<json_spirit::Value>(R"({"Hello" : "field"})");
        auto& v = get_value("$", json);
        ASSERT_EQ(v.type(), json_spirit::obj_type);
    }
    {
        auto json = make_json<json_spirit::mValue>(R"({"Hello" : "field"})");
        auto& v = get_value("$", json);
        ASSERT_EQ(v.type(), json_spirit::obj_type);
    }
    {
        auto json = make_json<json_spirit::wValue>(LR"({"Hello" : "field"})");
        auto& v = get_value(L"$", json);
        ASSERT_EQ(v.type(), json_spirit::obj_type);
    }
    {
        auto json = make_json<json_spirit::wmValue>(LR"({"Hello" : "field"})");
        auto& v = get_value(L"$", json);
        ASSERT_EQ(v.type(), json_spirit::obj_type);
    }
}

TEST(JsonSpiritObjectCase, JsonSpiritObjectCase)
{
    {
        auto json = make_json<json_spirit::Value>(R"({"Hello" : "field"})");
        const auto& cjson = json;
        const auto& cobj = get_obj("$", cjson);
        auto& obj = get_obj("$", json);
        ASSERT_EQ(cobj.size(), 1);
        ASSERT_EQ(obj.size(), 1);
    }
    {
        auto json = make_json<json_spirit::mValue>(R"({"Hello" : "field"})");
        const auto& cjson = json;
        const auto& cobj = get_obj("$", cjson);
        auto& obj = get_obj("$", json);
        ASSERT_EQ(cobj.size(), 1);
        ASSERT_EQ(obj.size(), 1);
    }
    {
        auto json = make_json<json_spirit::wValue>(LR"({"Hello" : "field"})");
        const auto& cjson = json;
        const auto& cobj = get_obj(L"$", cjson);
        auto& obj = get_obj(L"$", json);
        ASSERT_EQ(cobj.size(), 1);
        ASSERT_EQ(obj.size(), 1);
    }
    {
        auto json = make_json<json_spirit::wmValue>(LR"({"Hello" : "field"})");
        const auto& cjson = json;
        const auto& cobj = get_obj(L"$", cjson);
        auto& obj = get_obj(L"$", json);
        ASSERT_EQ(cobj.size(), 1);
        ASSERT_EQ(obj.size(), 1);
    }
}

TEST(JsonSpiritArrayCase, JsonSpiritArrayCase)
{
    {
        auto json = make_json<json_spirit::Value>(R"([1, 2, 3])");
        const auto& cjson = json;
        const auto& carr = get_array("$", cjson);
        auto& arr = get_array("$", json);
        ASSERT_EQ(carr.size(), 3);
        ASSERT_EQ(arr.size(), 3);
    }
    {
        auto json = make_json<json_spirit::mValue>(R"([1, 2, 3])");
        const auto& cjson = json;
        const auto& carr = get_array("$", cjson);
        auto& arr = get_array("$", json);
        ASSERT_EQ(carr.size(), 3);
        ASSERT_EQ(arr.size(), 3);
    }
    {
        auto json = make_json<json_spirit::wValue>(LR"([1, 2, 3])");
        const auto& cjson = json;
        const auto& carr = get_array(L"$", cjson);
        auto& arr = get_array(L"$", json);
        ASSERT_EQ(carr.size(), 3);
        ASSERT_EQ(arr.size(), 3);
    }
    {
        auto json = make_json<json_spirit::wmValue>(LR"([1, 2, 3])");
        const auto& cjson = json;
        const auto& carr = get_array(L"$", cjson);
        auto& arr = get_array(L"$", json);
        ASSERT_EQ(carr.size(), 3);
        ASSERT_EQ(arr.size(), 3);
    }
}

TEST(JsonSpiritStringCase, JsonSpiritStringTest)
{
    {
        auto json = make_json<json_spirit::Value>(R"("Hello world!!!")");
        const auto& s = get_str("$", json);
        ASSERT_EQ(s, "Hello world!!!");
    }
    {
        auto json = make_json<json_spirit::mValue>(R"("Hello world!!!")");
        const auto& s = get_str("$", json);
        ASSERT_EQ(s, "Hello world!!!");
    }
    {
        auto json = make_json<json_spirit::wValue>(LR"("Hello world!!!")");
        const auto& s = get_str(L"$", json);
        ASSERT_EQ(s, L"Hello world!!!");
    }
    {
        auto json = make_json<json_spirit::wmValue>(LR"("Hello world!!!")");
        const auto& s = get_str(L"$", json);
        ASSERT_EQ(s, L"Hello world!!!");
    }
}

TEST(JsonSpiritIntCase, JsonSpiritIntTest)
{
    {
        auto json = make_json<json_spirit::Value>(R"(2)");
        const auto& cjson = json;
        int i = get_int("$", cjson);
        ASSERT_EQ(i, 2);
    }
    {
        auto json = make_json<json_spirit::mValue>(R"(2)");
        const auto& cjson = json;
        int i = get_int("$", cjson);
        ASSERT_EQ(i, 2);
    }
    {
        auto json = make_json<json_spirit::wValue>(LR"(2)");
        const auto& cjson = json;
        int i = get_int(L"$", cjson);
        ASSERT_EQ(i, 2);
    }
    {
        auto json = make_json<json_spirit::wmValue>(LR"(2)");
        const auto& cjson = json;
        int i = get_int(L"$", cjson);
        ASSERT_EQ(i, 2);
    }
}

TEST(JsonSpiritBoolCase, JsonSpiritBoolTest)
{
    {
        auto json = make_json<json_spirit::Value>(R"(false)");
        const auto& cjson = json;
        bool b = get_bool("$", cjson);
        ASSERT_EQ(b, false);
    }
    {
        auto json = make_json<json_spirit::mValue>(R"(false)");
        const auto& cjson = json;
        bool b = get_bool("$", cjson);
        ASSERT_EQ(b, false);
    }
    {
        auto json = make_json<json_spirit::wValue>(LR"(false)");
        const auto& cjson = json;
        bool b = get_bool(L"$", cjson);
        ASSERT_EQ(b, false);
    }
    {
        auto json = make_json<json_spirit::wmValue>(LR"(false)");
        const auto& cjson = json;
        bool b = get_bool(L"$", cjson);
        ASSERT_EQ(b, false);
    }
}

TEST(JsonSpiritInt64Case, JsonSpiritInt64Test)
{
    {
        auto json = make_json<json_spirit::Value>(R"(3423423873487389343)");
        const auto& cjson = json;
        std::int64_t i = get_int64("$", cjson);
        ASSERT_EQ(i, 3423423873487389343LL);
    }
    {
        auto json = make_json<json_spirit::mValue>(R"(3423423873487389343)");
        const auto& cjson = json;
        std::int64_t i = get_int64("$", cjson);
        ASSERT_EQ(i, 3423423873487389343LL);
    }
    {
        auto json = make_json<json_spirit::wValue>(LR"(3423423873487389343)");
        const auto& cjson = json;
        std::int64_t i = get_int64(L"$", cjson);
        ASSERT_EQ(i, 3423423873487389343LL);
    }
    {
        auto json = make_json<json_spirit::wmValue>(LR"(3423423873487389343)");
        const auto& cjson = json;
        std::int64_t i = get_int64(L"$", cjson);
        ASSERT_EQ(i, 3423423873487389343LL);
    }
}

TEST(JsonSpiritRealCase, JsonSpiritRealTest)
{
    {
        auto json = make_json<json_spirit::Value>(R"(1.0)");
        const auto& cjson = json;
        double d = get_real("$", cjson);
        ASSERT_EQ(d, 1.0);
    }
    {
        auto json = make_json<json_spirit::mValue>(R"(1.0)");
        const auto& cjson = json;
        double d = get_real("$", cjson);
        ASSERT_EQ(d, 1.0);
    }
    {
        auto json = make_json<json_spirit::wValue>(LR"(1.0)");
        const auto& cjson = json;
        double d = get_real(L"$", cjson);
        ASSERT_EQ(d, 1.0);
    }
    {
        auto json = make_json<json_spirit::wmValue>(LR"(1.0)");
        const auto& cjson = json;
        double d = get_real(L"$", cjson);
        ASSERT_EQ(d, 1.0);
    }
}