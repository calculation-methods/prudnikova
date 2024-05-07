#ifndef PLIC_H
#define PLIC_H

#include "grids.h"

// Функция 1
bool lineLineIntersection(LineSegment f1, LineSegment f2, FunctionPoint& ans);

// Функция 2
bool pointLocation(const FunctionPoint& point, const LineSegment& lf);

// Функция 3: Сбор вершин многоугольника
Polygon collectPolygonVertices(const LineSegment& lf, const Grid& g);

#endif