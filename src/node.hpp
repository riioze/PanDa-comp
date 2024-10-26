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
    mul_op,
    add_op,
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
    int depth;
    Node(NodeType type, std::string repr) : type(type), repr(repr) ,children(),depth(0){}
    Node(NodeType type, std::string repr,int depth) : type(type), repr(repr) ,children(), depth(depth){}
    inline void add_depth(bool from_children = false){
        depth++;
        for (auto &c:children){
            c.add_depth();
        }
    }
    
};



inline bool operator==(Node n1,Node n2){
    return (n1.repr==n2.repr); //FIXME doesnt work when comparing type 
}

inline std::ostream &operator<<(std::ostream &os, Node n){
    
    os<<std::string(n.depth,'\t')<<n.repr<<"\n";
    for (Node c : n.children){
        os<<c;
    }
    return os<<"";
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
    {"+",Node(NodeType::add_op,"+")},
    {"-",Node(NodeType::add_op,"-")},
    {"*",Node(NodeType::mul_op,"*")},
    {"/",Node(NodeType::mul_op,"/")}, 
    {"=",Node(NodeType::assignment,"=")},
};

#endif