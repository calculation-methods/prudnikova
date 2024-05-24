#define BOOST_TEST_MODULE geometry_toolbox
#include <boost/test/included/unit_test.hpp>

#include "../PLIC.h"
#include "../structures.h"
#include "../linear.h"

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
    BOOST_TEST(PLIC::pointLocation(p3, l1)); // граничная точка
    BOOST_TEST(PLIC::pointLocation(p4, l1));
    BOOST_TEST(PLIC::pointLocation(p5, l1)); // граничная точка
    BOOST_TEST(!PLIC::pointLocation(p6, l1));
}

BOOST_AUTO_TEST_CASE(EmptyGrid)
{
    Grid emptyGrid;

    LineSegment line = {FunctionPoint{0, 0}, 1.0};

    Polygon result = PLIC::collectPolygonVertices(line, emptyGrid, 0, 0);

    BOOST_TEST(result.vertexNum == 0);
    BOOST_TEST(result.vertex.size() == 0);
}

BOOST_AUTO_TEST_CASE(LineIntersectsCell)
{
    Grid grid(1.0, 1.0, 3, 3);

    LineSegment line;
    line.n.x = 0;
    line.n.y = 1;
    line.rho = 1;

    Polygon result = PLIC::collectPolygonVertices(line, grid, 1, 1);

    FunctionPoint v1 = {0.0, 1.0};
    FunctionPoint v2 = {2.0, 1.0};

    BOOST_TEST(result.vertexNum == 2);
    BOOST_TEST(result.vertex.size() == 2);
    BOOST_TEST(result.vertex[0] == v1);
    BOOST_TEST(result.vertex[1] == v2);
}

BOOST_AUTO_TEST_CASE(LineOutsideCell)
{
    Grid grid(1.0, 1.0, 3, 3);
    
    LineSegment line;

    line.n.x = 0;
    line.n.y = 1;
    line.rho = 1;

    Polygon result = PLIC::collectPolygonVertices(line, grid, 1, 1);

    BOOST_TEST(result.vertexNum == 0);
    BOOST_TEST(result.vertex.size() == 0);
}
BOOST_AUTO_TEST_SUITE_END()