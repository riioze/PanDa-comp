#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <optional>
#include <map>
#include <vector>
#include <iostream>

/**
 * @file node.hpp
 * @brief Defines the structures and functions related to the AST nodes.
 */


/**
 * @enum NodeType
 * @brief Enumerates all possible types of nodes in the AST.
 */
enum class NodeType {
	program,            ///< The root node of the AST.
	full_type,          ///< Contains full type information (e.g., `int* const`).
	raw_type,           ///< Represents a basic type (e.g., `int`, `char`, or user-defined types).
	identifier,         ///< Represents variable, function, or class names.
	expression,         ///< Represents a complete expression.

	// Arithmetic Operators
	mul_op,             ///< `*` multiplication operator.
	div_op,             ///< `/` division operator.
	mod_op,             ///< `%` modulus operator.
	add_op,             ///< `+` addition operator.
	sub_op,             ///< `-` subtraction operator.

	// Bitwise Operators
	bitwise_and_op,     ///< `&` bitwise AND.
	bitwise_or_op,      ///< `|` bitwise OR.
	bitwise_xor_op,     ///< `^` bitwise XOR.
	shift_left_op,      ///< `<<` left shift.
	shift_right_op,     ///< `>>` right shift.

	// Logical Operators
	logical_and_op,     ///< `&&` logical AND.
	logical_or_op,      ///< `||` logical OR.
	logical_not_op,     ///< `!` logical NOT.

	// Comparison Operators
	eq_op,             ///< `==` equality operator.
	neq_op,            ///< `!=` inequality operator.
	lt_op,             ///< `<` less than.
	gt_op,             ///< `>` greater than.
	le_op,             ///< `<=` less than or equal.
	ge_op,             ///< `>=` greater than or equal.

	// Unary Operators
	unary_plus,        ///< `+` unary plus.
	unary_minus,       ///< `-` unary minus.
	address_of,        ///< `&` address-of operator.
	dereference,       ///< `*` dereference operator.

	// Assignment Operators
	assignment,        ///< `=` assignment.
	add_assign,        ///< `+=` addition assignment.
	sub_assign,        ///< `-=` subtraction assignment.
	mul_assign,        ///< `*=` multiplication assignment.
	div_assign,        ///< `/=` division assignment.
	mod_assign,        ///< `%=` modulus assignment.
	and_assign,        ///< `&=` bitwise AND assignment.
	or_assign,         ///< `|=` bitwise OR assignment.
	xor_assign,        ///< `^=` bitwise XOR assignment.
	shl_assign,        ///< `<<=` left shift assignment.
	shr_assign,        ///< `>>=` right shift assignment.

	// Other Statements
	literal,
	declaration,        ///< Represents a declaration (`full_type identifier;`).
	initialisation,     ///< Represents an initialization (`full_type identifier = value;`).
	function,           ///< Represents an entire function.
	function_sign,      ///< Represents a function signature (name and parameters).
	function_params,    ///< Represents function parameters.
	function_body,      ///< Represents the function body.
	_return,           ///< Represents a return statement.

	// Delimiters and Parentheses
	delimiter,         ///< Represents a delimiter (`;`, `,`).
	paren,            ///< Represents parentheses `()`.
	brackets          ///< Represents curly brackets `{}`.
};
 

/**
 * @enum OpPriority
 * @brief Represents operator precedence levels in an expression parser.
 * 
 * This enumeration defines the precedence of different categories of operators.
 * Higher values correspond to higher precedence.
 */
enum class OpPriority {
	lowest,       ///< Lowest priority (e.g., assignment operators)
	logical_or,   ///< Logical OR (||)
	logical_and,  ///< Logical AND (&&)
	bitwise_or,   ///< Bitwise OR (|)
	bitwise_xor,  ///< Bitwise XOR (^)
	bitwise_and,  ///< Bitwise AND (&)
	equality,     ///< Equality and inequality (==, !=)
	relational,   ///< Relational operators (<, >, <=, >=)
	shift,        ///< Bitwise shift (<<, >>)
	adding_op,    ///< Addition and subtraction (+, -)
	mult_op,      ///< Multiplication, division, and modulus (*, /, %)
	unary,        ///< Unary operators (!, ~, ++, --, - (negation))
	call,         ///< Function calls, array subscripting, member access ((), [], ., ->)
	highest       ///< Highest priority (e.g., scope resolution ::)
};

