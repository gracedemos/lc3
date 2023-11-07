//
// Created by Grace Demos on 11/7/23.
//
#include <iostream>

#include "utils.h"

void dumpRegisters(Registers* registers) {
    std::cout << "Register Dump:\n";
    std::cout << "PC: 0x" << std::hex << registers->pc << "\tIR: 0x" << registers->ir << "\n";
    std::cout << "R0: 0x" << std::hex << registers->r0 << "\n";
    std::cout << "R1: 0x" << std::hex << registers->r1 << "\n";
    std::cout << "R2: 0x" << std::hex << registers->r2 << "\n";
    std::cout << "R3: 0x" << std::hex << registers->r3 << "\n";
    std::cout << "R4: 0x" << std::hex << registers->r4 << "\n";
    std::cout << "R5: 0x" << std::hex << registers->r5 << "\n";
    std::cout << "R6: 0x" << std::hex << registers->r6 << "\n";
    std::cout << "R7: 0x" << std::hex << registers->r7 << "\n";
}

