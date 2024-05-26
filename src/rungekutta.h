#ifndef RUNGEKUTTA_H
#define RUNGEKUTTA_H

#include <iostream>
#include <cmath>
#include <vector>

#include "structures.h"
#include "operations.h"


// Функция для решения уравнения переноса методом Рунге-Kутты 2-го порядка
table_function runge_kutta(const table_function& f, const table_function& u, const table_function& v, double dt, grid g); 

#endif