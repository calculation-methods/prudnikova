#include "assemble.h"
#include "line_equation.h"
#include "structures.h"
#include "time.h"

interface_field solver::compute_interfaces (const table_function &vof, const grid &f_grid)
{
  const int imax = f_grid.x_size;
  const int jmax = f_grid.y_size;

  interface_field interfaces (imax + 1);
  for (int i = 1; i <= imax; i++)
    {
      interfaces[i].resize (jmax + 1);
      for (int j = 0; j < jmax; j++)
        interface[i][j] = build_linear_approximation(vof, f_grid, i, j);
    }

  return interfaces;
}

table_function solver::compute_flux_x(const interface_field &interfaces, const table_function &velocity_x, const grid &f_grid)
{
  const int imax = f_grid.x_size;
  const int jmax = f_grid.y_size;

  table_function fluxes (imax + 1, jmax + 1);
  for (int i = 0; i <= imax; i++)
    for (int j = 0; j < jmax; j++)
      {
        const double velocity = velocity_x.points[i][j];
        const line_equation &interface = velocity > 0. ? interface[i][j] : interface[i-1][j];
        const grid_edge edge = f_grid.get_vertical_edge (i, j);

        fluxes[i][j] = compute_flux (interface, edge, velocity, delta_t);
      }

  return fluxes;
}

table_function solver::compute_flux_x(const interface_field &interfaces, const table_function &velocity_y, const grid &f_grid)
{
  const int imax = f_grid.x_size;
  const int jmax = f_grid.y_size;

  table_function fluxes (imax + 1, jmax + 1);
  for (int i = 0; i <= imax; i++)
    for (int j = 1; j <= jmax; j++)
      {
        const double velocity = velocity_y.points[i][j];
        const line_equation &interface = velocity > 0. ? interface[i][j] : interface[i][j-1];
        const grid_edge edge = f_grid.get_horizontal_edge (i, j);

        fluxes[i][j] = compute_flux (interface, edge, velocity, delta_t);
      }

  return fluxes;
}

void solver::time_step(const computation_params& vertical, const computation_params& horizontal,  const grid &cur_grid, table_function& f)
{
    const interface_field interfaces = compute_interfaces (f, cur_grid);
    const table_function flux_x = compute_flux_x (interfaces, horizontal.velocity, cur_grid);
    const table_function flux_y = compute_flux_y (interfaces, vertical.velocity, cur_grid);

    for (int i = 1; i <= imax; i++)
      for (int j = 1; j <= jmax; j++)
        {
          const double delta_flux_x = flux_x[i][j] - flux_x[i - 1][j];
          const double delta_flux_y = flux_y[i][j] - flux_y[i][j - 1];
          f.points[i][j] += delta_flux_x + delta_flux_y;
        }
}

table_function solver::time_integration(const table_function& vof_0, const computation_params& params, const grid& f_grid)
{
    const int periods =  / params.delta_t;

    table_function vof = vof_0;
    for (int k = 0; k < periods; k++)
      time_step(params, f_grid, vof);

    return vof;
}

