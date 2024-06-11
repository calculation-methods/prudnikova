#ifndef PLIC_H
#define PLIC_H
#include <algorithm>
#include <optional>

#include "structures.h"

class line_equation;

namespace PLIC
{
    constexpr double epsilon = 1e-10;

    std::optional<point> line_line_intersection(const line_equation &f1, const line_equation &f2);
    bool point_to_line_relation(const point &pnt, const line_equation &line_eq);
    double cut_polygon_by_interface(const line_equation &interface, const polygon &plgn);
    double polygon_area(const polygon &plgn);
}

#endif
