find_package(Boost COMPONENTS unit_test_framework)
include_directories(${Boost_INCLUDE_DIRS})

# add_executable(linear_equations slau.cpp)
# target_link_libraries(linear_equations PUBLIC math_methods)
# target_include_directories (linear_equations PUBLIC ${PROJECT_SOURCE_DIR}/math)
# add_test(NAME solve_linear_equation_test COMMAND linear_equations)

# set(TEST_SOURCES1
#     area.cpp
#     ${PROJECT_SOURCE_DIR}/line_equation.cpp
# )
# set(POLYGON_AREA polygon_area)
# add_executable(${POLYGON_AREA} ${TEST_SOURCES1})
# target_link_libraries(${POLYGON_AREA} PUBLIC math_methods)
# target_include_directories (${POLYGON_AREA} PUBLIC "${PROJECT_SOURCE_DIR}/math")
# add_test(NAME ${POLYGON_AREA} COMMAND ${POLYGON_AREA})

set(TEST unit_tests)
add_executable(${TEST} slau.cpp area.cpp PLIC.cpp ../line_equation.cpp ../PLIC.cpp)
target_link_libraries(${TEST} PUBLIC math_methods ${Boost_LIBRARIES})
target_include_directories (${TEST} PUBLIC "${PROJECT_SOURCE_DIR}/math")
add_test(NAME ${TEST} COMMAND ${TEST})