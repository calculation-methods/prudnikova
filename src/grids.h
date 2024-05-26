#ifndef GRIDS_H
#define GRIDS_H

#include "linear.h"

// Функция, вычисляющая координаты вершин ij-ой ячейки сетки g
polygon gridCellCoodrs (const grid& g, const int i, const int j);

std::vector<line_segment> buildLineSegmentFromCell(grid g, const int i, const int j);

#endif