#include "lexer.hpp"
#include <iostream>
#include <fstream>

int main(int argc, char **argv){

    if (argc < 2) {
        std::cerr << "No input file\n";
        return 1;
    }

    std::string input_name = argv[1];
    //std::string output_name = argv[2];
    
    std::ifstream input_file(input_name);
    std::string program = "";
    if (!input_file.is_open()){
        std::cerr << "Unable to open file : " << input_name << "\n";
        return 1;
    }

    while(input_file){
        char c = input_file.get();
        program+=c;
    }


    auto tokens = tokenize(program);
    for (auto t : tokens){
        std::cout << t << "\n";
    }
    return 0;
}