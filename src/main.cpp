#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
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
    std::string content;
    content = content_stream.str();


    auto tokens = tokenize(content);


    Node root = Node(NodeType::program,"root");
    
    get_parse_tree(root,tokens);

    std::cout << root << std::endl;

    return EXIT_SUCCESS;
}