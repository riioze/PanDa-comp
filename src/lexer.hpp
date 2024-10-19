#ifndef LEXER_H
#define LEXER_H
#include <vector>
#include "node.hpp"

std::vector<Node> tokenize(std::string const &str);

#endif