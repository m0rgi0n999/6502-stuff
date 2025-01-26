// cpu.hpp
#ifndef CPU_HPP
#define CPU_HPP

#include <cstdint>
#include "memory.hpp"
#include "instruction_set.hpp"

class CPU6502 {
public:
    // Registers
    uint8_t A = 0;   // Accumulator
    uint8_t X = 0;   // X Index
    uint8_t Y = 0;   // Y Index
    uint8_t SP = 0xFF; // Stack Pointer
    uint16_t PC = 0;  // Program Counter
    uint8_t P = 0;    // Processor Status

    Memory& memory; // Reference to memory

    // Constructor
    CPU6502(Memory& mem) : memory(mem) {}

    void reset() {
        A = X = Y = 0;
        SP = 0xFF;
        P = 0x20; // Default flags
        PC = memory.read16(0xFFFC); // Reset vector
    }

    void execute();

    void updateZeroNegativeFlags(uint8_t value);
};

#endif // CPU_HPP
