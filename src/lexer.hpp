#ifndef LEXER_H
#define LEXER_H
#include <vector>
#include "token.hpp"

std::vector<Token> tokenize(const std::string &str);


#endif