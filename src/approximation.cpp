#include "approximation.h"

point compute_normal(const table_function &f, int i, int j)
{
  const double delta_x = f.f_grid.delta_x;
  const double delta_y = f.f_grid.delta_y;

  point normal;
  normal.x = 0.5 * (f[i + 1][j] - f[i - 1][j]) / delta_x;
  normal.y = 0.5 * (f[i][j + 1] - f[i][j - 1]) / delta_y;

  return normal;
}

double compute_rho(const double etalon_value, const polygon &cell, const line_equation &slider_line)
{
  std::vector<std::pair<double, double>> vof_vs_rho;
  for (const point &vertex : cell)
  {
    const double rho = slider_line.compute_distance (vertex)
    const double vof = PLIC::collect_polygon_vertices(line_equation (slider_line.x, slider_line.y, -rho), cell);
    rho.push_back (vor, rho);
  }

  auto sort_by_vof = [] (const auto &a, const auto &b) { return a.vof < b.vof; }; 
  double rho_min = ranges::min (rho, sort_by_vof);
  double rho_max = ranges::max (rho, sort_by_vof);

  constexpr double eps = 1e-6;
  while (std::abs(rho_max - rho_min) > eps) {
      const double rho_mean = 0.5 * (rho_min + rho_max);
      const line_equation new_line(n.x, n.y, -rho_mean);
      const new_vof = PLIC::collect_polygon_vertices(new_line, cell);
      if (new_vof > etalon_vof)
        rho_max = rho_mean;
      else
        rho_min = rho_mean;
  }

  return (rho_max + rho_min) / 2;
}

line_segment build_linear_approximation(const table_function &f, int i, int j)
{
    const point normal = compute_normal(f, i, j);

    const grid &g = f.f_grid;
    const double liquid_volume = f.points[i][j] * g.delta_x * g.delta_y;
    const double rho = compute_rho(liquid_volume, grid.get_cell (i,j), normal);

    return line_equation (normal.x, normal.y, -rho);
}

