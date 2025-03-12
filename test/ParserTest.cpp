#include <gtest/gtest.h>
#include <parser.hpp>
#include <string>
#include <vector>


TEST(ParseContainers, TestRecursiveContainerGrouping){
    Node goal = Node(NodeType::program,"");
    Node parens = Node(NodeType::paren,"()");
    parens.children = {Node(NodeType::brackets,"{}")};
    goal.children = {parens};
    Node result = Node(NodeType::program,"");
    result.children = {
        Node(NodeType::paren,"("),
        Node(NodeType::brackets,"{"),
        Node(NodeType::brackets,"}"),
        Node(NodeType::paren,")")
    };
    group_by_containers(result);
    EXPECT_EQ(goal,result);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}