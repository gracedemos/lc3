//
// Created by Grace Demos on 10/23/23.
//

#include <fstream>
#include <iostream>
#include "Instructions.h"

#include "Emulator.h"

Emulator::Emulator(const char *path) {
    std::ifstream file(path, std::ios::binary);
    file.seekg(0, std::ios::end);
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    code.resize(size);
    file.read(reinterpret_cast<char*>(code.data()),size);
    file.close();

    registers = {};
    flags = {};

    int i = 0;
    while (i < code.size() * 2) {
        auto bytePtr = reinterpret_cast<uint8_t*>(code.data());
        uint8_t temp = bytePtr[i];
        bytePtr[i] = bytePtr[i + 1];
        bytePtr[i + 1] = temp;
        i += 2;
    }

    init();
}

void Emulator::init() {
    memory.resize(0x10000);
    uint16_t startIndex = code[0];
    memcpy(&memory[startIndex], &code[1], code.size() - 1);

    registers.pc = startIndex;
}

void Emulator::execute() {
    registers.ir = memory[registers.pc];
    registers.pc++;

    uint16_t opcode = registers.ir & OPCODE_MASK;
    switch (opcode) {
        case ADD_OPCODE:
            Instructions::add(&registers, &flags);
            break;
        case AND_OPCODE:
            Instructions::lc3_and(&registers, &flags);
            break;
        case BR_OPCODE:
            Instructions::br(&registers, &flags);
            break;
        case JMP_OPCODE:
            Instructions::jmp(&registers);
            break;
        case JSR_OPCODE:
            Instructions::jsr(&registers);
            break;
        case LD_OPCODE:
            Instructions::ld(memory, &registers, &flags);
            break;
        case LEA_OPCODE:
            Instructions::lea(&registers);
            break;
        case NOT_OPCODE:
            Instructions::lc3_not(&registers, &flags);
            break;
        case ST_OPCODE:
            Instructions::st(memory, &registers);
            break;
        case TRAP_OPCODE:
            Instructions::trap(memory, &registers);
            break;
        default:
            std::cerr << "Error [pc = 0x" << std::hex << registers.pc << "]: Unimplemented instruction\n";
            std::exit(1);
    }
}

void Emulator::run() {
    while (true) {
        execute();
    }
}
