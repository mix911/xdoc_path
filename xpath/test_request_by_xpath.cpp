#include "xml_utils.h"
#include <gtest/gtest.h>

using namespace std;

TEST(TestRequestByXPathSuit, TestRequestByXPath)
{
    static const char* c_xml = R"(<root1>
    <nodes name="Value">
        <node nodeName="Value1">Text1</node>
        <node nodeName="Value2"/>
        <node nodeName="Value3">Text3<subnodes/>Text33</node>
        <node nodeName="Value4"><![CDATA[Text4]]></node>
    </nodes>
</root1>
<root2>
</root2>)";
    TiXmlDocument doc;
    doc.Parse(c_xml);
    ASSERT_FALSE(doc.Error());
    auto nodes = request_by_xpath("/root1", &doc);
    ASSERT_EQ(nodes.size(), 1);
    ASSERT_EQ(dynamic_cast<TiXmlElement*>(nodes[0])->Value(), string("root1"));
    auto cnodes = request_by_xpath("/root2", const_cast<const TiXmlDocument*>(&doc));
    ASSERT_EQ(cnodes.size(), 1);
    nodes = request_by_xpath("/root1/nodes", &doc);
    ASSERT_EQ(nodes.size(), 1);
    nodes = request_by_xpath("/root1/nodes/@name", &doc);
    ASSERT_EQ(nodes.size(), 1);
    ASSERT_EQ(dynamic_cast<TiXmlAttribute*>(nodes[0])->Name(), string("name"));
    ASSERT_EQ(dynamic_cast<TiXmlAttribute*>(nodes[0])->Value(), string("Value"));
    nodes = request_by_xpath("/root1/nodes/node/@nodeName", &doc);
    ASSERT_EQ(nodes.size(), 4);
    ASSERT_EQ(dynamic_cast<TiXmlAttribute*>(nodes[0])->Name(), string("nodeName"));
    ASSERT_EQ(dynamic_cast<TiXmlAttribute*>(nodes[1])->Name(), string("nodeName"));
    ASSERT_EQ(dynamic_cast<TiXmlAttribute*>(nodes[2])->Name(), string("nodeName"));
    ASSERT_EQ(dynamic_cast<TiXmlAttribute*>(nodes[3])->Name(), string("nodeName"));
    ASSERT_EQ(dynamic_cast<TiXmlAttribute*>(nodes[0])->Value(), string("Value1"));
    ASSERT_EQ(dynamic_cast<TiXmlAttribute*>(nodes[1])->Value(), string("Value2"));
    ASSERT_EQ(dynamic_cast<TiXmlAttribute*>(nodes[2])->Value(), string("Value3"));
    ASSERT_EQ(dynamic_cast<TiXmlAttribute*>(nodes[3])->Value(), string("Value4"));
    nodes = request_by_xpath("/root1/././././././nodes", &doc);
    ASSERT_EQ(nodes.size(), 1);
    nodes = request_by_xpath("/root1/nodes/node/text()", &doc);
    ASSERT_EQ(dynamic_cast<TiXmlText*>(nodes[0])->Value(), string("Text1"));
    ASSERT_EQ(dynamic_cast<TiXmlText*>(nodes[1])->Value(), string("Text3"));
    ASSERT_EQ(dynamic_cast<TiXmlText*>(nodes[2])->Value(), string("Text33"));
    ASSERT_EQ(dynamic_cast<TiXmlText*>(nodes[3])->Value(), string("Text4"));
}