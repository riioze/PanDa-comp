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

std::vector<Node>::iterator go_to_closing(std::vector<Node>::iterator opening,std::vector<Node>::iterator end){
	std::map<NodeType,int> counts = {};

	counts[opening->type]++;
	std::vector<Node>::iterator it;
	for (it = opening+1; it != end; it++){
		if (is_opener(*it)){
			counts[it->type]++;
		} else if (is_closer(*it)){
			counts[it->type]--;
			if (counts[opening->type]==0){
				return it;
			}
		}
	}
	return it;

}

void group_by_containers(Node &node){

	std::vector<Node> grouped_children = {};

	grouped_children.reserve(node.children.size());

	auto it = node.children.begin();

	while (it<node.children.end()){
		auto current = *it;

		if (is_opener(current)){
			auto opening = it;
			auto closing = go_to_closing(opening,node.children.end());
			if (closing == node.children.end()){
				raise_missmatched_containers("opening "+ current.repr+ " without corresponding closing one");
			} else {
				std::string repr = opening->repr+closing->repr;
				NodeType type = opening->type;
				std::vector<Node> children = std::vector(opening+1,closing);
				Node grouped(type,repr);
				grouped.depth = node.depth+1;
				grouped.add_children(children);
				group_by_containers(grouped);
				grouped_children.push_back(grouped);
				it = closing;
			}
		} else if (is_closer(current)){
			raise_missmatched_containers("closing " + current.repr + " before an opening one");
		} else {
			grouped_children.push_back(current);
		}

		it++;
	}

	node.reset_children(grouped_children);
	
}


void group_operators(Node &node){ //TODO detect unary operators

}



void get_parse_tree(Node &root, std::vector<Node> node_list){
	root.add_children(node_list);

	group_by_containers(root);

}