#ifndef LINEAR_H
#define LINEAR_H

#include <iostream>

#include "structures.h"

double linearSolve(const LinearFunction& lf, double x) {
    if (lf.n.size() != 2) {
        throw std::invalid_argument("Некорретно введены данные нормали линейной функции");
    }

    double n_x = lf.n[1].x - lf.n[0].x;
    double n_y = lf.n[1].y - lf.n[0].y;

    // Вычисляем значение y по формуле линейной функции: n_x * x + n_y * y + rho = 0
    return - (lf.rho + n_x * x) / n_y;
}


double linearFindX(const LinearFunction& lf, double y) {
    if (lf.n.size() != 2) {
        throw std::invalid_argument("Некорретно введены данные нормали линейной функции");
    }

    double n_x = lf.n[1].x - lf.n[0].x;
    double n_y = lf.n[1].y - lf.n[0].y;

    // Вычисляем значение x по формуле линейной функции: n_x * x + n_y * y + rho = 0
    return - (lf.rho + n_y * y) / n_x;
}

#endif
