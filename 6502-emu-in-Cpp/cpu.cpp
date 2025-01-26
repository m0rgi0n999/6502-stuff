// cpu.cpp
#include "cpu.hpp"
#include <iostream>
#include <iomanip>

void CPU6502::updateZeroNegativeFlags(uint8_t value) {
    P = (value == 0 ? P | 0x02 : P & ~0x02); // Zero flag
    P = (value & 0x80 ? P | 0x80 : P & ~0x80); // Negative flag
}

void CPU6502::execute() {
    uint8_t opcode = memory.read(PC++); // Fetch
    InstructionSet::executeInstruction(opcode, *this, memory); // Delegate execution
}
