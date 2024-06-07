#ifndef APPROXIMATION_H
#define APPROXIMATION_H

#include <limits>

#include "area.h"
#include "operations.h"
#include "line_equation.h"

double bisection_method(const grid &g, double value, const point &n, const int i, const int j);

line_equation build_linear_approximation(const table_function &f, int i, int j);


#endif
