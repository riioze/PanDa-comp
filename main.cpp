#include "lexer.hpp"
#include <iostream>

int main(int argn, char **argc){
    auto tokens = tokenize("int main()\n{\treturn 0;\n}");
    for (auto t : tokens){
        std::cout << t << "\n";
    }
    return 0;
}