#ifndef PLIC_H
#define PLIC_H
#include <algorithm> 

#include "grids.h"

namespace PLIC {

    // Функция 1
    bool line_line_intersection(line_segment f1, line_segment f2, point& ans);

    // Функция 2
    bool is_point_in_phase1(const point& point, const line_segment& lf);

    // Функция 3: Сбор вершин многоугольника
    polygon collect_polygon_vertices(const line_segment& lf, const grid& g, const int i, const int j);

    // Функция 4: расчёт площади многоугольника
    double polygon_area(const polygon& p);
}

#endif