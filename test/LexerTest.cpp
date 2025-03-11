#include <gtest/gtest.h>
#include <lexer.hpp>
#include <string>
#include <vector>

TEST(getNodeTests, TestReturnKeyword){
    Node n = get_node("return");
    ASSERT_EQ(n, Node(NodeType::_return,"return"));
};

TEST(getNodeTests, TestInt64Keyword){
    Node n = get_node("int64");
    ASSERT_EQ(n, Node(NodeType::raw_type,"int64"));
};

TEST(getNodeTests, TestIntLit){
    Node n = get_node("12");
    ASSERT_EQ(n,Node(NodeType::literal,"12"));
};

TEST(TokenizeTests, TestSmallProg){
    std::string str("int64 i = 12;");
    std::vector<Node> goal = {
        Node(NodeType::raw_type,"int64"),
        Node(NodeType::identifier,"i"),
        Node(NodeType::assignment,"="),
        Node(NodeType::literal,"12"),
        Node(NodeType::delimiter,";")
    };
    auto result = tokenize(str);
    ASSERT_EQ(result, goal);

};

TEST(TokenizeTests, TestBigProg){
    std::string str("int64 main(){\n\tint64 i = (3+5)*2;\treturn 69;\n}");
    std::vector<Node> goal = {
        Node(NodeType::raw_type,"int64"),
        Node(NodeType::identifier,"main"),
        Node(NodeType::paren,"("),
        Node(NodeType::paren,")"),
        Node(NodeType::brackets,"{"),
        Node(NodeType::raw_type,"int64"),
        Node(NodeType::identifier,"i"),
        Node(NodeType::assignment,"="),
        Node(NodeType::paren,"("),
        Node(NodeType::literal,"3"),
        Node(NodeType::add_op,"+"),
        Node(NodeType::literal,"5"),
        Node(NodeType::paren,")"),
        Node(NodeType::mul_op,"*"),
        Node(NodeType::literal,"2"),
        Node(NodeType::delimiter,";"),
        Node(NodeType::_return,"return"),
        Node(NodeType::literal,"69"),
        Node(NodeType::delimiter,";"),
        Node(NodeType::brackets,"}")
    };
    auto result = tokenize(str);
    ASSERT_EQ(goal,result);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}