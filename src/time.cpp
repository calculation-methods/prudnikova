#include "line_equation.h"
#include "structures.h"
#include "time.h"

interface_field solver::compute_interfaces (const table_function &vof) const
{
  const int imax = f_grid.x_size;
  const int jmax = f_grid.y_size;

  interface_field interfaces (imax + 1);
  for (int i = 1; i <= imax; i++)
    {
      interfaces[i].resize (jmax + 1);
      for (int j = 0; j < jmax; j++)
        interfaces[i][j] = build_linear_approximation(vof, i, j);
    }

  return interfaces;
}

table_function solver::compute_flux_x(const interface_field &interfaces, const table_function &velocity_x) const
{
  const int imax = f_grid.x_size;
  const int jmax = f_grid.y_size;

  table_function fluxes (imax + 1, jmax + 1);
  for (int i = 0; i <= imax; i++)
    for (int j = 0; j < jmax; j++)
      {
        const double velocity = velocity_x.points[i][j];
        const line_equation &interface = velocity > 0. ? interfaces[i][j] : interfaces[i-1][j];
        const grid_edge edge = f_grid.get_vertical_edge (i, j);

        fluxes.points[i][j] = compute_flux (interface, edge, velocity, delta_t);
      }

  return fluxes;
}

table_function solver::compute_flux_y(const interface_field &interfaces, const table_function &velocity_y) const
{
  const int imax = f_grid.x_size;
  const int jmax = f_grid.y_size;

  table_function fluxes (imax + 1, jmax + 1);
  for (int i = 0; i <= imax; i++)
    for (int j = 1; j <= jmax; j++)
      {
        const double velocity = velocity_y.points[i][j];
        const line_equation &interface = velocity > 0. ? interfaces[i][j] : interfaces[i][j-1];
        const grid_edge edge = f_grid.get_horizontal_edge (i, j);

        fluxes.points[i][j] = compute_flux (interface, edge, velocity, delta_t);
      }

  return fluxes;
}

void solver::time_step(table_function &vof) const
{
    const int imax = f_grid.x_size;
    const int jmax = f_grid.y_size;

    const interface_field interfaces = compute_interfaces (vof);
    const table_function flux_x = compute_flux_x (interfaces, velocity_x);
    const table_function flux_y = compute_flux_y (interfaces, velocity_y);

    for (int i = 1; i <= imax; i++)
      for (int j = 1; j <= jmax; j++)
        {
          const double delta_flux_x = flux_x.points[i][j] - flux_x.points[i - 1][j];
          const double delta_flux_y = flux_y.points[i][j] - flux_y.points[i][j - 1];
          vof.points[i][j] += delta_flux_x + delta_flux_y;
        }
}

table_function solver::time_integration(const table_function &vof_0, const double finish_time) const
{
    table_function vof = vof_0;
    for (double time = start_time; time < finish_time; time += delta_t)
      time_step(vof);
    return vof;
}

