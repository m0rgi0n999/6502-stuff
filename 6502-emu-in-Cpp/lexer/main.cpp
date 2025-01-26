#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <map>
#include <vector>
#include <stdexcept>
#include "Lexer.h" // Include your lexer impliedementation
#include <cstdint> // For uint8_t

void debugInstruction(const std::string& instruction, const std::string& addressingMode) {
    std::cout << "Instruction: " << instruction 
              << ", Addressing Mode: " << addressingMode << std::endl;
}

// Opcode map
std::unordered_map<std::string, std::unordered_map<std::string, uint8_t>> opcodes;

// Function to initialize opcodes
void initializeOpcodes() {
    // Example opcodes for 6502 instructions
    opcodes["BRK"]["implied"] = 0x00;
    opcodes["ORA"]["indirectX"] = 0x01;
    opcodes["ORA"]["zeropage"] = 0x05;
    opcodes["ASL"]["zeropage"] = 0x06;
    opcodes["PHP"]["implied"] = 0x08;
    opcodes["ORA"]["immediateediate"] = 0x09;
    opcodes["ASL"]["accumulator"] = 0x0A;
    opcodes["ORA"]["absolute" ] = 0x0D;
    opcodes["ASL"]["absolute" ] = 0x0E;
    opcodes["BPL"]["relative"] = 0x10;
    opcodes["ORA"]["indirectY"] = 0x11;
    opcodes["ORA"]["zeropageX"] = 0x15;
    opcodes["ASL"]["zeropageX"] = 0x16;
    opcodes["CLC"]["implied"] = 0x18;
    opcodes["ORA"]["absoluteY"] = 0x19;
    opcodes["ORA"]["absoluteX"] = 0x1D;
    opcodes["ASL"]["absoluteX"] = 0x1E;
    opcodes["JSR"]["absolute" ] = 0x20;
    opcodes["AND"]["indirectX"] = 0x21;
    opcodes["BIT"]["zeropage"] = 0x24;
    opcodes["AND"]["zeropage"] = 0x25;
    opcodes["ROL"]["zeropage"] = 0x26;
    opcodes["PLP"]["implied"] = 0x28;
    opcodes["AND"]["immediate"] = 0x29;
    opcodes["ROL"]["accumulator"] = 0x2A;
    opcodes["BIT"]["absolute" ] = 0x2C;
    opcodes["AND"]["absolute" ] = 0x2D;
    opcodes["ROL"]["absolute" ] = 0x2E;
    opcodes["BMI"]["relative"] = 0x30;
    opcodes["AND"]["indirectY"] = 0x31;
    opcodes["AND"]["zeropageX"] = 0x35;
    opcodes["ROL"]["zeropageX"] = 0x36;
    opcodes["SEC"]["implied"] = 0x38;
    opcodes["AND"]["absoluteY"] = 0x39;
    opcodes["AND"]["absoluteX"] = 0x3D;
    opcodes["ROL"]["absoluteX"] = 0x3E;
    opcodes["RTI"]["implied"] = 0x40;
    opcodes["EOR"]["indirectX"] = 0x41;
    opcodes["EOR"]["zeropage"] = 0x45;
    opcodes["LSR"]["zeropage"] = 0x46;
    opcodes["PHA"]["implied"] = 0x48;
    opcodes["EOR"]["immediate"] = 0x49;
    opcodes["LSR"]["accumulator"] = 0x4A;
    opcodes["JMP"]["absolute" ] = 0x4C;
    opcodes["EOR"]["absolute" ] = 0x4D;
    opcodes["LSR"]["absolute" ] = 0x4E;
    opcodes["BVC"]["relative"] = 0x50;
    opcodes["EOR"]["indirectY"] = 0x51;
    opcodes["EOR"]["zeropageX"] = 0x55;
    opcodes["LSR"]["zeropageX"] = 0x56;
    opcodes["CLI"]["implied"] = 0x58;
    opcodes["EOR"]["absoluteY"] = 0x59;
    opcodes["EOR"]["absoluteX"] = 0x5D;
    opcodes["LSR"]["absoluteX"] = 0x5E;
    opcodes["RTS"]["implied"] = 0x60;
    opcodes["ADC"]["indirectX"] = 0x61;
    opcodes["ADC"]["zeropage"] = 0x65;
    opcodes["ROR"]["zeropage"] = 0x66;
    opcodes["PLA"]["implied"] = 0x68;
    opcodes["ADC"]["immediate"] = 0x69;
    opcodes["ROR"]["accumulator"] = 0x6A;
    opcodes["JMP"]["indirect"] = 0x6C;
    opcodes["ADC"]["absolute" ] = 0x6D;
    opcodes["ROR"]["absolute" ] = 0x6E;
    opcodes["BVS"]["relative"] = 0x70;
    opcodes["ADC"]["indirectY"] = 0x71;
    opcodes["ADC"]["zeropageX"] = 0x75;
    opcodes["ROR"]["zeropageX"] = 0x76;
    opcodes["SEI"]["implied"] = 0x78;
    opcodes["ADC"]["absoluteY"] = 0x79;
    opcodes["ADC"]["absoluteX"] = 0x7D;
    opcodes["ROR"]["absoluteX"] = 0x7E;
    opcodes["STA"]["indirectX"] = 0x81;
    opcodes["STY"]["zeropage"] = 0x84;
    opcodes["STA"]["zeropage"] = 0x85;
    opcodes["STX"]["zeropage"] = 0x86;
    opcodes["DEY"]["implied"] = 0x88;
    opcodes["TXA"]["implied"] = 0x8A;
    opcodes["STY"]["absolute" ] = 0x8C;
    opcodes["STA"]["absolute" ] = 0x8D;
    opcodes["STX"]["absolute" ] = 0x8E;
    opcodes["BCC"]["relative"] = 0x90;
    opcodes["STA"]["indirectY"] = 0x91;
    opcodes["STY"]["zeropageX"] = 0x94;
    opcodes["STA"]["zeropageX"] = 0x95;
    opcodes["STX"]["zeropageX"] = 0x96;
    opcodes["TYA"]["implied"] = 0x98;
    opcodes["STA"]["absoluteX"] = 0x99;
    opcodes["TXS"]["implied"] = 0x9A;
    opcodes["STA"]["absoluteX"] = 0x9D;
    opcodes["LDY"]["immediate"] = 0xA0;
    opcodes["LDA"]["indirectX"] = 0xA1;
    opcodes["LDX"]["immediate"] = 0xA2;
    opcodes["LDY"]["zeropage"] = 0xA4;
    opcodes["LDA"]["zeropage"] = 0xA5;
    opcodes["LDX"]["zeropage"] = 0xA6;
    opcodes["TAY"]["implied"] = 0xA8;
    opcodes["LDA"]["immediate"] = 0xA9;
    opcodes["TAX"]["implied"] = 0xAA;
    opcodes["LDY"]["absolute" ] = 0xAC;
    opcodes["LDA"]["absolute" ] = 0xAD;
    opcodes["LDX"]["absolute" ] = 0xAE;
    opcodes["BCS"]["relative"] = 0xB0;
    opcodes["LDA"]["indirect"] = 0xB1;
    opcodes["LDY"]["zeropageY"] = 0xB4;
    opcodes["LDA"]["zeropageY"] = 0xB5;
    opcodes["LDX"]["zeropageY"] = 0xB6;
    opcodes["CLV"]["implied"] = 0xB8;
    opcodes["LDA"]["absoluteY"] = 0xB9;
    opcodes["TSX"]["implied"] = 0xBA;
    opcodes["LDY"]["absoluteX"] = 0xBC;
    opcodes["LDA"]["absoluteX"] = 0xBD;
    opcodes["LDX"]["absoluteX"] = 0xBE;
    opcodes["CPY"]["immediate"] = 0xC0;
    opcodes["CMP"]["indirectX"] = 0xC1;
    opcodes["CPY"]["zeropage"] = 0xC4;
    opcodes["CMP"]["zeropage"] = 0xC5;
    opcodes["DEC"]["zeropage"] = 0xC6;
    opcodes["INY"]["implied"] = 0xC8;
    opcodes["CMP"]["immediate"] = 0xC9;
    opcodes["DEX"]["implied"] = 0xCA;
    opcodes["CPY"]["absolute" ] = 0xCC;
    opcodes["CMP"]["absolute" ] = 0xCD;
    opcodes["DEC"]["absolute" ] = 0xCE;
    opcodes["BNE"]["relative"] = 0xD0;
    opcodes["CMP"]["indirectY"] = 0xD1;
    opcodes["CMP"]["zeropageX"] = 0xD5;
    opcodes["DEC"]["zeropageX"] = 0xD6;
    opcodes["CLD"]["implied"] = 0xD8;
    opcodes["CMP"]["absoluteY"] = 0xD9;
    opcodes["CMP"]["absoluteX"] = 0xDD;
    opcodes["DEC"]["absoluteX"] = 0xDE;
    opcodes["CPX"]["immediate"] = 0xE0;
    opcodes["SBC"]["indirectX"] = 0xE1;
    opcodes["CPX"]["zeropage"] = 0xE4;
    opcodes["SBC"]["zeropage"] = 0xE5;
    opcodes["INC"]["zeropage"] = 0xE6;
    opcodes["INX"]["implied"] = 0xE8;
    opcodes["SBC"]["immediate"] = 0xE9;
    opcodes["NOP"]["implied"] = 0xEA;
    opcodes["CPX"]["absolute" ] = 0xEC;
    opcodes["SBC"]["absolute" ] = 0xED;
    opcodes["INC"]["absolute" ] = 0xEE;
    opcodes["BEQ"]["relative"] = 0xF0;
    opcodes["SBC"]["indirectY"] = 0xF1;
    opcodes["SBC"]["zeropageX"] = 0xF5;
    opcodes["INC"]["zeropageX"] = 0xF6;
    opcodes["SED"]["implied"] = 0xF8;
    opcodes["SBC"]["absoluteY"] = 0xF9;
    opcodes["SBC"]["absoluteX"] = 0xFD;
    opcodes["INC"]["absoluteX"] = 0xFE;

    /*// extended opcodes 65C02
    opcodes["TSB"]["zeropage"] = 0x04;
    opcodes["RMB0"]["zeropage"] = 0x07;
    opcodes["TSB"]["absolute" ] = 0x0C;
    opcodes["BBR0"]["relative"] = 0x0F;
    opcodes["ORA"]["zeropage"] = 0x12;
    opcodes["TRB"]["zeropage"] = 0x14;
    opcodes["RMB1"]["zeropage"] = 0x17;
    opcodes["INC"]["accumulator"] = 0x1A;
    opcodes["TRB"]["absolute" ] = 0x1C;
    opcodes["BBR1"]["relative"] = 0x1F;
    opcodes["RMB2"]["zeropage"] = 0x27;
    opcodes["AND"]["zeropage"] = 0x32;
    opcodes["EOR"]["zeropage"] = 0x52;
    opcodes["ADC"]["zeropage"] = 0x72;
    opcodes["STA"]["zeropage"] = 0x92;
    opcodes["BRA"]["relative"] = 0x80;
    opcodes["LDA"]["zeropage"] = 0xB2;
    opcodes["CMP"]["zeropage"] = 0xD2;
    opcodes["SBC"]["zeropage"] = 0xF2;
    opcodes["BIT"]["zeropageX"] = 0x34;
    opcodes["STZ"]["zeropage"] = 0x64;
    opcodes["STZ"]["zeropageX"] = 0x74;
    opcodes["RMB3"]["zeropage"] = 0x37;
    opcodes["RMB4"]["zeropage"] = 0x47;
    opcodes["RMB5"]["zeropage"] = 0x57;
    opcodes["RMB6"]["zeropage"] = 0x67;
    opcodes["RMB7"]["zeropage"] = 0x77;
    opcodes["SMB0"]["zeropage"] = 0x87;
    opcodes["SMB1"]["zeropage"] = 0x97;
    opcodes["SMB2"]["zeropage"] = 0xA7;
    opcodes["SMB3"]["zeropage"] = 0xB7;
    opcodes["SMB4"]["zeropage"] = 0xC7;
    opcodes["SMB5"]["zeropage"] = 0xD7;
    opcodes["SMB6"]["zeropage"] = 0xE7;
    opcodes["SMB7"]["zeropage"] = 0xF7;
    opcodes["BIT"]["immediate"] = 0x89;
    opcodes["BBR3"]["relative"] = 0x3F;
    opcodes["BBR4"]["relative"] = 0x4F;
    opcodes["BBR5"]["relative"] = 0x5F;
    opcodes["BBR6"]["relative"] = 0x6F;
    opcodes["BBR7"]["relative"] = 0x7F;
    opcodes["BBS0"]["relative"] = 0x8F;
    opcodes["BBS1"]["relative"] = 0x9F;
    opcodes["BBS2"]["relative"] = 0xAF;
    opcodes["BBS3"]["relative"] = 0xBF;
    opcodes["BBS4"]["relative"] = 0xCF;
    opcodes["BBS5"]["relative"] = 0xDF;
    opcodes["BBS6"]["relative"] = 0xEF;
    opcodes["BBS7"]["relative"] = 0xFF;
    opcodes["BBR2"]["relative"] = 0x2F;
    opcodes["DEC"]["accumulator"] = 0x3A;
    opcodes["PHY"]["implied"] = 0x5A;
    opcodes["PLY"]["implied"] = 0x7A;
    opcodes["PHX"]["implied"] = 0xDA;
    opcodes["PLX"]["implied"] = 0xFA;
    opcodes["WAI"]["implied"] = 0xCB;
    opcodes["STP"]["implied"] = 0xDB;
    opcodes["BIT"]["absoluteX"] = 0x3C;
    opcodes["JMP"]["absoluteX"] = 0x7C;
    opcodes["STZ"]["absolute" ] = 0x9C;
    opcodes["STZ"]["absoluteX"] = 0x9E;
    */
}

