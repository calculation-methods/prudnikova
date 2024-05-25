# find_package(Boost)
# include_directories(${Boost_INCLUDE_DIR})

add_executable(check_area_calculation area.cpp ../structures.cpp ../PLIC.cpp ../linear.cpp)

add_test(NAME unit-tests COMMAND check_area_calculation)
