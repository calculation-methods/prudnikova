find_package(Boost COMPONENTS unit_test_framework)
include_directories(${Boost_INCLUDE_DIRS})

set(TEST unit_tests)
add_executable(${TEST} slau.cpp area.cpp PLIC.cpp)
target_link_libraries(${TEST} PUBLIC math_methods geometry_tools structures grid plic ${Boost_LIBRARIES})
add_test(NAME ${TEST} COMMAND ${TEST})