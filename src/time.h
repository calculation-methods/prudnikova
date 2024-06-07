#ifndef ASSEMBLE_H
#define ASSEMBLE_H

#include "flux.h"
#include "structures.h"

using interface_field = std::vector<std::vector<line_equation>>;

namespace solver
{
  interface_field compute_interfaces (const table_function &vof, const grid &f_grid);
  table_function compute_flux_x(const interface_field &interfaces, const table_function &velocity_x, const grid &f_grid);
  table_function compute_flux_x(const interface_field &interfaces, const table_function &velocity_y, const grid &f_grid);
  void time_step(const computation_params &params, const grid &cur_grid, table_function &f);
  void time_integration(const computation_params &params, const grid& f_grid, table_function &vof_0);
}

#endif
