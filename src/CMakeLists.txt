cmake_minimum_required(VERSION 3.20)
project(src)

set(CMAKE_CXX_STANDARD 14)

add_executable(src main.cpp grids.h linear.h operations.h PLIC.h structures.h)
