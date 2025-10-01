#ifndef PANDA_TREEOPTIMIZER_HPP
#define PANDA_TREEOPTIMIZER_HPP

#include "parser.hpp"

class TreeOptimizer {
public:
	explicit TreeOptimizer(std::ifstream && input_stream) : parser(std::move(input_stream)) {};

	Node get_next_tree();
private:
	Parser parser;
};


#endif // PANDA_TREEOPTIMIZER_HPP
