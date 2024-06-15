#ifndef GRID_H
#define GRID_H

#include "line_equation.h"

enum class orientation
{
  horizontal,
  vertical,
  other
};

struct grid_edge
{
  point start;
  point end;

  orientation get_orientation() const;
};

struct rectangular_grid {
    double delta_x;
    double delta_y;

    size_t x_size;
    size_t y_size;

    rectangular_grid();

    rectangular_grid(double dx, double dy, size_t sizex, size_t sizey);

    rectangular_grid(size_t sizex, size_t sizey);

    polygon get_cell (const int i, const int j) const;

    grid_edge get_vertical_edge (const int i, const int j) const;
    grid_edge get_horizontal_edge (const int i, const int j) const;

    rectangular_grid& operator=(const rectangular_grid& other);
};

bool operator==(const rectangular_grid& lhs, const rectangular_grid& rhs);

#endif /* GRID_H */
