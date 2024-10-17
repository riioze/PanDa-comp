#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <optional>
#include <map>

enum class TokenType{
    _return,
    int_lit,
    semi
};

std::map<std::string,TokenType> const KEY_WORDS = {
    {"return",TokenType::_return}
};

struct Token
{
    TokenType type;
    std::optional<std::string> value;

    std::string to_string(){
        if (value) return value.value();
        
        if (type == TokenType::_return)return "return";
        return ";";
        
    }
};


#endif