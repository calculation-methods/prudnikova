#include "grid.h"

#include "structures.h"
#include "line_equation.h"

orientation grid_edge::get_orientation() const
{
  if (start.x == end.x)
    return orientation::vertical;
  if (start.y == end.y)
    return orientation::horizontal;
  return orientation::other;
}

rectangular_grid::rectangular_grid() {}

rectangular_grid::rectangular_grid(double dx, double dy, size_t sizex, size_t sizey) : delta_x(dx), delta_y(dy), x_size(sizex), y_size(sizey) {}

rectangular_grid::rectangular_grid(size_t sizex, size_t sizey) : x_size(sizex), y_size(sizey) {}

polygon rectangular_grid::get_cell (const int i, const int j) const
{
  const point upper_left = {delta_x * i, delta_y * j};
  const point down_left  = {delta_x * i, delta_y * j};
  const point down_right = {delta_x * i, delta_y * j};
  const point upper_right= {delta_x * i, delta_y * j};

  return {upper_left, down_left, down_right, upper_right};
}

grid_edge rectangular_grid::get_vertical_edge (const int i, const int j) const
{
  const double x_coord = i * delta_x;
  const double y_coord = (j - 1) * delta_y;

  const point start (x_coord, y_coord);
  const point end   (x_coord, y_coord + delta_y);

  return {start, end};
}

grid_edge rectangular_grid::get_horizontal_edge (const int i, const int j) const
{
  const double x_coord = (i - 1) * delta_x;
  const double y_coord = j * delta_y;

  const point start (          x_coord, y_coord);
  const point end   (delta_x + x_coord, y_coord);

  return {start, end};
}

rectangular_grid& rectangular_grid::operator=(const rectangular_grid& other) {
    if (this != &other) {
        delta_x = other.delta_x;
        delta_y = other.delta_y;
        x_size = other.x_size;
        y_size = other.y_size;
    }
    return *this;
}

bool operator==(const rectangular_grid& lhs, const rectangular_grid& rhs)
{
    return std::fabs(lhs.delta_x - rhs.delta_x) < 1e-10
        && std::fabs(lhs.delta_y - rhs.delta_y) < 1e-10
        && lhs.x_size == rhs.x_size
        && lhs.y_size == rhs.y_size;
}