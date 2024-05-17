#include "approximation.h"

double bisectionMethod(const Grid& g, double value, const FunctionPoint& n, int i, int j) {
    double a = -g.delta_x * std::max(std::abs(n.x), std::abs(n.y));
    double b = g.delta_x * std::max(std::abs(n.x), std::abs(n.y));
    double eps = 1e-6;
    double fa = approxArea(g, a, n, i, j, value);
    double fb = approxArea(g, b, n, i, j, value);

    if (fa == 0) {
        return a;
    }
    if (fb == 0) {
        return b;
    }
    if (fa * fb > 0) {
        // Решение не существует на данном интервале
        return NAN;
    }

    while (std::abs(b - a) > eps) {
        double c = (a + b) / 2;
        double fc = approxArea(g, c, n, i, j, value);
        if (fc == 0) {
            return c;
        }
        if (fa * fc < 0) {
            b = c;
        } else {
            a = c;
            fa = fc;
        }
    }

    return (a + b) / 2;
}

// Построение линейной аппроксимации
LineSegment buildLinearApproximation(const TableFunction& f, Grid g, int i, int j) {
    FunctionPoint n;
    n.x = 0;
    n.y = 0;
    
    for (size_t i0 = i - 1; i0 < i + 2; i0++) {
        for (size_t j0 = j - 1; j0 < j + 2; j0++) {
            n.x += df_dx(f, g, i0, j0);
            n.y += df_dy(f, g, i0, j0);
        }
    }

    if (n.x) {
        n.x /= std::sqrt(n.x * n.x + n.y * n.y);
    }
    if (n.y) {
        n.y /= std::sqrt(n.x * n.x + n.y * n.y);
    }

    LineSegment lf;

    const double rho = bisectionMethod(g, f.points[i][j], n, i, j);

    lf.rho = rho;
    lf.n = n;

    return lf;
}