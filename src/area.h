#ifndef AREA_H
#define AREA_H

#include "grids.h"
#include "PLIC.h"

// Подсчёт занимаемой фазой площади 
double phaseArea(const TableFunction& func, Grid g, int i, int j);

// Функция, вычисляющая отношение изначальной площади первой фазы к площади ячейки сетки
double calculatePhaseRatio(const TableFunction& func, Grid g, int i, int j);

double approxArea(const Grid& g, double rho, const FunctionPoint& n, int i, int j, double value);

#endif