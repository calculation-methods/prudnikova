#include "linear.h"

double compute_y(const line_segment& lf, double x) 
{
    const double n_x = lf.n.x;
    const double n_y = lf.n.y;

    // Вычисляем значение y по формуле линейной функции: n_x * x + n_y * y - rho = 0
    return (lf.rho - n_x * x) / n_y;
}


double compute_x(const line_segment& lf, double y) 
{
    const double n_x = lf.n.x;
    const double n_y = lf.n.y;

    // Вычисляем значение x по формуле линейной функции: n_x * x + n_y * y - rho = 0
    return (lf.rho - n_y * y) / n_x;
}