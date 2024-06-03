#include "PLIC.h"

#include "line_equation.h"

#include <vector>


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
  std::vector<point> result;

  auto is_liquid_point = [&line_eq] (const point &pnt) { return point_to_line_relation(pnt, line_eq); };

  const size_t size = plgn.size ();
  for (size_t i = 0; i < size; ++i)
  {
    const point &begin_edge = plgn[i];
    const point &end_edge = plgn[(i+1) % size];

    if (is_liquid_point(begin_edge))
      result.push_back (begin_edge);

    const bool is_edge_split = is_liquid_point(begin_edge) != is_liquid_point(end_edge);
    if (is_edge_split)
      result.push_back (line_eq.cross (line_eq (begin_edge, end_edge)));
  }

  return polygon (result);
}

double PLIC::polygon_area(const polygon &plgn)
{
  return plgn.area();
}
