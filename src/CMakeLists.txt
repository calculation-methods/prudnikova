cmake_minimum_required(VERSION 3.20)
project(src)

set(CMAKE_CXX_STANDARD 14)

add_executable(src main.cpp approximation.h approximation.cpp area.h area.cpp flux.cpp flux.h grids.cpp grids.h linear.cpp linear.h operations.cpp
operations.h PLIC.cpp PLIC.h readfile.cpp readfile.h structures.cpp structures.h)
