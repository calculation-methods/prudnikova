#include "linear.h"

double linearSolve(const LineSegment& lf, double x) {
    const double n_x = lf.n.x;
    const double n_y = lf.n.y;

    // Вычисляем значение y по формуле линейной функции: n_x * x + n_y * y + rho = 0
    return - (lf.rho + n_x * x) / n_y;
}


double linearFindX(const LineSegment& lf, double y) {
    const double n_x = lf.n.x;
    const double n_y = lf.n.y;

    // Вычисляем значение x по формуле линейной функции: n_x * x + n_y * y + rho = 0
    return - (lf.rho + n_y * y) / n_x;
}