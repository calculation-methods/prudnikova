#define BOOST_TEST_MODULE geometry_toolbox
#include <boost/test/included/unit_test.hpp>

#include "../PLIC.h"
#include "../structures.h"

BOOST_AUTO_TEST_SUITE(PLICTests)

BOOST_AUTO_TEST_CASE(LineLineIntersectionTest)
{
    LineSegment l1 = {{1.0, 1.0}, 2.0};
    LineSegment l2 = {{1.0, -1.0}, -1.0};
    FunctionPoint p;
    bool intersect = PLIC::lineLineIntersection(l1, l2, p);
    BOOST_TEST(intersect);
    BOOST_TEST(std::fabs(p.x - 1.0) == 0.5);
    BOOST_TEST(std::fabs(p.y) == 1.5);
}

BOOST_AUTO_TEST_CASE(PointLocationTest)
{
    LineSegment l1 = {{1.0, 1.0}, 2.0};
    FunctionPoint p1 = {3.0, 5.0};
    FunctionPoint p2 = {0.0, 0.0};
    FunctionPoint p3 = {0.0, 2.0};
    FunctionPoint p4 = {2.0, 2.0};
    FunctionPoint p5 = {2.0, 0.0};
    FunctionPoint p6 = {0.0, 1.0};
    BOOST_TEST(PLIC::pointLocation(p1, l1));
    BOOST_TEST(!PLIC::pointLocation(p2, l1));
    BOOST_TEST(PLIC::pointLocation(p3, l1));
    BOOST_TEST(PLIC::pointLocation(p4, l1));
    BOOST_TEST(PLIC::pointLocation(p5, l1));
    BOOST_TEST(!PLIC::pointLocation(p6, l1));
}

BOOST_AUTO_TEST_SUITE_END()