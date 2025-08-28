#include "token.hpp"

Token::Token(TokenType type, int line, int column) {
    this->type = type;
    this->line = line;
    this->column = column;
}

Token::Token(TokenType type, int line, int column, const std::string &representation) {
    this->type = type;
    this->line = line;
    this->column = column;
    this->representation = representation;
}
