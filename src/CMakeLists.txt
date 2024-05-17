cmake_minimum_required(VERSION 3.20)
project(src)

set(CMAKE_CXX_STANDARD 14)

add_executable(src main.cpp approximation.cpp area.cpp assemble.cpp flux.cpp grids.cpp linear.cpp operations.cpp PLIC.cpp printfile.cpp readfile.cpp structures.cpp)

enable_testing()
add_subdirectory(tests)
