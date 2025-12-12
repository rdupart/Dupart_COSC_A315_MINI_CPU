#include "Memory.h"
#include <iostream>
using namespace std;

Memory::Memory() {
    for (int i = 0; i < SIZE; i++)
        mem[i] = 0;
}

uint32_t Memory::read32(uint32_t addr) const {
    // combine 4 bytes (big-endian)
    uint32_t b0 = mem[addr];
    uint32_t b1 = mem[addr + 1];
    uint32_t b2 = mem[addr + 2];
    uint32_t b3 = mem[addr + 3];
    return (b0 << 24) | (b1 << 16) | (b2 << 8) | b3;
}

void Memory::write32(uint32_t addr, uint32_t value) {
    // store 4 bytes (big-endian)
    mem[addr]     = (value >> 24) & 0xFF;
    mem[addr + 1] = (value >> 16) & 0xFF;
    mem[addr + 2] = (value >> 8) & 0xFF;
    mem[addr + 3] = value & 0xFF;
}
