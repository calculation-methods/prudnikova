#ifndef OPERATIONS_H
#define OPERATIONS_H

#include "structures.h"

// df/dx в точке
double df_dx(const TableFunction& f, const Grid& g, int i, int j);

// df/dy в точке
double df_dy(const TableFunction& f, const Grid& g, int i, int j);

// df/dx с результатами на плоскости
TableFunction df_dx_(const TableFunction& f, const Grid& g);

// df/dy с результатами на плоскости
TableFunction df_dy_(const TableFunction& f, const Grid& g);

std::vector<TableFunction> nabla(const TableFunction& f, const Grid& g);

// Дивергенция в точке
double divergence(const TableFunction& f, const Grid& g, int i, int j);

#endif
