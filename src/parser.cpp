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

void raise_missmatched_containers(std::string msg){ // TODO real error message
    std::cerr << "Missmatched parentheses : "<<msg<<std::endl;
    exit(EXIT_FAILURE);
} 

void group_by_containers(std::vector<Node> &node_list){
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
            std::cout<<(*current).repr;
            if (current == node_list.end()){
                raise_missmatched_containers("No closing container corresponds to the opening "+(*opening).repr);
            }
            if (is_opener(*current)){
                opened.push_back((*current).type);
            }
            else if (is_closer(*current)){
                if ((*current).type != opened.back()) raise_missmatched_containers("Opening "+(*opening).repr+" and closing "+(*current).repr +"don't correspond");
                opened.pop_back();
                std::cout<<opened.size();
            }

            current++;
        }
        auto const &closing = current;
        Node grouped((*opening).type,(*opening).repr+(*(closing-1)).repr);
        if ((opening+1)!=(closing-1)) {
            std::vector<Node> to_group(opening+1,closing-1);
            group_by_containers(to_group);
            grouped.children = to_group;
        };        
        std::cout<<grouped;
        node_list.erase(opening,closing);
        node_list.insert(opening,grouped);        
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

    group_by_containers(node_list);

    root.children = node_list;
        
    return root;
}