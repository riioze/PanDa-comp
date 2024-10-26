#include "parser.hpp"

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

void raise_missmatched_containers(std::string msg){ // TODO real error message
    std::cerr << "Missmatched parentheses : "<<msg<<std::endl;
    exit(EXIT_FAILURE);
} 

void group_by_containers(Node &node){
    auto &node_list = node.children;
    while (1){        
        auto opening = std::find_if(node_list.begin(),node_list.end(),is_opener);
        if(opening == node_list.end()){
            auto closing = std::find_if(node_list.begin(),node_list.end(),is_closer);
            if (closing != node_list.end()) { // if there are still closing parens but no opening parens
                raise_missmatched_containers("No opening container corresponds to the closing "+(*closing).repr);
            }
            return;
        }
        std::vector<NodeType> opened = {(*opening).type}; //store the type of all opened brackets
        auto current = opening+1;
        while (opened.size()>0){
            if (current == node_list.end()){
                raise_missmatched_containers("No closing container corresponds to the opening "+(*opening).repr);
            }
            if (is_opener(*current)){
                opened.push_back((*current).type);
            }
            else if (is_closer(*current)){
                if ((*current).type != opened.back()) raise_missmatched_containers("Opening "+(*opening).repr+" and closing "+(*current).repr +"don't correspond");
                opened.pop_back();
            }

            current++;
        }
        auto const &closing = current;
        Node grouped((*opening).type,(*opening).repr+(*(closing-1)).repr);
        if ((opening+1)!=(closing-1)) {
            std::vector<Node> to_group(opening+1,closing-1);
            
            grouped.children = get_parse_tree(to_group).children;
        };
        node_list.erase(opening,closing);
        node_list.insert(opening,grouped);        
    }
}


void group_operators(Node &node){ //TODO detect unary operators
    auto &node_list = node.children;
    if (node.children.size() == 0) return;
    auto mul_it = std::find_if(node_list.begin(),node_list.end(),is_empty_mul);
    while (mul_it != node_list.end()){
        
        Node mul_op = (*mul_it);
        mul_op.children = {*(mul_it-1),*(mul_it+1)};
        node_list.erase(mul_it-1,mul_it+2);
        node_list.insert(mul_it-1,mul_op);
        
        mul_op.add_depth();

        mul_it = std::find_if(node_list.begin(),node_list.end(),is_empty_mul);
    }

    auto add_it = std::find_if(node_list.begin(),node_list.end(),is_empty_add);
    while (add_it != node_list.end()){
        Node add_op = (*add_it);
        add_op.children = {*(add_it-1),*(add_it+1)};
   
        node_list.erase(add_it-1,add_it+2);
        
        node_list.insert(add_it-1,add_op);


        add_it = std::find_if(node_list.begin(),node_list.end(),is_empty_add);
    }

    
}

Node get_parse_tree(std::vector<Node> node_list){
    Node root(NodeType::program,"root");
    

    //Create Full type Nodes
    for (int i=0;i<node_list.size();i++){
        if (node_list[i].type == NodeType::raw_type){ // TODO make more complexe full types
            Node new_node = Node(NodeType::full_type,node_list[i].repr);
            new_node.children.push_back(node_list[i]);
            node_list[i] = new_node;
        }
    }
    root.children = node_list;
    group_by_containers(root);

    

    group_operators(root);

    return root;
}