#ifndef GRIDS_H
#define GRIDS_H

#include "linear.h"

// Функция, вычисляющая координаты вершин ij-ой ячейки сетки g
Polygon gridCellCoodrs (const Grid& g, const int i, const int j);

std::vector<LineSegment> buildLineSegmentFromCell(Grid g, const int i, const int j);

#endif