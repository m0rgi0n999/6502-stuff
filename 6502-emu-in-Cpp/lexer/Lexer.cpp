#include "Lexer.h"
#include <sstream>
#include <cctype>
#include <unordered_set>
#include <iostream> // For std::cout

// Set of valid 6502 instructions
const std::unordered_set<std::string> instructions = {
    "ADC", "AND", "ASL", "BCC", "BCS", "BEQ", "BIT", "BMI", "BNE", "BPL",
    "BRK", "BVC", "BVS", "CLC", "CLD", "CLI", "CLV", "CMP", "CPX", "CPY",
    "DEC", "DEX", "DEY", "EOR", "INC", "INX", "INY", "JMP", "JSR", "LDA",
    "LDX", "LDY", "LSR", "NOP", "ORA", "PHA", "PHP", "PLA", "PLP", "ROL",
    "ROR", "RTI", "RTS", "SBC", "SEC", "SED", "SEI", "STA", "STX", "STY",
    "TAX", "TAY", "TSX", "TXA", "TXS", "TYA" 
};

std::vector<Token> lex(std::istream& input) {
    std::vector<Token> tokens;
    std::string line;

    while (std::getline(input, line)) {
        std::istringstream lineStream(line);
        std::string word;

        while (lineStream >> word) {
            // Check if the word is an instruction
            if (instructions.find(word) != instructions.end()) {
                tokens.push_back({TokenType::INSTRUCTION, word});
            }
            // Check if the word is a number (e.g., #$10, $1234)
            else if (word[0] == '#' || word[0] == '$' || std::isdigit(word[0])) {
                tokens.push_back({TokenType::NUMBER, word});
            }
            // Treat unrecognized tokens as unknown
            else {
                tokens.push_back({TokenType::UNKNOWN, word});
            }
        }
    }

    // Debug output: print all tokens
    /*std::cout << "Lexer Debug Output:\n";
    for (const auto& token : tokens) {
        std::cout << "Token: Type=" << static_cast<int>(token.type)
                  << ", Value=" << token.value << std::endl;
    }
    */
    return tokens;
}
