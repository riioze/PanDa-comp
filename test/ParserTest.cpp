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

/**
 * @brief Tests the parsing of operations without priority.
 * 
 * This function constructs an expression tree with a single binary operation (e.g., +, -, *, /)
 * and verifies that the `group_operators` function correctly processes it into a structured AST.
 * 
 * @param opType The type of operation (NodeType::add_op, NodeType::sub_op, etc.).
 * @param opSymbol The symbol representing the operation ("+", "-", "*", "/").
 */
void TestParseOperationWithoutPriority(NodeType opType, const std::string& opSymbol) {
    Node goal = Node(NodeType::program, "");
    Node opNode = Node(opType, opSymbol);
    goal.children = {opNode};
    opNode.children = {
        Node(NodeType::literal, "8"),
        Node(NodeType::literal, "2")
    };

    Node result = Node(NodeType::program, "");
    result.children = {
        Node(NodeType::literal, "8"),
        Node(opType, opSymbol),
        Node(NodeType::literal, "2")
    };

    group_operators(result);
    EXPECT_EQ(goal, result);
}

/**
 * @test Tests parsing of an addition operation without priority.
 */
TEST(ParseOperationWithoutPriority, TestOnlyPlus) {
    TestParseOperationWithoutPriority(NodeType::add_op, "+");
}

/**
 * @test Tests parsing of a subtraction operation without priority.
 */
TEST(ParseOperationWithoutPriority, TestOnlyMinus) {
    TestParseOperationWithoutPriority(NodeType::sub_op, "-");
}

/**
 * @test Tests parsing of a multiplication operation without priority.
 */
TEST(ParseOperationWithoutPriority, TestOnlyMultiply) {
    TestParseOperationWithoutPriority(NodeType::mul_op, "*");
}

/**
 * @test Tests parsing of a division operation without priority.
 */
TEST(ParseOperationWithoutPriority, TestOnlyDivide) {
    TestParseOperationWithoutPriority(NodeType::div_op, "/");
}

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}