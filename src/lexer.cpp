#include "lexer.hpp"

Node get_node(const std::string &str){


    // check if it is a keyword
    auto i = KEY_WORDS.find(str);
    if (i!=KEY_WORDS.end()){
        return KEY_WORDS.at(str);
    }

    // check if it is a lit int
    bool is_int = true;
    for (int i = 0; i<str.length();i++){
        if (!std::isdigit(str.at(i))){
            is_int=false;
            break;
        }
    }
    if (is_int){
        return Node(NodeType::literal,str);
    }

    return Node(NodeType::identifier, str);

    
}

std::vector<Node> tokenize(std::string const &str){
    std::vector<Node> node_list;
    std::string buf;
    for (int i = 0;i < str.length(); i++){
        char c = str.at(i);
        std::string c_str(1,c);
        if (std::isalnum(c)){
            buf.push_back(c);
        }
        else if (buf!=""){
            Node n = get_node(buf);
            node_list.push_back(n);
            buf.clear();
        }
        if (c=='='){ //TODO deal with == <= ect
            node_list.push_back(Node(NodeType::assignment, "="));
        }
        
        //check if it is an operator
        auto fo = OPERATORS.find(c_str);
        if (fo!=OPERATORS.end()){
            node_list.push_back(OPERATORS.at(c_str));
        }

        //check if it is a delimiter
        auto fd = DELIMITERS.find(c_str);
        if (fd!=DELIMITERS.end()){
            node_list.push_back(DELIMITERS.at(c_str));
        }

        //check if it is a container 
        auto fop = OPENERS.find(c_str);
        if (fop!=OPENERS.end()){
            node_list.push_back(OPENERS.at(c_str));
        }    
        auto fc = CLOSERS.find(c_str);
        if (fc!=CLOSERS.end()){
            node_list.push_back(CLOSERS.at(c_str));
        }
    }
    return node_list;
}