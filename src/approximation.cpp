#include "approximation.h"
#include "PLIC.h"

point compute_normal(const table_function &f, int i, int j)
{
  const double delta_x = f.f_grid.delta_x;
  const double delta_y = f.f_grid.delta_y;

  point normal;
  normal.x = 0.5 * (f.points[i + 1][j] - f.points[i - 1][j]) / delta_x;
  normal.y = 0.5 * (f.points[i][j + 1] - f.points[i][j - 1]) / delta_y;

  return normal;
}

double compute_rho(const double etalon_value, const polygon &cell, const line_equation &slider_line)
{
  std::vector<std::pair<double, double>> vof_vs_rho;
  for (const point &vertex : cell)
  {
    const double rho = slider_line.compute_distance (vertex);
    const double vof = PLIC::cut_polygon_by_interface(line_equation (slider_line.a, slider_line.b, -rho), cell);
    vof_vs_rho.emplace_back (vof, rho);
  }

  auto mean_value = [] (const double a, const double b) { return 0.5 * (a + b); };

  auto sort_by_vof = [] (const std::pair<double, double> &a, const std::pair<double, double> &b) { return a.first < b.first; };

  auto minmax_rho = std::minmax_element (vof_vs_rho.begin(), vof_vs_rho.end(), sort_by_vof);
  double rho_min = minmax_rho.first->second;
  double rho_max = minmax_rho.second->second;

  constexpr double eps = 1e-6;
  while (std::abs(rho_max - rho_min) > eps) {
      const double rho_mean = mean_value(rho_min, rho_max);
      const line_equation new_line(slider_line.a, slider_line.b, -rho_mean);
      const double new_vof = PLIC::cut_polygon_by_interface(new_line, cell);
      if (new_vof > etalon_value)
        rho_max = rho_mean;
      else
        rho_min = rho_mean;
  }

  return mean_value(rho_min, rho_max);
}

line_equation build_linear_approximation(const table_function &f, int i, int j)
{
    const rectangular_grid &g = f.f_grid;
    const double liquid_volume = f.points[i][j] * g.delta_x * g.delta_y;
    const point normal = compute_normal(f, i, j);
    const line_equation line (normal.x, normal.y, 0.);

    const double rho = compute_rho(liquid_volume, g.get_cell (i,j), line);

    return line_equation (normal.x, normal.y, -rho);
}

