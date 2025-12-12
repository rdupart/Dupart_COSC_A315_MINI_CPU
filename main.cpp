#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "memory.h"
#include "cpu.h"
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

void loadProgramFromFile(Memory& mem, const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Could not open file " << filename << endl;
        return;
    }

    string line;
    int addr = 0;
    
    while (getline(file, line)) {
        if (line.empty() || line[0] == '#' || line[0] == '/') {
            continue;
        }
        
        line.erase(0, line.find_first_not_of(" \t"));
        line.erase(line.find_last_not_of(" \t") + 1);
        
        if (line.empty()) continue;
        
        // Convert hex string to uint32_t
        uint32_t instruction;
        stringstream ss;
        
        if (line.substr(0, 2) == "0x" || line.substr(0, 2) == "0X") {
            ss << hex << line.substr(2);
        } else {
            ss << hex << line;
        }
        
        if (ss >> instruction) {
            mem.write32(addr, instruction);
            addr += 4;
            cout << "Loaded instruction 0x" << hex << instruction << " at address " << dec << addr - 4 << endl;
        } else {
            cout << "Warning: Could not parse line: " << line << endl;
        }
    }
    
    file.close();
    cout << "Loaded " << dec << (addr / 4) << " instructions from " << filename << endl;
}

int main() {
    Memory mem;

    cout << "Mini CPU Simulator\n";
    cout << "Choose program to run:\n";
    cout << "1 = Program 1\n";
    cout << "2 = Program 2\n";
    cout << "3 = Load from hex_file.txt\n";
    cout << "> ";

    int choice;
    cin >> choice;

    if (choice == 1)
        loadProgram1(mem);
    else if (choice == 2)
        loadProgram2(mem);
    else if (choice == 3)
        loadProgramFromFile(mem, "hex_file.txt");
    else {
        cout << "Invalid choice. Defaulting to Program 1.\n";
        loadProgram1(mem);
    }

    CPU cpu(mem);
    cpu.run();

    return 0;
}
