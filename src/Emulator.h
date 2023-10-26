//
// Created by Grace Demos on 10/23/23.
//

#ifndef LC3_EMULATOR_H
#define LC3_EMULATOR_H

#include <cstdint>
#include <vector>
#include "state.h"

class Emulator {
private:
    std::vector<uint16_t> code;
    std::vector<uint16_t> memory;
    Registers registers;
    Flags flags;

public:
    explicit Emulator(const char* path);
    void run();

private:
    void init();
    void execute();
};


#endif //LC3_EMULATOR_H
