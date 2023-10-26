#include <iostream>
#include "Emulator.h"

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cout << "Incorrect argument count\n";
        std::cout << "Usage: lc3 <filename>\n";
        std::cout << "Where file is an LC3 binary\n";
        return 1;
    }

    Emulator emulator(argv[1]);
    emulator.run();

    return 0;
}
