#ifndef PLIC_H
#define PLIC_H
#include <algorithm> 
#include <optional>

#include "grids.h"

namespace PLIC
{
    constexpr double epsilon = 1e-10;

    std::optional<point> line_line_intersection(const line_segment &f1, const line_segment &f2);
    bool point_to_line_relation(const point &point, const line_segment &lf);
    polygon collect_polygon_vertices(const line_segment &lf, const grid &g, const int i, const int j);
    double polygon_area(const polygon& p);
}

#endif