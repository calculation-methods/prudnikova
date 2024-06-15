#ifndef TIME_H
#define TIME_H

#include "flux.h"
#include "structures.h"

using interface_field = std::vector<std::vector<line_equation>>;

class solver
{
  table_function velocity_x;
  table_function velocity_y;

  grid f_grid;

  double delta_t;
  double start_time;

  void time_step(table_function &vof_0) const;
  interface_field compute_interfaces (const table_function &vof) const;
  table_function compute_flux_x(const interface_field &interfaces, const table_function &velocity_x) const;
  table_function compute_flux_y(const interface_field &interfaces, const table_function &velocity_y) const;

public:
  solver(const table_function &velocity_x_ext, const table_function &velocity_y_ext, const grid &grid_ext, const double delta_t_ext)
    : velocity_x(velocity_x_ext), velocity_y(velocity_y_ext), f_grid(grid_ext), delta_t(delta_t_ext) {};

  table_function time_integration(const table_function &vof_0, const double finish_time) const;
};

#endif
