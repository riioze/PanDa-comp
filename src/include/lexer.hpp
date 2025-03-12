#ifndef LEXER_H
#define LEXER_H

#include <vector>
#include "node.hpp"

/**
 * @file lexer.hpp
 * @brief Contains functions for lexical analysis.
 */

/**
 * @brief Converts a string into a corresponding Node.
 * @param str The string to transform into a Node.
 * @return The Node corresponding to the given string.
 */
Node get_node(const std::string &str);

/**
 * @brief Tokenizes a given string into a list of Nodes.
 * @param str The input string to tokenize.
 * @return A vector of Nodes representing the tokens extracted from the string.
 */
std::vector<Node> tokenize(const std::string &str);

#endif // LEXER_H
