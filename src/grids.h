#ifndef GRIDS_H
#define GRIDS_H

#include "linear.h"

// Функция, вычисляющая координаты вершин ij-ой ячейки сетки g
polygon polygon_from_cell (const grid& g, const int i, const int j);

std::vector<line_segment> line_segment_from_cell(grid g, const int i, const int j);

bool is_point_in_cell(const point& vertex, const grid& g, const int i, const int j);

#endif