#ifndef PANDA_TOKEN_HPP
#define PANDA_TOKEN_HPP
#include <string>


enum TokenType {
    start_of_input,

    // Literals
    integer_literal,
    floating_literal,
    character_literal,
    string_literal,
    boolean_literal,

    // Identifiers and Keywords
    identifier,
    keyword,

    // Operators
    plus,
    minus,
    star,
    slash,
    percent,
    double_plus,
    double_minus,
    equal,
    double_equal,
    not_equal,
    greater_than,
    less_than,
    greater_than_or_equal,
    less_than_or_equal,
    ampersand,
    pipe,
    hat,
    left_shift,
    right_shift,
    ones_complement,
    logical_and,
    logical_or,
    logical_not,

    // Assignment Operators
    plus_assign,
    minus_assign,
    star_assign,
    slash_assign,
    ampersand_assign,
    pipe_assign,
    hat_assign,
    left_shift_assign,
    right_shift_assign,

    // Punctuation
    left_paren,
    right_paren,
    left_brace,
    right_brace,
    left_bracket,
    right_bracket,
    semicolon,
    comma,
    colon,
    question_mark,
    dot,
    arrow,
    dot_star,
    arrow_star,
    scope_resolution,

    // Preprocessor
    preprocessor,

    // End of File
    eof,
};


class Token {
    public:
    Token(TokenType,int,int);
    Token(TokenType,int,int, const std::string &);

    private:
    TokenType type;
    int line, column;

    std::string representation;
};


#endif //PANDA_TOKEN_HPP