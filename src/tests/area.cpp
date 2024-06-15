#include <boost/test/unit_test.hpp>

#include "../line_equation.h"

BOOST_AUTO_TEST_CASE(polygon_area)
{
  const point point1 = {0,0};
  const point point2 = {1,0};
  const point point3 = {1,1};
  const point point4 = {0,1};

  const std::vector<point> points1 = {point1, point2, point3, point4};
  const std::vector<point> points2 = {point1, point2, point3};

  const polygon square(points1);
  const double square_area = square.area ();
  BOOST_TEST(square_area == 1.);

  const polygon triangle(points2);
  const double triangle_area = triangle.area ();
  BOOST_TEST(triangle_area == 0.5);
}