/**
 * @brief Maps operator priority levels to corresponding AST node types.
 */
const std::map<OpPriority, std::vector<NodeType>> priorityToNodeTypes = {
	{OpPriority::lowest, {NodeType::assignment, NodeType::add_assign, NodeType::sub_assign, NodeType::mul_assign, NodeType::div_assign, NodeType::mod_assign, NodeType::and_assign, NodeType::or_assign, NodeType::xor_assign, NodeType::shl_assign, NodeType::shr_assign}},

	{OpPriority::logical_or, {NodeType::logical_or_op}},
	{OpPriority::logical_and, {NodeType::logical_and_op}},
	
	{OpPriority::bitwise_or, {NodeType::bitwise_or_op}},
	{OpPriority::bitwise_xor, {NodeType::bitwise_xor_op}},
	{OpPriority::bitwise_and, {NodeType::bitwise_and_op}},

	{OpPriority::equality, {NodeType::eq_op, NodeType::neq_op}},
	{OpPriority::relational, {NodeType::lt_op, NodeType::gt_op, NodeType::le_op, NodeType::ge_op}},

	{OpPriority::shift, {NodeType::shift_left_op, NodeType::shift_right_op}},

	{OpPriority::adding_op, {NodeType::add_op, NodeType::sub_op}},
	{OpPriority::mult_op, {NodeType::mul_op, NodeType::div_op, NodeType::mod_op}},

	{OpPriority::unary, {NodeType::unary_plus, NodeType::unary_minus, NodeType::logical_not_op, NodeType::address_of, NodeType::dereference}},

	{OpPriority::call, {NodeType::paren, NodeType::brackets}},

	{OpPriority::highest, {}} // Reserved for highest-priority operations like `::`
};

const std::map<NodeType, OpPriority> nodeTypeToPriority = {
    {NodeType::assignment, OpPriority::lowest},
    {NodeType::add_assign, OpPriority::lowest}, {NodeType::sub_assign, OpPriority::lowest},
    {NodeType::mul_assign, OpPriority::lowest}, {NodeType::div_assign, OpPriority::lowest},
    {NodeType::mod_assign, OpPriority::lowest}, {NodeType::and_assign, OpPriority::lowest},
    {NodeType::or_assign, OpPriority::lowest}, {NodeType::xor_assign, OpPriority::lowest},
    {NodeType::shl_assign, OpPriority::lowest}, {NodeType::shr_assign, OpPriority::lowest},

    {NodeType::logical_or_op, OpPriority::logical_or},
    {NodeType::logical_and_op, OpPriority::logical_and},

    {NodeType::bitwise_or_op, OpPriority::bitwise_or},
    {NodeType::bitwise_xor_op, OpPriority::bitwise_xor},
    {NodeType::bitwise_and_op, OpPriority::bitwise_and},

    {NodeType::eq_op, OpPriority::equality}, {NodeType::neq_op, OpPriority::equality},
    {NodeType::lt_op, OpPriority::relational}, {NodeType::gt_op, OpPriority::relational},
    {NodeType::le_op, OpPriority::relational}, {NodeType::ge_op, OpPriority::relational},

    {NodeType::shift_left_op, OpPriority::shift}, {NodeType::shift_right_op, OpPriority::shift},

    {NodeType::add_op, OpPriority::adding_op}, {NodeType::sub_op, OpPriority::adding_op},

    {NodeType::mul_op, OpPriority::mult_op}, {NodeType::div_op, OpPriority::mult_op}, {NodeType::mod_op, OpPriority::mult_op},

    {NodeType::unary_plus, OpPriority::unary}, {NodeType::unary_minus, OpPriority::unary},
    {NodeType::logical_not_op, OpPriority::unary}, {NodeType::address_of, OpPriority::unary},
    {NodeType::dereference, OpPriority::unary},

    {NodeType::paren, OpPriority::call}, {NodeType::brackets, OpPriority::call}
};



/**
 * @struct Node
 * @brief Represents a recursive structure forming the AST.
 */
struct Node {
    NodeType type;                 ///< The type of the node.
    std::string repr;              ///< String representation (mainly for debugging).
    std::vector<Node> children;    ///< List of child nodes (e.g., `x` and `y` are children of `x + y`).
    int depth;                     ///< Depth level in the AST.

