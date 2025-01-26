#include "Lexer.h"
#include <sstream>
#include <cctype>
#include <algorithm>

// Constructor
Lexer::Lexer(const std::string& source) : source(source), pos(0) {}

std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;
    while (pos < source.size()) {
        char currentChar = source[pos];

        if (isspace(currentChar)) {
            // Skip spaces
            pos++;
        } else if (currentChar == ';') {
            // Handle comments
            tokens.push_back(handleComment());
        } else if (isalpha(currentChar)) {
            // Handle instructions and labels
            std::string word = readWord();
            if (isInstruction(word)) {
                tokens.push_back(Token(TokenType::INSTRUCTION, word));
            } else {
                tokens.push_back(Token(TokenType::LABEL, word));
            }
        } else if (isdigit(currentChar)) {
            // Handle numbers
            tokens.push_back(handleNumber());
        } else if (currentChar == '#') {
            // Handle immediate operand (e.g., #$FF)
            tokens.push_back(handleOperand());
        } else {
            tokens.push_back(Token(TokenType::INVALID, std::string(1, currentChar)));
            pos++;
        }
    }

    tokens.push_back(Token(TokenType::EOF_TOKEN, ""));
    return tokens;
}

std::string Lexer::readWord() {
    size_t startPos = pos;
    while (pos < source.size() && isalnum(source[pos])) {
        pos++;
    }
    return source.substr(startPos, pos - startPos);
}

Token Lexer::handleComment() {
    size_t startPos = pos;
    while (pos < source.size() && source[pos] != '\n') {
        pos++;
    }
    return Token(TokenType::COMMENT, source.substr(startPos, pos - startPos));
}

Token Lexer::handleNumber() {
    size_t startPos = pos;
    while (pos < source.size() && isdigit(source[pos])) {
        pos++;
    }
    return Token(TokenType::NUMBER, source.substr(startPos, pos - startPos));
}

Token Lexer::handleOperand() {
    pos++; // Skip the '#'
    return handleNumber();
}

bool Lexer::isInstruction(const std::string& word) {
    static const std::vector<std::string> instructions = {
        "LDA", "STA", "LDX", "STX", "LDY", "STY", "AND", "OR", "EOR", "ADC", "SBC",
        "CMP", "CPX", "CPY", "INX", "DEX", "INY", "DEY", "BNE", "BEQ", "BMI", "BPL",
        "BRK", "RTS", "JSR", "RTI", "NOP", "CLC", "SEC", "CLI", "SEI", "CLV", "SED", "SED"
    };
    return std::find(instructions.begin(), instructions.end(), word) != instructions.end();
}