void firstPass(const std::vector<Token>& tokens, std::map<std::string, uint16_t>& symbolTable) {
    uint16_t pc = 0; // Program counter

    for (size_t i = 0; i < tokens.size(); i++) {
        const Token& token = tokens[i];

        if (token.type == TokenType::LABEL) {
            if (symbolTable.find(token.value) != symbolTable.end()) {
                throw std::runtime_error("Error: Duplicate label: " + token.value);
            }
            symbolTable[token.value] = pc; // Record the label's address
        } else if (token.type == TokenType::INSTRUCTION) {
            pc++; // Increment for the opcode

            // Increment for operand size
            if (i + 1 < tokens.size() && tokens[i + 1].type == TokenType::NUMBER) {
                std::string operand = tokens[i + 1].value;
                if (operand[0] == '#' || operand.length() <= 3) {
                    pc++; // One-byte operand
                } else {
                    pc += 2; // Two-byte operand
                }
            }
        }
    }
}

// Function to assemble tokens into binary
void assemble(const std::vector<Token>& tokens, std::ofstream& outFile) {
    size_t pc = 0; // Program counter (memory address)

    for (size_t i = 0; i < tokens.size(); i++) {
        const Token& token = tokens[i];

        if (token.type == TokenType::INSTRUCTION) {
            std::string instruction = token.value;
            std::string addressingMode;
            uint16_t operand = 0;

            // Determine addressing mode and operand
            if (i + 1 < tokens.size() && tokens[i + 1].type == TokenType::NUMBER) {
                std::string operandStr = tokens[i + 1].value;

                if (operandStr[0] == '#') {
                    addressingMode = "immediate";
                    if (operandStr[1] == '$') {
                        operand = std::stoi(operandStr.substr(2), nullptr, 16);
                    } else {
                        operand = std::stoi(operandStr.substr(1));
                    }
                } else if (operandStr[0] == '$') {
                    addressingMode = (operandStr.length() <= 3) ? "zeropage" : "absolute" ;
                    operand = std::stoi(operandStr.substr(1), nullptr, 16);
                } else if (operandStr[operandStr.length() - 1] == 'X') {
                    addressingMode = (operandStr.length() <= 3) ? "zeropageX" : "absoluteX";
                    operand = std::stoi(operandStr.substr(0, operandStr.length() - 1), nullptr, 16);
                } else if (operandStr[operandStr.length() - 1] == 'Y') {
                    addressingMode = (operandStr.length() <= 3) ? "zeropageY" : "absoluteY";
                    operand = std::stoi(operandStr.substr(0, operandStr.length() - 1), nullptr, 16);
                } else {
                    throw std::invalid_argument("Invalid operand format");
                }

                i++; // Skip operand token
            }

            if (opcodes.find(instruction) != opcodes.end() &&
                opcodes[instruction].find(addressingMode) != opcodes[instruction].end()) {
                uint8_t opcode = opcodes[instruction][addressingMode];

                // Write opcode and operand to file
                outFile.put(opcode);
                pc++;

                if (addressingMode != "implied" && addressingMode != "accumulator") {
                    outFile.put(static_cast<uint8_t>(operand & 0xFF)); // Write low byte
                    pc++;

                    if (addressingMode == "absolute"  || addressingMode == "absoluteX" ||
                        addressingMode == "absoluteY" || addressingMode == "indirectX" ||
                        addressingMode == "indirectY") {
                        outFile.put(static_cast<uint8_t>((operand >> 8) & 0xFF)); // Write high byte
                        pc++;
                    }
                }
            } else {
                std::cerr << "Error: Unknown instruction or addressing mode: "
                          << instruction << " " << addressingMode << std::endl;
                return;
            }
        }
    }
}

int main(int argc, char* argv[]) {
    // Debug
    std::string instruction = "LDA";
    std::string addressingMode = "immediate";
    debugInstruction(instruction, addressingMode);

    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <source_file.asm>" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    std::ifstream asmFile(filename);
    if (!asmFile.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return 1;
    }

    std::vector<Token> tokens = lex(asmFile); // Lexical analysis
    asmFile.close();

    std::map<std::string, uint16_t> symbolTable;
    try {
        firstPass(tokens, symbolTable); // Build the symbol table
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    std::string outputFilename = filename.substr(0, filename.find_last_of('.')) + ".bin";
    std::ofstream outFile(outputFilename, std::ios::binary);
    if (!outFile.is_open()) {
        std::cerr << "Error: Could not create output file " << outputFilename << std::endl;
        return 1;
    }

    initializeOpcodes(); // Initialize opcode map

    assemble(tokens, outFile); // Assemble tokens into binary
    outFile.close();

    std::cout << "Assembly complete. Output written to " << outputFilename << std::endl;
    return 0;
    
}
