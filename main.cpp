#include <iostream>
#include "Memory.h"
#include "CPU.h"
using namespace std;

void loadProgram1(Memory& mem) {
    uint32_t prog[] = {
        0x2008000A, // ADDI $t0, $zero, 10
        0x20090001, // ADDI $t1, $zero, 1
        0x01095020, // ADD  $t2, $t0, $t1
        0xAC0A0000  // SW   $t2, 0($zero)
    };

    int addr = 0;
    for (uint32_t inst : prog) {
        mem.write32(addr, inst);
        addr += 4;
    }
}

void loadProgram2(Memory& mem) {
    uint32_t prog[] = {
        0x20080005, // ADDI $t0, $zero, 5
        0x20090000, // ADDI $t1, $zero, 0
        0x01285020, // ADD  $t1, $t1, $t0
        0x2108FFFF, // ADDI $t0, $t0, -1
        0x11000002, // BEQ  $t0, $zero, END
        0x1000FFFC, // BEQ  $zero, $zero, LOOP
        0xAC090000  // SW $t1, 0($zero)
    };

    int addr = 0;
    for (uint32_t inst : prog) {
        mem.write32(addr, inst);
        addr += 4;
    }
}

int main() {
    Memory mem;

    cout << "Mini CPU Simulator\n";
    cout << "Choose program to run:\n";
    cout << "1 = Program 1\n";
    cout << "2 = Program 2\n";
    cout << "> ";

    int choice;
    cin >> choice;

    if (choice == 1)
        loadProgram1(mem);
    else
        loadProgram2(mem);

    CPU cpu(mem);
    cpu.run();

    return 0;
}
