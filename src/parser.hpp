#include "node.hpp"
#include <vector>
#include <iostream>
#include <algorithm>
#ifndef PARSER_H
#define PARSER_H
//! \file parser.hpp

//! \fn Node get_parse_tree(std::vector<Node> node_list)
//! \return the tree created from a list of nodes
Node get_parse_tree(std::vector<Node> node_list);

#endif