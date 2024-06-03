#include "PLIC.h"

#include "line_equation.h"


std::optional<point> PLIC::line_line_intersection(const line_equation &line_eq1, const line_equation &line_eq2)
{
  return line_eq1.cross(line_eq2);
}

bool PLIC::point_to_line_relation(const point &pnt, const line_equation &line_eq)
{
  return line_eq.substitute(pnt) >= 0.;
}

polygon PLIC::collect_polygon_vertices(const line_equation &line_eq, const polygon &plgn)
{
  polygon result;

  auto is_liquid_point = [&line_eq] (const point &pnt) { return line_eq.substitute (plgn) >= 0.; };

  std::vector<bool> is_liquid_vertex;
  for (const point &curr_pnt : plgn.vertexes)
    is_liquid_vertex.push_back (is_liquid_point (plgn[i]));

  for (int i = 0; i < size; ++i)
  {
    const point start_vertex = plgn[i];
    const point end_vertex = plgn[i+1];

    const bool both_vertex_liquid = is_liquid_vertex[i] && is_liquid_vertex[i+1];
    if (both_vertex_liquid)
    {
      result.push_back (start_vertex);
      continue;
    }

    const bool only_start_vertex_liquid = is_liquid_vertex[i];
    if (only_start_vertex_liquid)
    {
      result.push_back (start_vertex);
      result.push_back (line_eq.cross (line_eq (start_vertex, end_vertex)));
    }

    const bool only_end_vertex_liquid = is_liquid_vertex[i];
    if (only_end_vertex_liquid)
    {
      result.push_back (line_eq.cross (line_eq (start_vertex, end_vertex)));
      result.push_back (end_vertex);
    }
  }

  return result;
}

double PLIC::polygon_area(const polygon &plgn)
{
  return plgn.area();
}
