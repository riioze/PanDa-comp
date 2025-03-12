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
    mul_op,            ///< `*` multiplication operator.
    div_op,            ///< `/` division operator.
    add_op,            ///< `+` addition operator.
    min_op,            ///< `-` subtraction operator.
    declaration,        ///< Represents a declaration (`full_type identifier;`).
    assignment,        ///< Represents an assignment (`identifier = value;`).
    initialisation,    ///< Represents an initialization (`full_type identifier = value;`).
    literal,           ///< Represents a literal value.
    function,          ///< Represents an entire function.
    function_sign,     ///< Represents a function signature (name and parameters).
    function_params,   ///< Represents function parameters.
    function_body,     ///< Represents the function body.
    _return,          ///< Represents a return statement.
    delimiter,        ///< Represents a delimiter (`;`, `,`).
    paren,           ///< Represents parentheses `()`.
    brackets         ///< Represents curly brackets `{}`.
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
    {"-", Node(NodeType::min_op, "-")},
    {"*", Node(NodeType::mul_op, "*")},
    {"/", Node(NodeType::div_op, "/")},
    {"=", Node(NodeType::assignment, "=")}
};

#endif // TOKEN_H
