#ifndef GRIDS_H
#define GRIDS_H

#include "linear.h"

// Функция, вычисляющая координаты вершин ij-ой ячейки сетки g
Polygon gridCellCoodrs (Grid g, int i, int j);

// Функция, находящая точки пересечения прямой с ij-ой ячейкой сетки
std::vector<FunctionPoint> gridCellLinearIntersection(const LineSegment& lf, const Grid& g, int i, int j);

#endif