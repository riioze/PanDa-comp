#include "include/parser.hpp"

int find_last(std::vector<Node> const node_list,Node n){
    for (int i=node_list.size()-1;i>=0;i--){
        if (node_list.at(i) == n){
            return i;
        }
    }
    return -1;
}

bool is_opener(Node n){
    auto f = OPENERS.find(n.repr);
    return f!=OPENERS.end();
}

bool is_closer(Node n){
    auto f = CLOSERS.find(n.repr);
    return f!=CLOSERS.end();
}

bool is_empty_mul(Node &n){
    return n.type == NodeType::mul_op && n.children.size()==0;
}

bool is_empty_add(Node n){
    return n.type == NodeType::add_op && n.children.size()==0;
}

bool is_expression_end(Node n){
    return n.repr == ";" || n.repr == "{}";
}

void raise_missmatched_containers(std::string msg){ // TODO real error message
    std::cerr << "Missmatched parentheses : "<<msg<<std::endl;
    exit(EXIT_FAILURE);
} 

Node get_container_node(std::vector<Node> node_list, NodeType type, std::string repr){
    Node container = Node(type,repr);

    return container;
}

void group_by_containers(Node &node){

}


void group_operators(Node &node){ //TODO detect unary operators


    
}



Node get_parse_tree(std::vector<Node> node_list){
    Node root(NodeType::program,"root");



    return root;
}