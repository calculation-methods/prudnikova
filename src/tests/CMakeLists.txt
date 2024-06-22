find_package(Boost COMPONENTS unit_test_framework)
include_directories(${Boost_INCLUDE_DIRS})

# if(ENABLE_COVERAGE)
  # set compiler flags
  set(CMAKE_CXX_FLAGS "-O0 -coverage")

  # find required tools
  find_program(LCOV lcov REQUIRED)
  find_program(GENHTML genhtml REQUIRED)

  # add coverage target
  add_custom_target(coverage
    # gather data
    COMMAND ${LCOV} --directory . --capture --output-file coverage.info
    # generate report
    COMMAND ${GENHTML} --demangle-cpp -o coverage coverage.info
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
# endif()

set(TEST unit_tests)
add_executable(${TEST} slau.cpp area.cpp PLIC.cpp)
target_link_libraries(${TEST} PUBLIC math_methods geometry_tools structures grid plic ${Boost_LIBRARIES})
add_test(NAME ${TEST} COMMAND ${TEST})

