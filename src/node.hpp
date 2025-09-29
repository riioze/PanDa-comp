#ifndef PANDA_NODE_HPP
#define PANDA_NODE_HPP
#include <utility>

#include "token.hpp"

enum class NodeType {
	integer_literal,                   // e.g., 42
	floating_literal,                  // e.g., 3.14
	character_literal,                 // e.g., 'a'
	string_literal,                    // e.g., "hello"
	boolean_literal,                   // e.g., true or false

	reference,                         // when a variable is used in an expression

	prefix_increment,                  // e.g., ++a
	prefix_decrement,                  // e.g., --a
	prefix_plus,                       // e.g., +a
	prefix_minus,                      // e.g., -a
	bitwise_not,                       // e.g., ~a
	logical_not,                       // e.g., !a

	indirection,                       // e.g., *a
	address_of,                        // e.g., &a

	binary_multiplication,             // e.g., a*b
	binary_division,                   // e.g., a/b
	binary_modulo,                     // e.g., a%b
	binary_addition,                   // e.g., a+b
	binary_subtraction,                // e.g., a-b

	greater_than,                      // e.g., >
	less_than,                         // e.g., <
	greater_than_or_equal,             // e.g., >=
	less_than_or_equal,                // e.g., <=

	double_equal,                      // e.g., ==
	not_equal,                         // e.g., !=

	logical_and,                       // e.g., a&&b
	logical_or,                        // e.g., a||b

	direct_assignment,                 // e.g., a=b

	eof,                               // automatically returned at the end of the file
};
NodeType convert_literal(TokenType tokenType);
NodeType convert_prefix(TokenType tokenType);

class Node {
	public:
	NodeType type;
	Token token;
	std::vector<Node> children;

	Node() : type(NodeType::eof), token(), children() {}
	Node(NodeType type, Token token) : type(type), token(std::move(token)), children() {}
	Node(NodeType type, Token token, std::vector<Node> children) : type(type), token(std::move(token)), children(std::move(children)) {}



};


#endif //PANDA_NODE_HPP