
#ifndef PANDA_PARSER_HPP
#define PANDA_PARSER_HPP
#include "lexer.hpp"
#include "node.hpp"


class Parser {
	private:
	Lexer lexer;

	public:
	explicit Parser(Lexer lexer) : lexer(std::move(lexer)) {};

	Node get_next_tree();
	Node get_instruction();
	Node get_expression();
	Node get_prefix();
	Node get_suffix();
	Node get_atom();
};


#endif // PANDA_PARSER_HPP
