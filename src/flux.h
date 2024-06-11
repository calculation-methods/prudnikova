#ifndef FLUX_H
#define FLUX_H

#include "PLIC.h"
#include "approximation.h"

polygon volume_flux_polygon (const point &offset, const grid_edge &edge);
double compute_flux(const line_equation &interface, const grid_edge &edge, const double velocity, const double delta_t);

#endif
