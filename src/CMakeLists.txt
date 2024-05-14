cmake_minimum_required(VERSION 3.17)
project(diploma)

set(CMAKE_CXX_STANDARD 14)

add_executable(program main.cpp approximation.cpp area.cpp flux.cpp grids.cpp linear.cpp operations.cpp PLIC.cpp readfile.cpp structures.cpp)

enable_testing()
add_subdirectory(tests)
