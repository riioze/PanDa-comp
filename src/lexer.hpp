#ifndef PANDA_LEXER_HPP
#define PANDA_LEXER_HPP
#include <iosfwd>
#include <sstream>
#include <unordered_set>

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

	// Preprocessor Directives (treated as keywords)
	"define", "undef", "include", "ifdef", "ifndef", "if", "else", "elif", "endif",
	"line", "error", "pragma",

	// C++20/C++23 additions
	"import", "module", "constinit", "std"
};

/**
 * @class Lexer
 * @brief Handles the tokenization of the code
 */
class Lexer {
    public:
	explicit Lexer(std::string& input_string) :
	input_code(input_string), current_line(0), current_column(0), current_token(TokenType::start_of_input, -1, -1),
	last_token(TokenType::start_of_input, -1, -1) {}
	Token current_token,last_token;

    char consume_character();
    void next_token();
    bool check_token(TokenType expected);
    void accept_token(TokenType expected);
	bool check_token(std::vector<TokenType> expected);

    private:
    std::istringstream input_code;
    int current_line = 0;
    int current_column = 0;


    void set_current_token(TokenType token_type, const std::string &representation);
};


#endif //PANDA_LEXER_HPP