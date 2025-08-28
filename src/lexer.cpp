#include "lexer.hpp"

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
    return CPP_KEYWORDS.find(ident) != CPP_KEYWORDS.end();
}

Lexer::Lexer(std::istream *input_code) : current_line(0), current_column(0), current_token(TokenType::start_of_input,-1,-1), last_token(TokenType::start_of_input,-1,-1) {
    this->input_code = input_code;
}

void Lexer::next_token() {
    last_token = current_token;
    char c;
    *input_code>>c;

    while (isspace(c)) {
        *input_code>>c;
        if (c == '\n') { // TODO: add handling of commentaries
            current_line++;
            current_column = 0;
        } else {
            current_column++;
        }
    }

    if (is_number(c)) {
        std::stringstream current_number;
        while (is_number(c)) {
            current_number<<c;
            current_column++;
        }
        if (c=='.') {
            current_number<<c;
            current_column++;
            while (is_number(c)) {
                current_number<<c;
                current_column++;
            }
            current_token = Token(TokenType::floating_literal,current_column,current_line,current_number.str());
            return;
        }
        current_token = Token(TokenType::integer_literal,current_column,current_line,current_number.str());
        return;
    }
    if (is_letter(c)) {
        std::stringstream current_identifier;
        while (is_alpha_numeric(c)) {
            current_identifier<<c;
            current_column++;
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
}