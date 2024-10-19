#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <optional>
#include <map>
#include <vector>
#include <iostream>


enum class NodeType{

    // only one (basically the root)
    program,

    //types full type is a node with at list a raw type + eventualy consts ect
    full_type,
    raw_type,

    //mainly variable/function/class name
    identifier,

    //expression things
    expression,
    operation,
    declaration,
    assignment,
    literal,

    // function things
    function,
    function_sign,
    function_params,
    function_body,
    _return,

    //delimiters
    delimiter, // ; ,
    paren, // (, ) and ()
    brackets, // {, } and {}
};

struct Node {
    NodeType type;
    std::string repr;
    std::vector<Node> children;
    Node(NodeType node, std::string repr) : type(type), repr(repr) {}
    
};

inline bool operator==(Node n1,Node n2){
    return (n1.repr==n2.repr); //FIXME doesnt work when comparing type 
}

inline std::ostream &operator<<(std::ostream &os, Node n){
    os<<n.repr;
    for (Node c : n.children){
        os<<c;
    }
    return os<<std::endl;
}


std::map<std::string,Node> const KEY_WORDS = {
    {"int64",Node(NodeType::raw_type,"int64")},
    {"return",Node(NodeType::_return,"return")},
};

std::map<std::string,Node> const DELIMITERS = {
    {";",Node(NodeType::delimiter,";")},
    {",",Node(NodeType::delimiter,";")},
};

std::map<std::string,Node> const OPENERS = {
    {"(",Node(NodeType::paren,"(")},
    {"{",Node(NodeType::brackets,"{")},
};

std::map<std::string,Node> const CLOSERS = {
    {")",Node(NodeType::paren,")")},
    {"}",Node(NodeType::brackets,"}")},
};

std::map<std::string,Node> const OPERATORS = {
    {"+",Node(NodeType::operation,"+")},
    {"-",Node(NodeType::operation,"-")},
    {"*",Node(NodeType::operation,"*")},
    {"/",Node(NodeType::operation,"/")},    
};

#endif