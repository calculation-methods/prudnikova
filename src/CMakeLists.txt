cmake_minimum_required(VERSION 3.17)
project(diploma)

set(CMAKE_CXX_STANDARD 20)

add_executable(src main.cpp time.cpp PLIC.cpp printfile.cpp readfile.cpp structures.cpp line_equation.cpp)

add_subdirectory(math)
target_link_libraries (src PUBLIC math_methods)
target_include_directories (src PUBLIC math)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tests)

enable_testing()
