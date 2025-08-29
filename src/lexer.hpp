#ifndef PANDA_LEXER_HPP
#define PANDA_LEXER_HPP
#include <iosfwd>
#include <istream>
#include <unordered_set>

#include "node.hpp"
#include "token.hpp"

/**
 * Contains all the C++ keywords
 */
const std::unordered_set<std::string> CPP_KEYWORDS = {
    // C++ Keywords
    "alignas", "alignof", "and", "and_eq", "asm", "auto", "bitand", "bitor",
    "bool", "break", "case", "catch", "char", "char8_t", "char16_t", "char32_t",
    "class", "compl", "concept", "const", "consteval", "constexpr", "const_cast",
    "continue", "co_await", "co_return", "co_yield", "decltype", "default", "delete",
    "do", "double", "dynamic_cast", "else", "enum", "explicit", "export", "extern",
    "false", "float", "for", "friend", "goto", "if", "inline", "int", "long",
    "mutable", "namespace", "new", "noexcept", "not", "not_eq", "nullptr", "operator",
    "or", "or_eq", "private", "protected", "public", "register", "reinterpret_cast",
    "requires", "return", "short", "signed", "sizeof", "static", "static_assert",
    "static_cast", "struct", "switch", "template", "this", "thread_local", "throw",
    "true", "try", "typedef", "typeid", "typename", "union", "unsigned", "using",
    "virtual", "void", "volatile", "wchar_t", "while", "xor", "xor_eq",

    // C++20/C++23 additions
    "import", "module", "constinit", "std"
};

/**
 * @class Lexer
 * @brief Handles the tokenization of the code
 */
class Lexer {
    public:
    explicit Lexer(std::istream *input_code);

    void next_token();
    bool check_token();
    void accept_token();

    private:
    std::istream *input_code;
    int current_line = 0;
    int current_column = 0;

    Token current_token,last_token;
};


#endif //PANDA_LEXER_HPP