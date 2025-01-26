#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>

// Token types
enum class TokenType {
    INSTRUCTION, // For opcodes like LDA, ADC, etc.
    NUMBER,      // For operands like #$10 or $1234
    LABEL,       // For labels
    UNKNOWN      // For unrecognized tokens
};

// Token structure
struct Token {
    TokenType type;
    std::string value;
};

// Lexer function declaration
std::vector<Token> lex(std::istream& input);

#endif // LEXER_H
