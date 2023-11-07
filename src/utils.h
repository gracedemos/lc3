//
// Created by Grace Demos on 10/25/23.
//

#ifndef LC3_UTILS_H
#define LC3_UTILS_H

#include "state.h"

struct int5 {
    signed int val : 5;
};

struct int6 {
    signed int val : 6;
};

struct int9 {
    signed int val : 9;
};

struct int11 {
    signed int val: 11;
};

void dumpRegisters(Registers* registers);

#endif //LC3_UTILS_H
