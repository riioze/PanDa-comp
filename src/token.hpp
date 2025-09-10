#ifndef PANDA_TOKEN_HPP
#define PANDA_TOKEN_HPP
#include <string>
#include <utility>
#include <vector>

/**
 * @enum TokenType
 * @brief enum of all the types possible for <code>Token</code>
 */
enum class TokenType {

	start_of_input,                    // Start of input marker

	// Literals
	integer_literal,                   // e.g., 42
	floating_literal,                  // e.g., 3.14
	character_literal,                 // e.g., 'a'
	string_literal,                    // e.g., "hello"
	boolean_literal,                   // e.g., true or false

	// Identifiers and Keywords
	identifier,                        // e.g., myVariable
	keyword,                           // e.g., if, else, while

	// Operators
	plus,                              // e.g., +
	minus,                             // e.g., -
	star,                              // e.g., *
	slash,                             // e.g., /
	percent,                           // e.g., %
	double_plus,                       // e.g., ++
	double_minus,                      // e.g., --
	equal,                             // e.g., =
	double_equal,                      // e.g., ==
	not_equal,                         // e.g., !=
	greater_than,                      // e.g., >
	less_than,                         // e.g., <
	greater_than_or_equal,             // e.g., >=
	less_than_or_equal,                // e.g., <=
	ampersand,                         // e.g., &
	pipe,                              // e.g., |
	hat,                               // e.g., ^
	left_shift,                        // e.g., <<
	right_shift,                       // e.g., >>
	bitwise_not,                       // e.g., ~
	logical_and,                       // e.g., &&
	logical_or,                        // e.g., ||
	logical_not,                       // e.g., !

	// Assignment Operators
	plus_assign,                       // e.g., +=
	minus_assign,                      // e.g., -=
	star_assign,                       // e.g., *=
	slash_assign,                      // e.g., /=
	percent_assign,                    // e.g., %=
	ampersand_assign,                  // e.g., &=
	pipe_assign,                       // e.g., |=
	hat_assign,                        // e.g., ^=
	left_shift_assign,                 // e.g., <<=
	right_shift_assign,                // e.g., >>=

	// Punctuation
	left_paren,                        // e.g., (
	right_paren,                       // e.g., )
	left_brace,                        // e.g., {
	right_brace,                       // e.g., }
	left_bracket,                      // e.g., [
	right_bracket,                     // e.g., ]
	semicolon,                         // e.g., ;
	comma,                             // e.g., ,
	colon,                             // e.g., :
	question_mark,                     // e.g., ?
	dot,                               // e.g., .
	arrow,                             // e.g., ->
	dot_star,                          // e.g., .*
	arrow_star,                        // e.g., ->*
	scope_resolution,                  // e.g., ::
	hash,                              // e.g., #

	// End of File
	eof,                               // End of file marker
};

inline std::vector<TokenType> LITERALS = {
	TokenType::integer_literal,                   // e.g., 42
	TokenType::floating_literal,                  // e.g., 3.14
	TokenType::character_literal,                 // e.g., 'a'
	TokenType::string_literal,                    // e.g., "hello"
	TokenType::boolean_literal,
};

inline std::vector<TokenType> PREFIXES = {
	TokenType::double_plus,
	TokenType::double_minus,
	TokenType::plus,
	TokenType::minus,
	TokenType::bitwise_not,
	TokenType::logical_not,
	TokenType::star,
	TokenType::ampersand
};

struct Token {
    public:
    Token(TokenType token_type,int line,int column) : token_type(token_type), line(line), column(column) {}
	Token(TokenType token_type,int line,int column, std::string  representation) : token_type(token_type), line(line), column(column), representation(std::move(representation)) {}

    TokenType token_type;
    int line, column;

    std::string representation;
};


#endif //PANDA_TOKEN_HPP