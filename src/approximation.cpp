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

    if (i == 0 && i < f.points.size()) {
        for (size_t j = i; j < i + 2; j++) {
            n.x += df_dx(f, g, i);
            n.y += df_dy(f, g, i);
        }
    } else if (i == f.points.size()) {
        for (size_t j = i - 1; j < i; j++) {
            n.x += df_dx(f, g, i);
            n.y += df_dy(f, g, i);
        }
    } else {
        for (size_t j = i - 1; j < i + 2; j++) {
            n.x += df_dx(f, g, i);
            n.y += df_dy(f, g, i);
        }
    }

    n.x /= std::sqrt(n.x * n.x + n.y * n.y);
    n.y /= std::sqrt(n.x * n.x + n.y * n.y);

    double value = calculatePhaseRatio(f, g, i, j);

    LineSegment lf;

    double rho = bisectionMethod(g, value, n, i, j);

    lf.rho = rho;
    lf.n = n;

    return lf;
}