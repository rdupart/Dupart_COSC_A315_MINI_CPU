#ifndef CPU_H
#define CPU_H

#include <cstdint>
#include "Memory.h"

class CPU {
public:
    CPU(Memory& m);

    void run(int maxCycles = 200);

private:
    Memory& mem;
    uint32_t PC;
    int32_t R[32];

    uint32_t fetch();
    void decodeExecute(uint32_t inst);
    void printState();
};

#endif
