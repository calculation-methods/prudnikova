#include "flux.h"
#include "structures.h"

polygon volume_flux_polygon (const double offset, const grid_edge &edge)
{
  const point first = edge.first;
  const point second = edge.second;
  const point third = second - offset;
  const point fourth = first - offset;

  if ((edge.orientation() == orientation::vertical && velocity < 0.) ||
      (edge.orientation() == orientation::horizontal && velocity > 0.))
    return {first, fourth, third, second};

  return {first, second, third, fourth};
}

double compute_flux(const line_equation &interface, const grid_edge &edge, const double velocity, const double delta_t)
{
  const double offset = velocity * delta_t;
  const polygon full_flux_polygon = volume_flux_polygon (offset, edge);
  const polygon liquid_flux_polygon = PLIC::collect_polygon_vertices(interface, full_flux_polygon);
  const double liquid_flux = PLIC::polygon_area (liquid_flux_polygon);

  return liquid_flux;
}
