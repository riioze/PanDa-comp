#ifndef PANDA_CODEGENERATOR_HPP
#define PANDA_CODEGENERATOR_HPP
#include "treeoptimizer.hpp"


class CodeGenerator {
public:
	explicit CodeGenerator(std::istringstream && input_stream) : treeOptimizer(std::move(input_stream)) {

	};
	std::vector<std::string> generate_code();
private:
	TreeOptimizer treeOptimizer;

};


#endif // PANDA_CODEGENERATOR_HPP
