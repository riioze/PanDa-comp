//
// Created by User on 29/09/2025.
//

#include "codegenerator.hpp"


std::vector<std::string> CodeGenerator::generate_code() {

	Node tree = treeOptimizer.get_next_tree();
	if (tree.type == NodeType::eof) {
		return {};
	}

	std::vector<std::string> lines{};
	generate_node(tree, lines);
	return lines;
}

void CodeGenerator::generate_node(const Node &node, std::vector<std::string> &lines) {

	auto nodeType = node.type;
	if (EASY_NODES.contains(nodeType)) {
		const auto& gen = EASY_NODES.at(nodeType);

		if (!gen.first.empty()) {
			lines.push_back(gen.first);
		}
		for (const auto& child : node.children) {
			generate_node(child, lines);
		}
		if (!gen.second.empty()) {
			lines.push_back(gen.second);
		}
		return;
	}

	switch (nodeType) {

		default:
			throw std::runtime_error("Invalid node type");
	}
}


