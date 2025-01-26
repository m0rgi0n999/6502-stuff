#include <iostream>
#include <cstdint>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include "Lexer.h"

// Simple Opcode Mapping for 6502
std::unordered_map<std::string, uint8_t> opcodes = {
    {"LDA", 0xA9},  // LDA immediate
    {"STA", 0x8D},  // STA absolute
    // Add more instructions here
};

// Function to handle instruction parsing and code generation
void assemble(const std::vector<Token>& tokens, std::ofstream& outFile) {
    size_t pc = 0; // Program counter (memory address)

    for (const auto& token : tokens) {
        if (token.type == TokenType::INSTRUCTION) {
            // check the instruction and generate the corresponding machine code
            if (opcodes.find(token.value) != opcodes.end()) {
                uint8_t opcode = opcodes[token.value];
                outFile.put(opcode); // Write the opcode to file
                pc++;

                // Handle operands (e.g. LDA #$01)
                if (token.value == "LDA" && tokens[pc].type == TokenType::NUMBER) {
                    uint8_t operand = std::stoi(tokens[pc].value, nullptr, 16); //Convert operand to byte
                    outFile.put(operand);
                    pc++;
                }
            }
        }
    }
}

std::string readFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return "";
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    
    // Check if the file was empty
    if (buffer.str().empty()) {
        std::cerr << "Error: File " << filename << " is empty." << std::endl;
        return "";
    }

    return buffer.str();
}


int main(int argc, char* argv[]) {
    // Check if filename is passed as a command line argument
    if (argc < 2) {
        std::cerr << "Error: Please provide the path to the assembly file." << std::endl;
        return 1;  // Exit with error code
    }

    // Get the filename from the command line argument
    std::string filename = argv[1];

    // Read file content into a string
    std::string code = readFile(filename);

    // Check if the file was successfully read
    if (code.empty()) {
        return 1;  // Return with error code if the file couldn't be read
    }

    // Create the lexer with the assembly code
    Lexer lexer(code);
    std::vector<Token> tokens = lexer.tokenize();

    // Open output binary file
    std::ofstream outFile("output.bin", std::ios::binary);
    if (!outFile) {
        std::cerr << "Error: Could not open output file." << std::endl;
        return 1;
    }

    // Assemble the code and generate machine code
    assemble(tokens, outFile);

    outFile.close();
    std::cout << "Assembly complete. Output written to output.bin" << std::endl;
    
    return 0;
}
