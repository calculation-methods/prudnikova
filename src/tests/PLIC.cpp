#include <boost/test/unit_test.hpp>

#include "../PLIC.h"
#include "../line_equation.h"

// BOOST_AUTO_TEST_SUITE(PLICTests)

BOOST_AUTO_TEST_CASE(LineLineIntersectionTest)
{
  const point p1 (0., 0.); 
  const point p2 (1., 1.); 
  const point p3 (0., 1.); 
  const point p4 (1., 0.); 
  const line_equation line (p1, p2);
  
  BOOST_TEST(PLIC::point_to_line_relation(p1, line) == true);
  BOOST_TEST(PLIC::point_to_line_relation(p2, line) == true);
  BOOST_TEST(PLIC::point_to_line_relation(p3, line) == true);
  BOOST_TEST(PLIC::point_to_line_relation(p4, line) == false);
}

BOOST_AUTO_TEST_SUITE(interface_cutting)
struct points_environment
{
  const point p1 {1, 3};               //  y ^
  const point p2 {2, 3};               //  3 +    p1 - p2 - p3
  const point p3 {3, 3};               //    |    |    |    |
  const point p4 {1, 2};               //  2 +    p4 - p5 - p6
  const point p5 {2, 2};               //    |    |    |    |
  const point p6 {3, 2};               //  1 +    p7 - p8 - p9
  const point p7 {1, 1};               //    |
  const point p8 {2, 1};               //  0 +----+----+----+---->
  const point p9 {3, 1};               //    0    1    2    3    x

  const polygon cell {p1, p7, p9, p3}; // counterclockwise
};

BOOST_FIXTURE_TEST_CASE(cut_triangle, points_environment)
{
  const line_equation interface (p2, p4);
  double liquid_area = PLIC::liquid_area(interface, cell);
  BOOST_TEST(liquid_area == 3.5);

  const line_equation interface_revert (p4, p2);
  double gas_area = PLIC::liquid_area(interface_revert, cell);
  BOOST_TEST(gas_area == 0.5);

  const line_equation interface_half_cell (p3, p7);
  liquid_area = PLIC::liquid_area(interface_half_cell, cell);
  BOOST_TEST(liquid_area == 2.0);

  const line_equation interface_half_cell_revert (p7, p3);
  gas_area = PLIC::liquid_area(interface_half_cell_revert, cell);
  BOOST_TEST(gas_area == 2.0);
}

BOOST_FIXTURE_TEST_CASE(cut_trapezoid, points_environment)
{
  const line_equation interface (p4, p6);
  double liquid_area = PLIC::liquid_area(interface, cell);
  BOOST_TEST(liquid_area == 2.);

  const line_equation interface_revert (p6, p4);
  double gas_area = PLIC::liquid_area(interface_revert, cell);
  BOOST_TEST(gas_area == 2.);

  const line_equation interface_half_cell (p4, p3);
  liquid_area = PLIC::liquid_area(interface_half_cell, cell);
  BOOST_TEST(liquid_area == 3.);

  const line_equation interface_half_cell_revert (p3, p4);
  gas_area = PLIC::liquid_area(interface_half_cell_revert, cell);
  BOOST_TEST(gas_area == 1.);
}

BOOST_AUTO_TEST_SUITE_END()
