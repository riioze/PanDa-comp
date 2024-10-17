#include "lexer.hpp"

Token get_token(const std::string &str){


    // check if it is a keyword
    auto i = KEY_WORDS.find(str);
    if (i!=KEY_WORDS.end()){
        return {KEY_WORDS.at(str)};
    }

    // check if it is a lit int
    bool is_int = true;
    for (int i = 0; i<str.length();i++){
        if (!std::isdigit(str.at(i))){
            is_int=false;
            break;
        }
    }
    if (is_int){
        return {TokenType::int_lit,str};
    }

    return {};

    
}

std::vector<Token> tokenize(const std::string &str){
    std::vector<Token> token_list;
    std::string buf;
    for (int i = 0;i < str.length(); i++){
        char c = str.at(i);
        if (std::isalnum(c)){
            buf.push_back(c);
        }
        else if (buf!=""){
            Token t = get_token(buf);
            token_list.push_back(t);
            buf.clear();
        }
        if (c==';'){
            token_list.push_back({TokenType::semi});
        }
    }
    return token_list;
}