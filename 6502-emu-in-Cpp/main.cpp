// main.cpp
#include <iostream>
#include "cpu.hpp"
#include "memory.hpp"
#include "instruction_set.hpp"

int main() {
    Memory memory;

    // Initialie the instruction set
    InstructionSet::initialize();

    // Load a program into memory
    memory.write(0xFFFC, 0x00); // Reset vector (low byte)
    memory.write(0xFFFD, 0x80); // Reset vector (high byte)
    memory.write(0x8000, 0xA9); // LDA Immediate
    memory.write(0x8001, 0x42); // Value to load
    memory.write(0x8002, 0x00); // BRK

    CPU6502 cpu(memory);
    cpu.reset();

    while (true) {
        cpu.execute();
        if (memory.read(cpu.PC) == 0x00) break; // Stop at BRK
    }

    return 0;
}
