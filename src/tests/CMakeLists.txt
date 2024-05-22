find_package(Boost)
add_executable(check_area_calculation area.cpp ../structures.cpp ../PLIC.cpp ../linear.cpp)

add_test(NAME unit-tests COMMAND check_area_calculation)
