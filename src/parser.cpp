#include "include/parser.hpp"

int find_last(const std::vector<Node>& node_list, Node n){
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

void raise_missmatched_containers(const std::string& msg){ // TODO real error message
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

std::vector<std::vector<Node>> cut_by_delimiters(std::vector<Node> nodes){
	std::vector<std::vector<Node>> result;
	std::vector<Node> currentChunk;

	for (const auto& node : nodes) {
		if (node.type == NodeType::delimiter) {
			if (!currentChunk.empty()) {  // Avoid empty chunks
				result.push_back(std::move(currentChunk));
				currentChunk.clear();

			}
		} else if (node.type == NodeType::brackets){
			if (!currentChunk.empty()) {  // Avoid empty chunks
				currentChunk.push_back(node);
				result.push_back(std::move(currentChunk));
				currentChunk.clear();
			}
		} else {
			currentChunk.push_back(node);
		}
	}

	// Push last chunk if not empty
	if (!currentChunk.empty()) {
		result.push_back(std::move(currentChunk));
	}

	return result;
}

std::vector<Node>::iterator find_lowest_priority_node(std::vector<Node>& nodes) {
	return std::min_element(nodes.begin(), nodes.end(), [](const Node& a, const Node& b) {
		auto itA = nodeTypeToPriority.find(a.type);
		auto itB = nodeTypeToPriority.find(b.type);
		
		// If `a` is not in the map, assume maximum priority
		OpPriority priorityA = (itA != nodeTypeToPriority.end()) ? itA->second : OpPriority::highest;
		OpPriority priorityB = (itB != nodeTypeToPriority.end()) ? itB->second : OpPriority::highest;

		return priorityA < priorityB;  // Lower priority value means lower precedence
	});
}

Node get_grouped_expression(std::vector<Node> nodes){
	if (nodes.size() == 1) { // arrived at a leaf
		auto node = nodes[0];
		if (node.type == NodeType::paren){
			return get_grouped_expression(node.children);
		} else {
			return node;
		}
	}
	auto it = find_lowest_priority_node(nodes);
	if (it == nodes.end()){ // error for now
		std::cerr<<"multiple nodes w/out priority"<<std::endl;
		for (auto node:nodes){
			std::cerr<<node<<std::endl;
		}
		exit(EXIT_FAILURE);
	}
	auto instruction_node = *it;

	if (it == nodes.begin()){ // left unitary op
		instruction_node.add_child(get_grouped_expression(std::vector(it+1,nodes.end())));
	} else if (it == nodes.end()-1) { // right unitary op
		instruction_node.add_child(get_grouped_expression(std::vector(nodes.begin(),it)));
	} else {
		instruction_node.add_child(get_grouped_expression(std::vector(nodes.begin(),it)));
		instruction_node.add_child(get_grouped_expression(std::vector(it+1,nodes.end())));
	}

	return instruction_node;
}

void group_instructions(Node &node){
	std::vector<Node> grouped = {};

	for (auto instruction : cut_by_delimiters(node.children)){
		if (instruction.empty()) continue; // skip empty instructions

		if (instruction.size() == 4 && instruction[0].type == NodeType::raw_type && instruction[1].type == NodeType::identifier && instruction[2].type == NodeType::paren && instruction[3].type == NodeType::brackets){
			Node instruction_node = Node(NodeType::function,instruction[1].repr,node.depth+1);
			Node sign = Node(NodeType::function_sign, "sign");
			sign.add_children(std::vector(instruction.begin(),instruction.end()-1)); // TODO: function params
			instruction_node.add_child(sign);
			Node body = Node(NodeType::function_body,"body");
			body.add_children(instruction[3].children);
			group_instructions(body);
			instruction_node.add_child(body);
			grouped.push_back(instruction_node);
		}

		else {
			Node instruction_node = get_grouped_expression(instruction);
			grouped.push_back(instruction_node);
		}

		
	}
	node.reset_children(grouped);
}



void get_parse_tree(Node &root, const std::vector<Node>& node_list){ //TODO: group types
	root.add_children(node_list);

	group_by_containers(root);

	group_instructions(root);

}