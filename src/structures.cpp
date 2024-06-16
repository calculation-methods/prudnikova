#include "structures.h"

table_function& table_function::operator=(const table_function& other) 
{
    if (this != &other) {
        points = other.points;
        f_grid = other.f_grid;
    }
    return *this;
}

table_function::table_function() : points(0) {}

table_function::table_function(int n, int m) : points(n, std::vector<double>(m, 0.0)), f_grid(n, m) {}

bool operator==(const table_function& lhs, const table_function& rhs)
{
    if (lhs.points.size() != rhs.points.size()) return false;
    for (size_t i = 0; i < lhs.points.size(); ++i)
    {
        if (lhs.points[i].size() != rhs.points[i].size()) return false;
        for (size_t j = 0; j < lhs.points[i].size(); ++j)
        {
            if (std::fabs(lhs.points[i][j] - rhs.points[i][j]) >= 1e-10) return false;
        }
    }
    return true;
}

computation_params::computation_params() : velocity(), delta_t(0.0), grid_f() {}

computation_params::computation_params(table_function vel, double dt, rectangular_grid g)
        : velocity(vel), delta_t(dt), grid_f(g) {}

bool operator==(const computation_params& lhs, const computation_params& rhs)
{
    return lhs.velocity == rhs.velocity
        && std::fabs(lhs.delta_t - rhs.delta_t) < 1e-10
        && lhs.grid_f == rhs.grid_f;
}

point gradient (const int i, const int j) const
{
  const vector_2d &cells = points;
  const rectangular_grid &grid = f_grid;

  const int imax = grid.x_size;
  const int jmax = grid.y_size;

  const int i_next = (i + 1) % imax;
  const int i_prev = (i - 1) % imax;
  const int j_next = (j + 1) % jmax;
  const int j_prev = (j + 1) % jmax;

  const double delta_x = grid.delta_x;
  const double delta_y = grid.delta_y;

  const double x = 0.5 * (cells[i_next][j] - cells[i_prev][j]) / delta_x;
  const double y = 0.5 * (cells[i][j_next] - cells[i][j_prev]) / delta_y;

  return {x, y};
}

