#ifndef GRIDS_H
#define GRIDS_H

#include "linear.h"

// Функция, вычисляющая координаты вершин i-ой ячейки сетки g
Polygon gridCellCoodrs (Grid g, int i, int j);

// Функция, находящая точки пересечения прямой с i-ой ячейкой сетки
std::vector<FunctionPoint> gridCellLinearIntersection(const LineSegment& lf, const Grid& g, int i, int j);

#endif