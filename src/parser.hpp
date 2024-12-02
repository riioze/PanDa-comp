#include "node.hpp"
#include <vector>
#include <iostream>
#include <algorithm>
#ifndef PARSER_H
#define PARSER_H
//! \file parser.hpp

//! \fn int find_last(std::vector<Node> const node_list,Node n)
//! \param node_list : the list to loop threw to find n
//! \param n : the Node to find in the list
//! \return The last index in which n can be found, -1 else
int find_last(std::vector<Node> const node_list,Node n);

//! \fn void raise_missmatched_containers(std::string msg)
//! \brief called when the containers (parenthesis ect) are missmatched (no opening parent for a closing ect)
//! \param msg : message to add to the error
void raise_missmatched_containers(std::string msg);

//! \fn void group_by_containers(Node &node)
//! \brief recursivly groups the containers and create the parse trees inside of each container
//! \param node : Node in wich the containors will be matched and grouped
void group_by_containers(Node &node);

//! \fn void group_operators(Node &node)
//! \brief recursivly goups the operators in a node following the priority rules
//! \param node : Node in wich the operators will be matched and grouped
void group_operators(Node &node);

//! \fn Node get_parse_tree(std::vector<Node> node_list)
//! \brief recursivly create a parse tree from a list of Node
//! \param node_list : the list of Node from wich the parse tree will be created
//! \return the tree created from a list of nodes
Node get_parse_tree(std::vector<Node> node_list);
#endif