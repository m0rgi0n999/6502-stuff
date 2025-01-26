// memory.hpp
#ifndef MEMORY_HPP
#define MEMORY_HPP

#include <vector>
#include <cstdint>

class Memory {
public:
    std::vector<uint8_t> data;

    Memory(size_t size = 65536) : data(size, 0) {}

    uint8_t read(uint16_t addr) {
        return data[addr];
    }

    void write(uint16_t addr, uint8_t value) {
        data[addr] = value;
    }

    uint16_t read16(uint16_t addr) {
        return (read(addr + 1) << 8) | read(addr);
    }
};

#endif // MEMORY_HPP
