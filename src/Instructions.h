//
// Created by Grace Demos on 10/23/23.
//

#ifndef LC3_INSTRUCTIONS_H
#define LC3_INSTRUCTIONS_H

#include <vector>
#include "state.h"

#define OPCODE_MASK 0xf000

#define ADD_OPCODE 0x1000
#define AND_OPCODE 0x5000
#define BR_OPCODE 0x0000
#define JMP_OPCODE 0xc000
#define JSR_OPCODE 0x4000
#define LD_OPCODE 0x2000
#define LDI_OPCODE 0xa000
#define LDR_OPCODE 0x6000
#define LEA_OPCODE 0xe000
#define NOT_OPCODE 0x9000
#define RTI_OPCODE 0x8000
#define ST_OPCODE 0x3000
#define STI_OPCODE 0xb000
#define STR_OPCODE 0x7000
#define TRAP_OPCODE 0xf000

#define ADD_DR_MASK 0x0e00
#define ADD_SR1_MASK 0x01c0
#define ADD_SR2_MASK 0x0007
#define ADD_IMMEDIATE_MASK 0x001f

#define AND_DR_MASK 0x0e00
#define AND_SR1_MASK 0x01c0
#define AND_SR2_MASK 0x0007
#define AND_IMMEDIATE_MASK 0x001f

#define BR_NZP_MASK 0x0e00
#define BR_OFFSET_MASK 0x01ff

#define JMP_REG_MASK 0x01c0

#define JSR_OFFSET_MASK 0x07ff
#define JSRR_REG_MASK 0x01c0

#define LD_DR_MASK 0x0e00
#define LD_OFFSET_MASK 0x01ff

#define LEA_DR_MASK 0x0e00
#define LEA_OFFSET_MASK 0x01ff

#define NOT_DR_MASK 0x0e00
#define NOT_SR_MASK 0x01c0

#define ST_SR_MASK 0x0e00
#define ST_OFFSET_MASK 0x01ff

#define TRAP_VEC_MASK 0x00ff
#define TRAP_GETC 0x20
#define TRAP_OUT 0x21
#define TRAP_PUTS 0x22
#define TRAP_IN 0x23
#define TRAP_HALT 0x25

void setRegister(Registers* registers, uint8_t dr, uint16_t value);
uint16_t getRegister(Registers* registers, uint8_t sr);
void setFlags(Flags* flags, int16_t value);

class Instructions {
public:
    static void add(Registers* registers, Flags* flags);
    static void lc3_and(Registers* registers, Flags* flags);
    static void br(Registers* registers, Flags* flags);
    static void jmp(Registers* registers);
    static void jsr(Registers* registers);
    static void ld(std::vector<uint16_t> &memory, Registers* registers, Flags* flags);
    static void lea(Registers* registers);
    static void lc3_not(Registers* registers, Flags* flags);
    static void st(std::vector<uint16_t> &memory, Registers* registers);
    static void trap(std::vector<uint16_t> &memory, Registers* registers);
};

#endif //LC3_INSTRUCTIONS_H
