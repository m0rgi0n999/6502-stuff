// instruction_set.hpp
#ifndef INSTRUCTION_SET_HPP
#define INSTRUCTION_SET_HPP

#include <cstdint>
#include <unordered_map>
#include <functional>
#include "cpu.hpp"
#include "memory.hpp"

// Forward declaration of CPU class
class CPU6502;

class InstructionSet {
public:
    using InstructionHandler = std::function<void(CPU6502&, Memory&)>;

    static void initialize();
    static void executeInstruction(uint8_t opcode, CPU6502& cpu, Memory& memory);

private:
    static std::unordered_map<uint8_t, InstructionHandler> instructionMap;
};

#endif // INSTRUCTION_SET_HPP
