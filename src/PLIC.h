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
    double liquid_area(const line_equation &interface, const polygon &plgn);
    double polygon_area(const polygon &plgn);

    point compute_normal(const table_function &f, int i, int j);
    double compute_rho(const double etalon_value, const polygon &cell, const line_equation &slider_line);
    line_equation build_linear_approximation(const table_function &f, int i, int j);
}


#endif
