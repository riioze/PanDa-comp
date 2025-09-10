#include "node.hpp"

#include <stdexcept>

NodeType convert_literal(TokenType tokenType) {
	switch (tokenType) {
		case TokenType::boolean_literal: {
			return NodeType::boolean_literal;
		}

		case TokenType::integer_literal: {
			return NodeType::integer_literal;
		}

		case TokenType::string_literal: {
			return NodeType::string_literal;
		}

		case TokenType::floating_literal: {
			return NodeType::floating_literal;
		}

		case TokenType::character_literal: {
			return NodeType::character_literal;
		}

		default:throw std::runtime_error("TokenType not recognised as literal");
	}
}
NodeType convert_prefix(TokenType tokenType) {

	switch (tokenType) {

		case TokenType::double_plus : {
			return NodeType::prefix_increment;
		}

		case TokenType::double_minus : {
			return NodeType::prefix_decrement;
		}

		case TokenType::plus : {
			return NodeType::prefix_plus;
		}

		case TokenType::minus : {
			return NodeType::prefix_minus;
		}

		case TokenType::star : {
			return NodeType::indirection;
		}

		case TokenType::ampersand : {
			return NodeType::address_of;
		}

		case TokenType::bitwise_not: {
			return NodeType::bitwise_not;
		}

		case TokenType::logical_not: {
			return NodeType::logical_not;
		}

		default:throw std::runtime_error("Token type not recognised as prefix");
	}
}