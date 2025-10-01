#ifndef PANDA_CODEGENERATOR_HPP
#define PANDA_CODEGENERATOR_HPP
#include "treeoptimizer.hpp"

const std::map<NodeType,std::pair<std::string,std::string>> EASY_NODES = {
	// BINARY OPS

	{NodeType::logical_or, {"","or"}},
	{NodeType::logical_and, {"","and"}},
	{NodeType::double_equal, {"","cmpeq"}},
	{NodeType::not_equal, {"","cmpne"}},
	{NodeType::greater_than_or_equal, {"","cmpge"}},
	{NodeType::less_than_or_equal, {"","cmple"}},
	{NodeType::greater_than, {"","cmpgt"}},
	{NodeType::less_than, {"","cmplt"}},
	{NodeType::binary_addition, {"","add"}},
	{NodeType::binary_subtraction, {"","sub"}},
	{NodeType::binary_multiplication, {"","mult"}},
	{NodeType::binary_division, {"","div"}},
	{NodeType::binary_modulo, {"","mod"}},


	// UNARY OPS

	{NodeType::logical_not, {"","not"}},
	{NodeType::prefix_plus, {"push 0","add"}},
	{NodeType::prefix_plus, {"push 0","sub"}},


	// INSTRUCTIONS

	{NodeType::debug, {"","dbg"}},
	{NodeType::drop, {"","or"}}, // TODO : remove it when necessary
};

class CodeGenerator {
public:
	explicit CodeGenerator(std::ifstream && input_stream) : treeOptimizer(std::move(input_stream)) {

	};
	std::vector<std::string> generate_code();
	void generate_node(const Node &node, std::vector<std::string> &lines);
private:
	TreeOptimizer treeOptimizer;

};


#endif // PANDA_CODEGENERATOR_HPP
