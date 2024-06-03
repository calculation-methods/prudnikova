#include "area.h"

double approx_area(const grid& g, double rho, const point& n, int i, int j, double value) 
{
    line_equation lf = {n, rho};

    polygon result = PLIC::collect_polygon_vertices(lf, g.get_cell (i, j));

    const double area = PLIC::polygon_area(result);
    return area - value;
}
