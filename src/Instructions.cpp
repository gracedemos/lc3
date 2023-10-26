//
// Created by Grace Demos on 10/25/23.
//

#include <iostream>
#include "utils.h"

#include "Instructions.h"

void setRegister(Registers* registers, uint8_t dr, uint16_t value) {
    switch (dr) {
        case 0:
            registers->r0 = value;
            break;
        case 1:
            registers->r1 = value;
            break;
        case 2:
            registers->r2 = value;
            break;
        case 3:
            registers->r3 = value;
            break;
        case 4:
            registers->r4 = value;
            break;
        case 5:
            registers->r5 = value;
            break;
        case 6:
            registers->r6 = value;
            break;
        case 7:
            registers->r7 = value;
            break;
        default:
            std::cerr << "Error: invalid register\n";
            break;
    }
}

uint16_t getRegister(Registers* registers, uint8_t sr) {
    uint16_t result = 0;
    switch (sr) {
        case 0:
            result = registers->r0;
            break;
        case 1:
            result = registers->r1;
            break;
        case 2:
            result = registers->r2;
            break;
        case 3:
            result = registers->r3;
            break;
        case 4:
            result = registers->r4;
            break;
        case 5:
            result = registers->r5;
            break;
        case 6:
            result = registers->r6;
            break;
        case 7:
            result = registers->r7;
            break;
        default:
            break;
    }

    return result;
}

void setFlags(Flags* flags, int16_t value) {
    if (value < 0) {
        flags->n = 1;
        flags->z = 0;
        flags->p = 0;
    } else if (value > 0) {
        flags->n = 0;
        flags->z = 0;
        flags->p = 1;
    } else {
        flags->n = 0;
        flags->z = 1;
        flags->p = 0;
    }
}

void Instructions::lea(Registers* registers) {
    uint8_t dr = (registers->ir & LEA_DR_MASK) >> 9;
    int9 offset = {registers->ir & LEA_OFFSET_MASK};

    uint16_t address = registers->pc + offset.val;
    setRegister(registers, dr, address);
}

void Instructions::trap(std::vector<uint16_t> &memory, Registers* registers) {
    uint8_t trapVec = registers->ir & TRAP_VEC_MASK;
    uint16_t printIndex;

    switch (trapVec) {
        case TRAP_GETC:
            registers->r0 = getchar();
            break;
        case TRAP_OUT:
            std::cout << static_cast<char>(registers->r0);
            break;
        case TRAP_PUTS:
            printIndex = registers->r0;
            while (memory[printIndex] != 0) {
                std::cout << static_cast<char>(memory[printIndex]);
                printIndex++;
            }
            std::flush(std::cout);
            break;
        case TRAP_HALT:
            std::cout << "\n[LC3]: Emulator halted\n";
            std::exit(0);
        default:
            std::cerr << "Error [pc = 0x" << std::hex << registers->pc << "]: Invalid or unimplemented trap vector\n";
            std::exit(1);
    }
}

void Instructions::add(Registers* registers, Flags* flags) {
    uint8_t dr = (registers->ir & ADD_DR_MASK) >> 9;
    uint8_t sr1 = (registers->ir & ADD_SR1_MASK) >> 6;

    if (registers->ir & (1 << 5)) {
        int5 immediate = {registers->ir & ADD_IMMEDIATE_MASK};
        auto result = static_cast<int16_t>(getRegister(registers, sr1) + immediate.val);
        setRegister(registers, dr, result);
        setFlags(flags, result);
    } else {
        uint8_t sr2 = registers->ir & ADD_SR2_MASK;
        auto result = static_cast<int16_t>(getRegister(registers, sr1) + getRegister(registers, sr2));
        setRegister(registers, dr, result);
        setFlags(flags, result);
    }
}

void Instructions::ld(std::vector<uint16_t> &memory, Registers* registers, Flags* flags) {
    uint8_t dr = (registers->ir & LD_DR_MASK) >> 9;
    int9 offset = {registers->ir & LD_OFFSET_MASK};

    uint16_t address = registers->pc + offset.val;
    setRegister(registers, dr, memory[address]);
    setFlags(flags, static_cast<int16_t>(memory[address]));
}

void Instructions::lc3_and(Registers* registers, Flags* flags) {
    uint8_t dr = (registers->ir & AND_DR_MASK) >> 9;
    uint8_t sr1 = (registers->ir & AND_SR1_MASK) >> 6;

    if (registers->ir & (1 << 5)) {
        int5 immediate = {registers->ir & AND_IMMEDIATE_MASK};
        auto result = static_cast<int16_t>(getRegister(registers, sr1) & immediate.val);
        setRegister(registers, dr, result);
        setFlags(flags, result);
    } else {
        uint8_t sr2 = registers->ir & AND_SR2_MASK;
        auto result = static_cast<int16_t>(getRegister(registers, sr1) & getRegister(registers, sr2));
        setRegister(registers, dr, result);
        setFlags(flags, result);
    }
}

void Instructions::br(Registers* registers, Flags* flags) {
    uint8_t br_nzp = (registers->ir & BR_NZP_MASK) >> 9;
    uint8_t nzp = (flags->n << 2) | (flags->z << 1) | flags->p;
    int9 offset = {registers->ir & BR_OFFSET_MASK};

    if (br_nzp & nzp) {
        registers->pc += offset.val;
    } else if (br_nzp == 0) {
        registers->pc += offset.val;
    }
}

void Instructions::jsr(Registers* registers) {
    if (registers->ir & (1 << 11)) {
        int11 offset = {registers->ir & JSR_OFFSET_MASK};
        registers->r7 = registers->pc;
        registers->pc += offset.val;
    } else {
        uint8_t reg = (registers->ir & JSRR_REG_MASK) >> 6;
        registers->r7 = registers->pc;
        registers->pc = getRegister(registers, reg);
    }
}

void Instructions::jmp(Registers* registers) {
    uint8_t reg = (registers->ir & JMP_REG_MASK) >> 6;
    registers->pc = getRegister(registers, reg);
}

void Instructions::st(std::vector<uint16_t> &memory, Registers* registers) {
    uint8_t sr = (registers->ir & ST_SR_MASK) >> 9;
    int9 offset = {registers->ir & ST_OFFSET_MASK};

    memory[registers->pc + offset.val] = getRegister(registers, sr);
}

void Instructions::lc3_not(Registers* registers, Flags* flags) {
    uint8_t dr = (registers->ir & NOT_DR_MASK) >> 9;
    uint8_t sr = (registers->ir & NOT_SR_MASK) >> 6;

    uint16_t result = ~getRegister(registers, sr);
    setRegister(registers, dr, result);
    setFlags(flags, static_cast<int16_t>(result));
}
