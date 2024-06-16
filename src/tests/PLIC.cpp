#define BOOST_TEST_MODULE geometry_toolbox
#include <boost/test/included/unit_test.hpp>

#include "../PLIC.h"
#include "../structures.h"

// BOOST_AUTO_TEST_SUITE(PLICTests)

// BOOST_AUTO_TEST_CASE(LineLineIntersectionTest)
// {
//     line_segment l1 = {{1.0, 1.0}, 2.0};
//     line_segment l2 = {{1.0, -1.0}, -1.0};
//     point p;
//     std::optional intersect = PLIC::line_line_intersection(l1, l2);
//     BOOST_TEST(*intersect);
//     BOOST_TEST(std::fabs((*intersect).x - 0.5) < 1e-10);
//     BOOST_TEST(std::fabs((*intersect).y - 1.5) < 1e-10);

// }

// BOOST_AUTO_TEST_CASE(PointLocationTest)
// {
//     line_segment l1 = {{1.0, 1.0}, 2.0};
//     point p1 = {3.0, 5.0};
//     point p2 = {0.0, 0.0};
//     point p3 = {0.0, 2.0};
//     point p4 = {2.0, 2.0};
//     point p5 = {2.0, 0.0};
//     point p6 = {0.0, 1.0};
//     BOOST_TEST(PLIC::point_to_line_relation(p1, l1));
//     BOOST_TEST(!PLIC::point_to_line_relation(p2, l1));
//     BOOST_TEST(PLIC::point_to_line_relation(p3, l1)); // boundary point
//     BOOST_TEST(PLIC::point_to_line_relation(p4, l1));
//     BOOST_TEST(PLIC::point_to_line_relation(p5, l1)); // boundary point
//     BOOST_TEST(!PLIC::point_to_line_relation(p6, l1));
// }

// BOOST_AUTO_TEST_CASE(EmptyGrid)
// {
//     rectangular_grid emptyGrid;

//     line_segment line = {{0, 0}, 1.0};

//     polygon result = PLIC::collect_polygon_vertices(line, emptyGrid, 0, 0);

//     BOOST_TEST(result.vertex_num == 0);
//     BOOST_TEST(result.vertex.size() == 0);
// }

// BOOST_AUTO_TEST_CASE(LineIntersectsCell)
// {
//     rectangular_grid grid(1.0, 1.0, 3, 3);

//     line_segment line = {{0, 1}, 1};

//     polygon result = PLIC::collect_polygon_vertices(line, grid, 1, 1);

//     point v1 = {1.0, 1.0};
//     point v2 = {2.0, 1.0};
//     point v3 = {2.0, 2.0};
//     point v4 = {1.0, 2.0};

//     BOOST_TEST(result.vertex_num == 4);
//     BOOST_TEST(result.vertex.size() == 4);
//     BOOST_TEST(result.vertex[0] == v1);
//     BOOST_TEST(result.vertex[1] == v2);
//     BOOST_TEST(result.vertex[2] == v3);
//     BOOST_TEST(result.vertex[3] == v4);
// }

// BOOST_AUTO_TEST_CASE(form_polygon)
// {
//     line_segment line = {{1, 1}, 0.5};
//     point v1 = {0.5, 0};
//     point v2 = {1, 0};
//     point v3 = {1, 1};
//     point v4 = {0, 1};
//     point v5 = {0, 0.5};

//     rectangular_grid grid(1.0, 1.0, 3, 3);

//     polygon result = PLIC::collect_polygon_vertices(line, grid, 0, 0);
//     BOOST_TEST(result.vertex[0] == v1);
//     BOOST_TEST(result.vertex[1] == v2);
//     BOOST_TEST(result.vertex[2] == v3);
//     BOOST_TEST(result.vertex[3] == v4);
//     BOOST_TEST(result.vertex[4] == v5);
// }
// BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(interface_cutting)
//  
// y ^  
//   |    p1 - p2 - p3
//   |    |    |    |
//   |    p4 - p5 - p6
//   |    |    |    |
//   |    p7 - p8 - p9  
//   |
//   0-------------------> 
//                      x
BOOST_AUTO_TEST_CASE(cut_triangle)
{
	const point p1 (1, 3);
	const point p2 (2, 3);
	const point p3 (3, 3);
	const point p4 (1, 2);
	const point p5 (2, 2);
	const point p6 (3, 2);
	const point p7 (1, 1);
	const point p8 (2, 1);
	const point p9 (3, 1);

  const polygon cell {p1, p7, p9, p3};

  const line_equation interface (p2, p4);
  const double liquid_area = PLIC::liquid_area(interface, cell);
  BOOST_TEST(liquid_area == 3.5);

  const line_equation interface_revert (p4, p2);
  const double gas_area = PLIC::liquid_area(interface, cell);
  BOOST_TEST(gas_area == 0.5);

  const line_equation interface (p3, p7);
  const double liquid_area = PLIC::liquid_area(interface, cell);
  BOOST_TEST(liquid_area == 3.5);

  const line_equation interface_revert (p7, p3);
  const double gas_area = PLIC::liquid_area(interface, cell);
  BOOST_TEST(gas_area == 0.5);
}

BOOST_AUTO_TEST_CASE(cut_trapezoid)
{
	const point p1 (1, 3);
	const point p2 (2, 3);
	const point p3 (3, 3);
	const point p4 (1, 2);
	const point p5 (2, 2);
	const point p6 (3, 2);
	const point p7 (1, 1);
	const point p8 (2, 1);
	const point p9 (3, 1);

  const polygon cell {p1, p7, p9, p3};

  const line_equation interface (p4, p6);
  const double liquid_area = PLIC::liquid_area(interface, cell);
  BOOST_TEST(liquid_area == 2.);

  const line_equation interface_revert (p6, p4);
  const double gas_area = PLIC::liquid_area(interface, cell);
  BOOST_TEST(gas_area == 2.);

  const line_equation interface (p4, p3);
  const double liquid_area = PLIC::liquid_area(interface, cell);
  BOOST_TEST(liquid_area == 2.);

  const line_equation interface_revert (p3, p4);
  const double gas_area = PLIC::liquid_area(interface, cell);
  BOOST_TEST(gas_area == 2.);
}
BOOST_AUTO_TEST_SUITE_END()