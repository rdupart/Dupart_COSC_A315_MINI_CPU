#include "CPU.h"
#include <iostream>
#include <iomanip>
using namespace std;

CPU::CPU(Memory& m) : mem(m) {
    PC = 0;
    for (int i = 0; i < 32; i++) R[i] = 0;
}

uint32_t CPU::fetch() {
    return mem.read32(PC);
}

void CPU::decodeExecute(uint32_t inst) {
    int opcode = (inst >> 26) & 0x3F;
    int rs     = (inst >> 21) & 0x1F;
    int rt     = (inst >> 16) & 0x1F;
    int rd     = (inst >> 11) & 0x1F;
    int funct  = inst & 0x3F;
    int16_t imm = inst & 0xFFFF;  // signed immediate

    uint32_t nextPC = PC + 4;

    cout << "PC = 0x" << hex << PC << "  INST = 0x" 
         << setw(8) << setfill('0') << inst << dec << "\n";

    // R-type
    if (opcode == 0) {
        if (funct == 0x20) {              // ADD
            R[rd] = R[rs] + R[rt];
            cout << "  ADD\n";
        }
        else if (funct == 0x22) {         // SUB
            R[rd] = R[rs] - R[rt];
            cout << "  SUB\n";
        }
    }
    // I-type
    else if (opcode == 0x08) {            // ADDI
        R[rt] = R[rs] + imm;
        cout << "  ADDI\n";
    }
    else if (opcode == 0x23) {            // LW
        uint32_t addr = R[rs] + imm;
        R[rt] = mem.read32(addr);
        cout << "  LW\n";
    }
    else if (opcode == 0x2B) {            // SW
        uint32_t addr = R[rs] + imm;
        mem.write32(addr, R[rt]);
        cout << "  SW\n";
    }
    else if (opcode == 0x04) {            // BEQ
        if (R[rs] == R[rt]) {
            nextPC = nextPC + ((int32_t)imm << 2);
            cout << "  BEQ taken\n";
        }
        else {
            cout << "  BEQ not taken\n";
        }
    }
    else {
        cout << "Unknown instruction!\n";
    }

    R[0] = 0;  // keep $zero zero
    PC = nextPC;
}

void CPU::printState() {
    cout << "Registers:\n";
    for (int i = 0; i < 32; i++) {
        cout << "R[" << i << "] = " << R[i] << "  ";
        if (i % 4 == 3) cout << "\n";
    }
}

void CPU::run(int maxCycles) {
    for (int c = 0; c < maxCycles; c++) {
        if (PC >= Memory::SIZE) {
            cout << "PC out of range -> stopping\n";
            break;
        }
        uint32_t inst = fetch();
        decodeExecute(inst);
        printState();
        cout << "----------------------------\n";
    }
}
