#ifndef LEXER_H
#define LEXER_H
#include <vector>
#include "node.hpp"

//! \file lexer.hpp

//! \fn Node get_node(const std::string &str)
//! \param str : the string to tranform to Node
//! \return the Node corresponding to the str
Node get_node(const std::string &str);

//! \fn std::vector<Node> tokenize(std::string const &str)
//! \param str : The string to tokenize
//! \return The list of tokens corresponding to the str
std::vector<Node> tokenize(std::string const &str);

#endifs