#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "codeoptimizer.hpp"
#include "include/lexer.hpp"
#include "include/parser.hpp"

int main(int argc, char **argv){
    if (argc == 1) {
        std::cerr << "missing .pd input file" << std::endl;
        return EXIT_FAILURE;
    }


    // Read the Input file
    std::fstream input_file(argv[1], std::ios::in);
    if (!input_file){
        std::cerr << "Can't open input file" << std::endl;
        return EXIT_FAILURE;
    }
    std::stringstream content_stream;
    content_stream << input_file.rdbuf();
    input_file.close();
	std::istringstream input_stream(content_stream.str());


	CodeOptimizer codeOptimizer(std::move(input_stream));

	std::vector<std::string> code;

	do {
		code = codeOptimizer.generate_code();
		for (const auto& line : code) {
			std::cout << line << std::endl;
		}
	} while (!code.empty());



    return EXIT_SUCCESS;
}