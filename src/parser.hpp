
#ifndef PANDA_PARSER_HPP
#define PANDA_PARSER_HPP
#include <map>


#include "lexer.hpp"
#include "node.hpp"

#define MAX_PRECEDENCE 16

struct op {
	int precedence; // the more the precedence, the less the parts will be grouped together
	bool is_left_to_right;
	NodeType node_type;
};

inline std::map<TokenType,op> BINARY_OPERATORS = {
	{TokenType::star,{5,true,NodeType::binary_multiplication}},
	{TokenType::slash,{5,true,NodeType::binary_division}},
	{TokenType::percent,{5,true,NodeType::binary_modulo}},

	{TokenType::plus,{6,true,NodeType::binary_addition}},
	{TokenType::minus,{6,true,NodeType::binary_subtraction}},

	{TokenType::less_than,{9,true,NodeType::less_than}},
	{TokenType::less_than_or_equal,{9,true,NodeType::less_than_or_equal}},
	{TokenType::greater_than,{9,true,NodeType::greater_than}},
	{TokenType::greater_than_or_equal,{9,true,NodeType::greater_than_or_equal}},

	{TokenType::logical_and,{14,true,NodeType::logical_and}},

	{TokenType::logical_or,{15,true,NodeType::less_than}},

	{TokenType::equal,{16,false,NodeType::direct_assignment}},



};

inline bool check_op_precedence(TokenType tokenType, int precedence) {
	return (BINARY_OPERATORS.contains(tokenType)) && BINARY_OPERATORS.at(tokenType).precedence <= precedence;
}

class Parser {
	private:
	Lexer lexer;

	public:
	explicit Parser(Lexer lexer) : lexer(std::move(lexer)) {};

	Node get_next_tree();
	Node get_instruction();
	Node get_expression(int precedence);
	Node get_expression() {return get_expression(MAX_PRECEDENCE+1);};
	Node get_prefix();
	Node get_suffix();
	Node get_atom();
};


#endif // PANDA_PARSER_HPP
