#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <optional>
#include <map>
#include <vector>
#include <iostream>

//! \file node.hpp
//! \brief contains all the structs and function for the node

//! \enum NodeType
//! \brief contains all the possible values for Node.type
enum class NodeType{

	//! \brief only one (basically the root)
	program,

	//! \brief contains all the informations about the type (raw type + for instance * const ect)
	full_type,
	//! \brief contains only the basic type (int char ect but also created types from classes)
	raw_type,

	//! \brief mainly variable/function/class name
	identifier,

	//! \brief contains the whole expression
	expression,
	//! \brief * operator
	mul_op,
	//! \brief / operator
	div_op,
	//! \brief \+ operator
	add_op,
	//! \brief \\- operator
	min_op,
	//! \brief full_type indentifier; 
	declaration,
	//! \brief identifier = val;
	assignment,
	//! \brief full_type identifier = val;
	initialisation,
	//! \brief immediate
	literal,

	//! \brief the whole function
	function,
	//! \brief function name +params
	function_sign,
	//! \brief parameters
	function_params,
	//! \brief body
	function_body,
	//! \brief what is returned
	_return,

	//! \brief ; ,
	delimiter,
	//! \brief (, ) and ()
	paren, 
	//! \brief {, } and {}
	brackets,

	
};


//! \struct Node
//! \brief recursive struct containing the tree of the code
struct Node {
	//! \brief type of the Node
	NodeType type;
	//! \brief mostly for debugging, the str repressentation of the node
	std::string repr;
	//! \brief all the children node (for instance in x+y x and y are the children of a + node)
	std::vector<Node> children;
	//! \brief used to represent the children node as indented
	int depth;
	//! \fn Node(NodeType type, std::string repr)
	//! \brief Basic constructor for a node without any depth
	Node(NodeType type, std::string repr) : type(type), repr(repr) ,children(),depth(0){}
	//! \fn Node(NodeType type, std::string repr,int depth)
	//! \brief Basic constructor for a node with a none zero depth
	Node(NodeType type, std::string repr,int depth) : type(type), repr(repr) ,children(), depth(depth){}
	//! \fn void set_depth(int depth)
	//! \brief set the depth of the Node to depth and recursivly update the depth of its children
	inline void set_depth(int depth){
		this->depth = depth;
		for(auto c:children){
			c.set_depth(depth+1);
		}
	}
	//! \fn void add_child(Node child)
	//! \brief Add a new child Node to the Node
	//! \param child : the child to add, its depth will be automatically set to depth+1
	inline void add_child(Node child){
		child.set_depth(this->depth+1);
		children.push_back(child);
	}
	//! \fn void add_child(Node child, int new_depth)
	//! \brief Add a new child Node to the Node
	//! \param child : the child to add, its depth will be automatically set to depth+1
	//! \param new_depth : the depth to assign to the child
	inline void add_child(Node child,int new_depth){
		child.set_depth(new_depth);
		children.push_back(child);
	}
	//! \fn void add_children(std::vector<Node> new_children)
	//! \brief Add new children Nodes to the Node
	//! \param new_children : the children to add, their depth will be automatically set to depth+1
	inline void add_children(std::vector<Node> new_children){
		for (Node child : new_children){
			add_child(child);
		}
	}
	//! \fn void add_children(std::vector<Node> new_children,int new_depth)
	//! \brief Add new children Nodes to the Node
	//! \param new_children : the children to add, their depth will be automatically set to depth+1
	//! \param new_depth : the depth to assign to the children
	inline void add_children(std::vector<Node> new_children,int new_depth){
		for (Node child : new_children){
			add_child(child,new_depth);
		}
	}
	//! \fn void reset_children(std::vector<Node> new_children)
	//! \brief Clear the nodes children and add the new children Nodes to the Node
	//! \param new_children : the children to add, their depth will be automatically set to depth+1
	inline void reset_children(std::vector<Node> new_children){
		children.clear();
		add_children(new_children);
	}
	//! \fn void reset_children(std::vector<Node> new_children)
	//! \brief Clear the nodes children and add the new children Nodes to the Node
	//! \param new_children : the children to add, their depth will be automatically set to depth+1
	//! \param new_depth : the depth to assign to the children
	inline void reset_children(std::vector<Node> new_children,int new_depth){
		children.clear();
		add_children(new_children,new_depth);
	}


	
};


//! \fn bool operator==(Node n1,Node n2)
//! \brief Function to compare 2 nodes and see if they are identical
inline bool operator==(Node n1,Node n2){
	return (n1.repr==n2.repr) && n1.type == n2.type;
}

//! \fn std::ostream &operator<<(std::ostream &os, Node n)
//! \brief Function insert a Node in a ostream
inline std::ostream &operator<<(std::ostream &os, Node n){
	
	os<<std::string(n.depth,'\t')<<n.repr<<"\n";
	for (Node c : n.children){
		os<<c;
	}
	return os<<"";
}

//! \brief words reserved for the language
std::map<std::string,Node> const KEY_WORDS = {
	{"int64",Node(NodeType::raw_type,"int64")},
	{"return",Node(NodeType::_return,"return")},
};

//! \brief ; ,
std::map<std::string,Node> const DELIMITERS = {
	{";",Node(NodeType::delimiter,";")},
	{",",Node(NodeType::delimiter,",")},
};

//! \brief ( { 
std::map<std::string,Node> const OPENERS = {
	{"(",Node(NodeType::paren,"(")},
	{"{",Node(NodeType::brackets,"{")},
};

//! \brief } )
std::map<std::string,Node> const CLOSERS = {
	{")",Node(NodeType::paren,")")},
	{"}",Node(NodeType::brackets,"}")},
};

//! \brief \+ - * / =
std::map<std::string,Node> const OPERATORS = {
	{"+",Node(NodeType::add_op,"+")},
	{"-",Node(NodeType::add_op,"-")},
	{"*",Node(NodeType::mul_op,"*")},
	{"/",Node(NodeType::mul_op,"/")}, 
	{"=",Node(NodeType::assignment,"=")},
};



#endif