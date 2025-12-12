#ifndef MEMORY_H
#define MEMORY_H

#include <cstdint>

class Memory {
public:
    static const int SIZE = 4096; // 4 KB

    Memory();

    uint32_t read32(uint32_t addr) const;
    void write32(uint32_t addr, uint32_t value);

    uint8_t mem[SIZE];
};

#endif
