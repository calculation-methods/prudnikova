#ifndef APPROXIMATION_H
#define APPROXIMATION_H

#include "area.h"
#include "operations.h"

double bisectionMethod(const Grid& g, double value, const FunctionPoint& n, int i);


// Построение линейной аппроксимации
LineSegment buildLinearApproximation(const TableFunction& f, Grid g, int i);


#endif
