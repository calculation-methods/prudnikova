#ifndef PLIC_H
#define PLIC_H

#include "grids.h"

namespace PLIC {
    // Функция 1
    bool lineLineIntersection(LineSegment f1, LineSegment f2, FunctionPoint& ans);

    // Функция 2
    bool pointLocation(const FunctionPoint& point, const LineSegment& lf);

    // Функция 3: Сбор вершин многоугольника
    Polygon collectPolygonVertices(const LineSegment& lf, const Grid& g);

    // Функция 4: расчёт площади многоугольника
    double polygonArea(const Polygon& p);
}

#endif