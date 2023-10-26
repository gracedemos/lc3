//
// Created by Grace Demos on 10/23/23.
//

#ifndef LC3_STATE_H
#define LC3_STATE_H

#include <cstdint>

struct Registers {
    uint16_t pc;
    uint16_t ir;
    uint16_t r0;
    uint16_t r1;
    uint16_t r2;
    uint16_t r3;
    uint16_t r4;
    uint16_t r5;
    uint16_t r6;
    uint16_t r7;
};

struct Flags {
    uint8_t n;
    uint8_t z;
    uint8_t p;
};

#endif //LC3_STATE_H