    /**
     * @brief Constructs a node without specifying depth.
     * @param type The type of the node.
     * @param repr The string representation.
     */
    Node(NodeType type, std::string repr) : type(type), repr(repr), children(), depth(0) {}

    /**
     * @brief Constructs a node with a specified depth.
     * @param type The type of the node.
     * @param repr The string representation.
     * @param depth The depth in the AST.
     */
    Node(NodeType type, std::string repr, int depth) : type(type), repr(repr), children(), depth(depth) {}

    /**
     * @brief Sets the depth of the node and recursively updates the depth of its children.
     * @param depth The new depth.
     */
    inline void set_depth(int depth) {
        this->depth = depth;
        for (auto& c : children) {
            c.set_depth(depth + 1);
        }
    }

    /**
     * @brief Adds a child node and automatically sets its depth.
     * @param child The child node to add.
     */
    inline void add_child(Node child) {
        child.set_depth(this->depth + 1);
        children.push_back(child);
    }

    /**
     * @brief Adds a child node with a specified depth.
     * @param child The child node to add.
     * @param new_depth The depth to assign to the child.
     */
    inline void add_child(Node child, int new_depth) {
        child.set_depth(new_depth);
        children.push_back(child);
    }

    /**
     * @brief Adds multiple child nodes and automatically sets their depth.
     * @param new_children The child nodes to add.
     */
    inline void add_children(const std::vector<Node>& new_children) {
        for (Node child : new_children) {
            add_child(child);
        }
    }

    /**
     * @brief Adds multiple child nodes with a specified depth.
     * @param new_children The child nodes to add.
     * @param new_depth The depth to assign to the children.
     */
    inline void add_children(const std::vector<Node>& new_children, int new_depth) {
        for (Node child : new_children) {
            add_child(child, new_depth);
        }
    }

    /**
     * @brief Clears existing children and sets new child nodes.
     * @param new_children The child nodes to add.
     */
    inline void reset_children(const std::vector<Node>& new_children) {
        children.clear();
        add_children(new_children);
    }

    /**
     * @brief Clears existing children and sets new child nodes with a specified depth.
     * @param new_children The child nodes to add.
     * @param new_depth The depth to assign to the children.
     */
    inline void reset_children(const std::vector<Node>& new_children, int new_depth) {
        children.clear();
        add_children(new_children, new_depth);
    }
};

/**
 * @brief Compares two nodes for equality.
 * @param n1 The first node.
 * @param n2 The second node.
 * @return `true` if nodes are identical, `false` otherwise.
 */
inline bool operator==(Node n1, Node n2) {
    return (n1.repr == n2.repr) && (n1.type == n2.type);
}

/**
 * @brief Inserts a Node into an output stream.
 * @param os The output stream.
 * @param n The node to insert.
 * @return The updated output stream.
 */
inline std::ostream& operator<<(std::ostream& os, Node n) {
    os << std::string(n.depth, '\t') << n.repr << "\n";
    for (const Node& c : n.children) {
        os << c;
    }
    return os;
}

/**
 * @brief Reserved keywords for the language.
 */
const std::map<std::string, Node> KEY_WORDS = {
    {"int64", Node(NodeType::raw_type, "int64")},
    {"return", Node(NodeType::_return, "return")}
};

/**
 * @brief Delimiters such as `;` and `,`.
 */
const std::map<std::string, Node> DELIMITERS = {
    {";", Node(NodeType::delimiter, ";")},
    {",", Node(NodeType::delimiter, ",")}
};

/**
 * @brief Opening brackets and parentheses.
 */
const std::map<std::string, Node> OPENERS = {
    {"(", Node(NodeType::paren, "(")},
    {"{", Node(NodeType::brackets, "{")}
};

/**
 * @brief Closing brackets and parentheses.
 */
const std::map<std::string, Node> CLOSERS = {
    {")", Node(NodeType::paren, ")")},
    {"}", Node(NodeType::brackets, "}")}
};

/**
 * @brief Operators such as `+`, `-`, `*`, `/`, and `=`.
 */
const std::map<std::string, Node> OPERATORS = {
    {"+", Node(NodeType::add_op, "+")},
    {"-", Node(NodeType::sub_op, "-")},
    {"*", Node(NodeType::mul_op, "*")},
    {"/", Node(NodeType::div_op, "/")},
    {"=", Node(NodeType::assignment, "=")}
};

#endif // TOKEN_H
