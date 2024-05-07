#ifndef AREA_H
#define AREA_H

#include "grids.h"

double polygonArea(const Polygon& p);


// Подсчёт занимаемой фазой площади 
double phaseArea(const TableFunction& func, Grid g, int i);

// Функция, вычисляющая отношение изначальной площади первой фазы к площади ячейки сетки
double calculatePhaseRatio(const TableFunction& func, Grid g, int i);

double approxArea(const Grid& g, double rho, const FunctionPoint& n, int i, double value);

#endif