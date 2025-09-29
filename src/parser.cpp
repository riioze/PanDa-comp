
#include "parser.hpp"


Node Parser::get_next_tree() {
	if (lexer.check_token(TokenType::eof)) {
		Token eof_token = lexer.last_token;
		return {NodeType::eof,eof_token};
	}
	return get_instruction();
}
Node Parser::get_instruction() {
	return get_expression(); //TODO: implement it
}


Node Parser::get_expression(int precedence) {

	auto first_part = get_prefix();

	while (check_op_precedence(lexer.current_token.token_type, precedence)) {
		auto operator_token = lexer.current_token;
		lexer.next_token();
		auto operator_ = BINARY_OPERATORS.at(operator_token.token_type);
		int new_precedence = operator_.precedence;
		if (operator_.is_left_to_right) {
			new_precedence-=1;
		}
		auto second_part = get_expression(new_precedence);
		first_part = Node(operator_.node_type,operator_token,{first_part,second_part});
	}
	return first_part;
}

Node Parser::get_prefix() {

	 if (lexer.check_token(PREFIXES)) {
		auto token = lexer.last_token;
		return {convert_prefix(token.token_type),token};

	} else { // If there is no prefix, we check if there is a suffix
		return get_suffix();
	}
}
Node Parser::get_suffix() {
	return get_atom();
}
Node Parser::get_atom() {

	if (lexer.check_token(LITERALS)) { // When we have only a literal
		auto token = lexer.last_token;
		return {convert_literal(token.token_type),token};

	} else if (lexer.check_token(TokenType::left_paren)) { // When whe have an expression between parenthesis
		auto expression = get_expression();
		lexer.accept_token(TokenType::right_paren);
		return expression;

	} else if (lexer.check_token(TokenType::identifier)) { // When we come across a reference to a variable
		auto token = lexer.last_token;
		return {NodeType::reference,token};

	} else {
		throw std::runtime_error("Expected an identifier, a const or a parenthesis, got : "+lexer.current_token.representation);
	}


}
