#ifndef RUNGEKUTTA_H
#define RUNGEKUTTA_H

#include <iostream>
#include <cmath>
#include <vector>

#include "structures.h"
#include "operations.h"


// Функция для решения уравнения переноса методом Рунге-Kутты 2-го порядка
TableFunction rungeKutta(const TableFunction& f, const TableFunction& u, const TableFunction& v, double dt, Grid g); 

#endif