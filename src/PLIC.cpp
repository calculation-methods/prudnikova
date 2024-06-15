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

double PLIC::cut_polygon_by_interface(const line_equation &interface, const polygon &plgn)
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
