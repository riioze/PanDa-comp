#include "lexer.hpp"

#include <algorithm>
#include <iostream>
#include <sstream>

bool is_number(char c) {
    return c >= '0' && c <= '9';
}

bool is_letter(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

bool is_alpha_numeric(char c) {
    return is_number(c) || is_letter(c) || c == '_';
}

bool is_keyword(const std::string& ident) {
    return CPP_KEYWORDS.contains(ident);
}

char Lexer::consume_character(){
    char c;
    c = input_code.get();
    current_column++;
	std::cout<< static_cast<int>(c) <<std::endl;
    return c;
}

void Lexer::next_token() {
	last_token = current_token;
	char c = consume_character();
	while (isspace(c)) { // removes all the spacing characters

	    c=consume_character();
	    if (c == '\n') { // TODO: add handling of commentaries
	        current_line++;
	        current_column = 0;
	    }
	}

	if (is_number(c)) { // detect if we start a number token
	    std::stringstream current_number;
	    while (is_number(c)) {
	        c=consume_character();
	    }
	    if (c=='.') { // if we have a point it is a floating number
	        c=consume_character();
	        while (is_number(c)) {
	            c=consume_character();
	        }
	        current_token = Token(TokenType::floating_literal,current_column,current_line,current_number.str());
	        return;
	    }
	    current_token = Token(TokenType::integer_literal,current_column,current_line,current_number.str());
	    return;
	}
	if (is_letter(c)) { // detect if we start an alphanumerical sequence (keyword or identifier)
	    std::stringstream current_identifier;
	    while (is_alpha_numeric(c)) {
	        current_identifier<<c;
	        c=consume_character();
	    }

	    std::string identifier = current_identifier.str();
	    if (is_keyword(identifier)) {
	        if (identifier == "true" || identifier == "false") {
	            current_token = Token(TokenType::boolean_literal,current_column,current_line,identifier);
	            return;
	        }
	        current_token = Token(TokenType::keyword,current_column,current_line,identifier);
	        return;
	    }
	    current_token = Token(TokenType::identifier,current_column,current_line,identifier);
	    return;
	}


	switch (c) {
	    case '\'': {
	        char quoted = consume_character();
	        if (quoted == '\'') {
	            throw std::runtime_error("expected a character between the \'\'");
	        }

	        char end_quote = consume_character();
	        if (end_quote != '\'') {
	            throw std::runtime_error("expected a \' after the character");
	        }
	        set_current_token(TokenType::character_literal, std::string(1, quoted));
	        break;
	    }

	    case '"': {
	        auto quoted_string = std::stringstream();
	        char current_char;
	        while (input_code.good() && input_code.peek() != EOF && input_code.peek() != '"') {
	            current_char = consume_character();
	            quoted_string<<current_char;
	        }

	        if (!input_code.good() || input_code.peek() == EOF) {
	            throw std::runtime_error("unterminated string");
	        }

	        char end_quote = consume_character();
	        if (end_quote != '"') throw std::runtime_error("unterminated string");

	        set_current_token(TokenType::string_literal, quoted_string.str());

	        break;
	    }

	    case '+': {
	        if (input_code.peek() == '=') {
	            consume_character();
	            set_current_token(TokenType::plus_assign, "+=");
	            break;
	        } else if (input_code.peek() == '+'){
	            consume_character();
	            set_current_token(TokenType::double_plus, "++");
	            break;
	        }
	        else {
	            set_current_token(TokenType::plus, "+");
	            break;
	        }
	    }

	    case '-' : {
	        if (input_code.peek() == '=') {
	            consume_character();
	            set_current_token(TokenType::minus_assign, "-=");
	            break;
	        } else if (input_code.peek() == '-'){
	            consume_character();
	            set_current_token(TokenType::double_minus, "--");
	            break;
	        } else if (input_code.peek() == '>') {
		        consume_character();
	        	if (input_code.peek() == '*') {
	        		consume_character();
	        		set_current_token(TokenType::arrow_star, "->*");
	        		break;
	        	} else {
	        		set_current_token(TokenType::arrow, "->");
	        		break;
	        	}
	        }
	        else {
	            set_current_token(TokenType::minus, "-");
	            break;
	        }
	    }

	    case '*' : {
	        if (input_code.peek() == '=') {
	            consume_character();
	            set_current_token(TokenType::star_assign, "*=");
	            break;
	        }
	        else {
	            set_current_token(TokenType::star, "*");
	            break;
	        }
	    }

	    case '/' : {
	        if (input_code.peek() == '=') {
	            consume_character();
	            set_current_token(TokenType::slash_assign, "/=");
	            break;
	        }
	        else {
	            set_current_token(TokenType::slash, "/");
	            break;
	        }
	    }

	    case '%' : {
	        if (input_code.peek() == '=') {
	            consume_character();
	            set_current_token(TokenType::percent_assign, "%=");
	            break;
	        }
	        else {
	            set_current_token(TokenType::percent, "%");
	            break;
	        }
	    }

	    case '=': {
	        if (input_code.peek() == '=') {
	            consume_character();
	            set_current_token(TokenType::double_equal, "==");
	            break;
	        }
	        else {
	            set_current_token(TokenType::equal, "=");
	            break;
	        }
	    }

	    case '!': {
	        if (input_code.peek() == '=') {
	            consume_character();
	            set_current_token(TokenType::not_equal, "!=");
	            break;
	        }
	        else {
	            set_current_token(TokenType::logical_not, "!");
	            break;
	        }
	    }
	    case '>' : {
	        if (input_code.peek() == '=') {
	            consume_character();
	            set_current_token(TokenType::greater_than_or_equal, ">=");
	            break;
	        } else if (input_code.peek() == '>') {
	            consume_character();
	            if (input_code.peek() == '=') {
	                consume_character();
	                set_current_token(TokenType::right_shift_assign, ">>=");
	                break;
	            }
	            else {
	                set_current_token(TokenType::right_shift, ">>");
	                break;
	            }
	        } else {
	            set_current_token(TokenType::greater_than, ">");
	            break;
	        }
	    }

	    case '<': {
	        if (input_code.peek() == '=') {
	            consume_character();
	            set_current_token(TokenType::less_than_or_equal, "<");
	            break;
	        } else if (input_code.peek() == '<') {
	            consume_character();
	            if (input_code.peek() == '=') {
	                consume_character();
	                set_current_token(TokenType::left_shift_assign, "<<=");
	                break;
	            }
	            else {
	                set_current_token(TokenType::left_shift, "<<");
	                break;
	            }
	        } else {
	            set_current_token(TokenType::less_than, "<");
	        }
	    }

	    case '|': {
	        if (input_code.peek() == '=') {
	            consume_character();
	            set_current_token(TokenType::pipe_assign, "|=");
	            break;
	        } else if (input_code.peek() == '|') {
	            consume_character();
	            set_current_token(TokenType::logical_or, "||");
	            break;
	        } else {
	            set_current_token(TokenType::pipe, "|");
	            break;
	        }
	    }

	    case '&': {
	        if (input_code.peek() == '=') {
	            consume_character();
	            set_current_token(TokenType::ampersand_assign, "&=");
	            break;
	        } else if (input_code.peek() == '&') {
	            consume_character();
	            set_current_token(TokenType::logical_and, "&&");
	            break;
	        } else {
	            set_current_token(TokenType::ampersand, "&");
	            break;
	        }
	    }

	    case '^': {
	        if (input_code.peek() == '=') {
	            consume_character();
	            set_current_token(TokenType::hat_assign, "^=");
	            break;
	        } else {
	            set_current_token(TokenType::hat, "^");
	            break;
	        }
	    }

	    case '~' : {
	        set_current_token(TokenType::bitwise_not, "~");
	        break;
	    }

	    case '(': {
	        set_current_token(TokenType::left_paren, "(");
	    	break;
	    }

	    case ')': {
	        set_current_token(TokenType::right_paren, ")");
	    	break;
	    }

	    case '{': {
			set_current_token(TokenType::left_brace, "{");
	    	break;
		}

		case '}': {
			set_current_token(TokenType::right_brace, "}");
	    	break;
		}

		case '[' : {
		    set_current_token(TokenType::left_bracket, "[");
	    	break;
	    }

		case ']': {
			set_current_token(TokenType::right_bracket, "]");
	    	break;
		}

		case ';': {
			set_current_token(TokenType::semicolon, ";");
		    break;
	    }

		case ',': {
	    	set_current_token(TokenType::comma, ",");
	    	break;
		}

		case ':': {
	    	if (input_code.peek() == ':') {
	    		consume_character();
	    		set_current_token(TokenType::scope_resolution, "::");
	    		break;
	    	}
		    else {
			    set_current_token(TokenType::colon, ":");
	    		break;
		    }
		}

		case '?': {
	    	set_current_token(TokenType::question_mark, "?");
	    	break;
	    }

		case '.': {
		    if (input_code.peek() == '*') {
			    consume_character();
		    	set_current_token(TokenType::dot_star, "*");
		    	break;
		    } else {
			    set_current_token(TokenType::dot, ".");
		    	break;
		    }
	    }

		case '#' : {
		    set_current_token(TokenType::hash, "#");
	    	break;
	    }

		case EOF : {
	    	std::cout<<"got eof"<<std::endl;
		    set_current_token(TokenType::eof, "EOF");
	    	break;
	    }

	    default:
	        throw std::runtime_error(std::string("Unexpected character") + c + " char num : " + std::to_string(static_cast<int>(c)));
	}
}
bool Lexer::check_token(TokenType expected) {
	if (current_token.token_type == expected) {
		next_token();
		return true;
	}
	return false;
}
void Lexer::accept_token(TokenType expected) {
	if (!check_token(expected)) {
		throw std::runtime_error("Unexpected Token : " + current_token.representation + " token type code : " + std::to_string(static_cast<int>(current_token.token_type)) + " expected " + std::to_string(static_cast<int>(expected)));
	}
}
bool Lexer::check_token(std::vector<TokenType> expected) {
	return std::ranges::any_of(expected, [this](TokenType expected) {return check_token(expected);});
}
bool Lexer::check_keyword(const std::string& expected) {
	if (!CPP_KEYWORDS.contains(expected)) throw std::runtime_error( expected + "is not a keyword");
	return check_token(TokenType::keyword) && expected == last_token.representation;
}
void Lexer::accept_keyword(const std::string &expected) {
	if (!check_keyword(expected)) throw std::runtime_error("Unexpected keyword or token");
}


void Lexer::set_current_token(TokenType token_type, const std::string &representation) {
    current_token = Token(token_type,current_column,current_line,representation);
}
