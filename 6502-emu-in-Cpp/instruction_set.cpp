// instruction_set.cpp
#include "instruction_set.hpp"
#include <iostream>

std::unordered_map<uint8_t, InstructionSet::InstructionHandler> InstructionSet::instructionMap;

void InstructionSet::initialize() {
    instructionMap = {
        {0xA9, [](CPU6502& cpu, Memory& memory) { // LDA Immediate
            uint8_t value = memory.read(cpu.PC++);
            cpu.A = value;
            cpu.updateZeroNegativeFlags(cpu.A);
            std::cout << "LDA executed. A = " << std::hex << static_cast<int>(cpu.A) << "\n";
        }},
        {0x00, [](CPU6502& cpu, Memory&) { // BRK
            std::cout << "BRK encountered. Halting CPU." << std::endl;
            cpu.PC--; // Stay on BRK
        }},
        // Add more instructions here...
    };
}


void InstructionSet::executeInstruction(uint8_t opcode, CPU6502& cpu, Memory& memory) {
    std::cout << "Executing opcode: " << std::hex << static_cast<int>(opcode) << "\n";

    if (instructionMap.find(opcode) != instructionMap.end()) {
        instructionMap[opcode](cpu, memory);

        // Print CPU state after execution
        std::cout << "A: " << std::hex << static_cast<int>(cpu.A)
                  << " X: " << static_cast<int>(cpu.X)
                  << " Y: " << static_cast<int>(cpu.Y)
                  << " PC: " << cpu.PC
                  << " SP: " << static_cast<int>(cpu.SP)
                  << " P: " << static_cast<int>(cpu.P)
                  << "\n";
    } else {
        std::cerr << "Unknown opcode: " << std::hex << static_cast<int>(opcode) << "\n";
    }
}