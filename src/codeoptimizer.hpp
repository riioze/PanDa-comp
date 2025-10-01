#ifndef PANDA_CODEOPTIMIZER_HPP
#define PANDA_CODEOPTIMIZER_HPP
#include <fstream>


#include "codegenerator.hpp"


class CodeOptimizer {
public:
	explicit CodeOptimizer(std::ifstream input_stream) : codeGenerator(std::move(input_stream)){}
	std::vector<std::string> generate_code();
private:
	CodeGenerator codeGenerator;
};


#endif // PANDA_CODEOPTIMIZER_HPP
