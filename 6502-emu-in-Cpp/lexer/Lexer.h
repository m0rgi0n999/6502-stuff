#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>

// Enum for Token Types
enum class TokenType {
    INSTRUCTION,
    LABEL,
    OPERAND,
    REGISTER,
    NUMBER,
    COMMENT,
    EOF_TOKEN,
    INVALID
};

// Token structure to hold the token type and value
struct Token {
    TokenType type;
    std::string value;

    Token(TokenType t, const std::string& v) : type(t), value(v) {}
};

class Lexer {
public:
    Lexer(const std::string& source);
    std::vector<Token> tokenize();

private:
    std::string source;
    size_t pos;

    std::string readWord();
    Token handleComment();
    Token handleNumber();
    Token handleOperand();
    bool isInstruction(const std::string& word);
};

#endif
