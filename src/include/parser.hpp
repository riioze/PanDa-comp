#ifndef PARSER_H
#define PARSER_H

#include "node.hpp"
#include <vector>
#include <iostream>
#include <algorithm>

/**
 * @file parser.hpp
 * @brief Defines functions for parsing nodes and constructing a parse tree.
 */

/**
 * @brief Finds the last occurrence of a given node in a list.
 * 
 * @param node_list The list of nodes to search in.
 * @param n The node to find.
 * @return The last index where the node is found, or -1 if not found.
 */
int find_last(const std::vector<Node>& node_list, Node n);

/**
 * @brief Raises an error when mismatched containers (e.g., parentheses) are detected.
 * 
 * @param msg Additional message to include in the error.
 */
void raise_missmatched_containers(const std::string& msg);

/**
 * @brief Finds the closing container corresponding to an opening container node.
 * 
 * @param opening Iterator pointing to the opening container node.
 * @param end Iterator pointing to the end of the nodes.
 * @return Iterator pointing to the corresponding closing container or the end if not found.
 */
std::vector<Node>::iterator go_to_closing(std::vector<Node>::iterator opening, std::vector<Node>::iterator end);    

/**
 * @brief Recursively groups nodes inside containers and creates parse trees within them.
 * 
 * @param node The node in which container nodes will be matched and grouped.
 */
void group_by_containers(Node &node);


/**
 * @brief Splits a vector of Nodes into multiple vectors based on a delimiter (`;`).
 * @param nodes The vector of Nodes to split.
 * @return A vector of vectors containing the split sequences.
 */
std::vector<std::vector<Node>> cut_by_delimiters(std::vector<Node>);

/**
 * @brief Finds the node with the lowest priority using iterators.
 * @param nodes The vector of nodes representing an expression.
 * @return Iterator to the node with the lowest priority, or `nodes.end()` if no operator is found.
 */
std::vector<Node>::iterator find_lowest_priority_node(std::vector<Node>& nodes);

/**
 * @brief transforms a list of nodes into a node with children using the lowest priority one
 * @param nodes The vector of nodes representing an expression.
 * @return the node created
 */
Node get_grouped_expression(std::vector<Node> nodes);

/**
 * @brief Recursively groups instructions within a node based on priority rules.
 * 
 * @param node The node in which instuctions will be matched and grouped.
 */
void group_instructions(Node &node);

/**
 * @brief Recursively creates a parse tree from a list of nodes.
 * 
 * @param root The root node of the parse tree, typically of type `program` if it's the main program root.
 * @param node_list The list of nodes from which the parse tree will be constructed.
 */
void get_parse_tree(Node &root, const std::vector<Node>& node_list);

#endif // PARSER_H
