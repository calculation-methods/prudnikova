#include "flux.h"
#include "structures.h"

polygon volume_flux_polygon (const double offset, const grid_edge &edge)
{
  const point shift = edge.get_orientation() == orientation::vertical
    ? point(offset, 0.)
    : point(0., offset);

  const point first = edge.start;
  const point second = edge.end;
  const point third = second - shift;
  const point fourth = first - shift;

  if ((edge.get_orientation() == orientation::vertical && offset < 0.) ||
      (edge.get_orientation() == orientation::horizontal && offset > 0.))
    return {first, fourth, third, second};

  return {first, second, third, fourth};
}

double compute_flux(const line_equation &interface, const grid_edge &edge, const double velocity, const double delta_t)
{
  const double offset = velocity * delta_t;
  const polygon full_flux_polygon = volume_flux_polygon (offset, edge);
  const polygon liquid_flux_polygon = PLIC::cut_polygon_by_interface(interface, full_flux_polygon);
  const double liquid_flux = PLIC::polygon_area (liquid_flux_polygon);

  return liquid_flux;
}
