#include "PLIC.h"

#include <vector>

#include "line_equation.h"
#include "structures.h"

std::optional<point> PLIC::line_line_intersection(const line_equation &line_eq1, const line_equation &line_eq2)
{
  return line_eq1.cross(line_eq2);
}

bool PLIC::point_to_line_relation(const point &pnt, const line_equation &line_eq)
{
  return line_eq.substitute(pnt) >= 0.;
}

double PLIC::liquid_area(const line_equation &interface, const polygon &plgn)
{
  std::vector<point> result;

  auto is_liquid_point = [&interface] (const point &pnt) { return PLIC::point_to_line_relation(pnt, interface); };

  const size_t size = plgn.size ();
  for (size_t i = 0; i < size; ++i)
  {
    const point &begin_edge = plgn[i];
    const point &end_edge = plgn[(i+1) % size];

    if (is_liquid_point(begin_edge))
      result.push_back (begin_edge);

    const bool is_edge_split = is_liquid_point(begin_edge) != is_liquid_point(end_edge);
    if (is_edge_split)
      result.push_back (*PLIC::line_line_intersection(interface, line_equation (begin_edge, end_edge)));
  }

  return PLIC::polygon_area (polygon (result));
}

double PLIC::polygon_area(const polygon &plgn)
{
  return plgn.area();
}

point PLIC::compute_normal(const table_function &vof, const int i, const int j)
{
  return vof.gradient(i, j);
}

double PLIC::compute_rho(const double etalon_value, const polygon &cell, const line_equation &slider_line)
{
  std::vector<std::pair<double, double>> vof_vs_rho;
  for (const point &vertex : cell)
  {
    const double rho = slider_line.compute_distance (vertex);
    const double vof = PLIC::liquid_area(line_equation (slider_line.a, slider_line.b, -rho), cell);
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
      const double new_vof = PLIC::liquid_area(new_line, cell);
      if (new_vof > etalon_value)
        rho_max = rho_mean;
      else
        rho_min = rho_mean;
  }

  return mean_value(rho_min, rho_max);
}

line_equation PLIC::build_linear_approximation(const table_function &f, int i, int j)
{
    const rectangular_grid &g = f.f_grid;
    const double liquid_volume = f.points[i][j] * g.delta_x * g.delta_y;
    const point normal = compute_normal(f, i, j);
    const line_equation line (normal.x, normal.y, 0.);

    const double rho = compute_rho(liquid_volume, g.get_cell (i,j), line);

    return line_equation (normal.x, normal.y, -rho);
}
