cmake_minimum_required(VERSION 3.17)
project(diploma)

set(CMAKE_CXX_STANDARD 20)

add_executable(src main.cpp approximation.cpp time.cpp flux.cpp PLIC.cpp printfile.cpp readfile.cpp structures.cpp line_equation.cpp slau.cpp)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tests)

enable_testing()
