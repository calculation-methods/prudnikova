#include "approximation.h"

double approx_area(const grid& g, double rho, const point& n, int i, int j, double value)
{
    line_equation lf = {n, rho};

    polygon result = PLIC::collect_polygon_vertices(lf, g.get_cell (i, j));

    const double area = PLIC::polygon_area(result);
    return area - value;
}

double bisection_method(const grid& g, double value, const point& n, const int i, const int j)
{
    double a = - 1;
    double b = g.delta_x * g.x_size + 1;

    double eps = 1e-6;

    double fa = approx_area(g, a, n, i, j, value);
    double fb = approx_area(g, b, n, i, j, value);

    if (fa == 0) {
        return a;
    }
    if (fb == 0) {
        return b;
    }
    if (fa * fb > 0) {
        // no solution
        std::numeric_limits<double>::max();
    }

    while (std::abs(b - a) > eps) {
        double c = (a + b) / 2;
        double fc = approx_area(g, c, n, i, j, value);
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

line_segment build_linear_approximation(const table_function &f, int i, int j)
{
    const grid &g = f.f_grid;

    point n;
    n.x = 0.5 * (f[i + 1][j] - f[i - 1][j]) / g.delta_x;
    n.y = 0.5 * (f[i][j + 1] - f[i][j - 1]) / g.delta_y;

    double value = f.points[i][j] * g.delta_x * g.delta_y;

    const double rho = bisection_method(g, value, n, i, j);

    return line_equation (n.x, n.y, rho);
}

