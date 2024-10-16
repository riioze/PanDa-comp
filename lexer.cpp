#include "lexer.hpp"



std::vector<std::string> tokenize(std::string program){
    std::regex const REGEX("\\{|\\}|\\(|\\)|;|[a-zA-Z]\\w*|[0-9]+|\\=\\=|\\=|\\+|\\*|-|\\/");
    std::sregex_iterator tokens_begin(program.begin(),program.end(),REGEX);
    std::sregex_iterator token_end = std::sregex_iterator();

    std::vector<std::string> tokens = {};

    for (auto i = tokens_begin; i!=token_end;i++){
        auto token = *i;

        tokens.push_back(token.str());
    }
    return tokens;
}


