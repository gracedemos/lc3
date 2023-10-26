cmake_minimum_required(VERSION 3.26)
project(lc3)

set(CMAKE_CXX_STANDARD 17)

add_executable(lc3 src/main.cpp
        src/Emulator.cpp
        src/Emulator.h
        src/state.h
        src/Instructions.cpp
        src/Instructions.h
        src/utils.h
)
