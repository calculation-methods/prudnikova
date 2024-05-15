#define BOOST_TEST_MODULE geometry_toolbox
#include <boost/test/included/unit_test.hpp>

#include "../PLIC.h"
#include "../structures.h"

BOOST_AUTO_TEST_CASE(polygon_area)
{
  const FunctionPoint point1 = {0,0};
  const FunctionPoint point2 = {1,0};
  const FunctionPoint point3 = {1,1};
  const FunctionPoint point4 = {0,1};

  const std::vector<FunctionPoint> points1 = {point1, point2, point3, point4};
  const std::vector<FunctionPoint> points2 = {point1, point2, point3};

  const Polygon square(points1);
  const double square_area = PLIC::polygonArea (square);
  BOOST_TEST(square_area == 1.);

  const Polygon triangle(points2);
  const double triangle_area = PLIC::polygonArea (triangle);
  BOOST_TEST(triangle_area == 0.5);
}
