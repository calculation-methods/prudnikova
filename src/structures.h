#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <vector>
#include <cmath>
#include <iostream>

#include "grid.h"

using vector_2d = std::vector<std::vector<double>>;

struct table_function {
    vector_2d points;
    rectangular_grid f_grid;

    // Конструктор по умолчанию (без параметров)
    table_function();

    // Конструктор с параметром для инициализации размера вектора
    table_function(int n, int m);

    table_function& operator=(const table_function& other);

    double value (const int i, const int j) { return points[i][j]; }

    point gradient (const int i, const int j) const;
};

struct computation_params {
    table_function velocity;
    double delta_t; 
    rectangular_grid grid_f;

    // Дефолтный конструктор
    computation_params();

    // Конструктор с параметрами
    computation_params(table_function vel, double dt, rectangular_grid grid_f);
};

bool operator==(const table_function& lhs, const table_function& rhs);

bool operator==(const computation_params& lhs, const computation_params& rhs);

#endif

