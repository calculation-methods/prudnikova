#ifndef APPROXIMATION_H
#define APPROXIMATION_H

#include "operations.h"
#include "line_equation.h"

point compute_normal(const table_function &f, int i, int j);
double compute_rho(const double etalon_value, const polygon &cell, const line_equation &slider_line);
line_equation build_linear_approximation(const table_function &f, int i, int j);

#endif
