find_package(Boost COMPONENTS unit_test_framework)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(linear_equations slau.cpp)
target_link_libraries(linear_equations PUBLIC math_methods)
target_include_directories (linear_equations PUBLIC ${PROJECT_SOURCE_DIR}/math)
add_test(NAME solve_linear_equation_test COMMAND linear_equations)

# set(TEST_SOURCES1
#     area.cpp
#     ${CMAKE_CURRENT_SOURCE_DIR}/area.cpp
#     ${CMAKE_SOURCE_DIR}/structures.cpp
#     ${CMAKE_SOURCE_DIR}/PLIC.cpp
# )

# set(TEST_SOURCES2
#     PLIC.cpp
#     ${CMAKE_CURRENT_SOURCE_DIR}/PLIC.cpp
#     ${CMAKE_SOURCE_DIR}/structures.cpp
#     ${CMAKE_SOURCE_DIR}/PLIC.cpp
# )

# set(TEST_SOURCES3
#     linear.cpp
#     ${CMAKE_CURRENT_SOURCE_DIR}/linear.cpp
#     ${CMAKE_SOURCE_DIR}/structures.cpp
#     ${CMAKE_SOURCE_DIR}/PLIC.cpp
# )

# add_executable(polygon_area ${TEST_SOURCES1})
# add_executable(PLIC ${TEST_SOURCES2})
# add_executable(linear_solver ${TEST_SOURCES3})

#target_link_libraries(polygon_area ${Boost_LIBRARIES})
#target_link_libraries(PLIC ${Boost_LIBRARIES})

# add_test(NAME unit-tests1 COMMAND polygon_area)
# add_test(NAME unit-tests2 COMMAND PLIC)
# add_test(NAME unit-tests3 COMMAND linear_solver)
