cmake_minimum_required(VERSION 3.17)
project(diploma)

set(CMAKE_CXX_STANDARD 17)

add_library(geometry_tools OBJECT line_equation.cpp)
target_include_directories (geometry_tools PUBLIC math)

add_library(grid OBJECT grid.cpp)
add_library(io OBJECT printfile.cpp readfile.cpp)
add_library(structures OBJECT structures.cpp)
add_library(plic OBJECT PLIC.cpp)

add_executable(prog main.cpp time.cpp)
target_link_libraries (prog PUBLIC math_methods geometry_tools grid io structures plic)

add_subdirectory(math)

enable_testing()
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tests)
