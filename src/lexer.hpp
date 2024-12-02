#ifndef LEXER_H
#define LEXER_H
#include <vector>
#include "node.hpp"

//! \file lexer.hpp

//! \brief transforms a string into a vector of tokens
//! \param str : The string to tokenize
std::vector<Node> tokenize(std::string const &str);

#endifs