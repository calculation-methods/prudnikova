#include "assemble.h"

// Расчёт новой функции f_(n+1)
table_function f_full_step(const computation_params& vertical, const computation_params& horizontal, const table_function& f) 
{
    if (f.points.size() == 0) 
    {
        return {};
    }

    const int length = f.points.size();
    const int width = f.points[0].size();

    table_function new_f(length, width);

    for (int i = 0; i < length; i++) 
    {
        for (int j = 0; j < width; j++) 
        {
            line_segment approx = build_linear_approximation(f, vertical.grid_f, i, j);

            polygon p = PLIC::collect_polygon_vertices(approx, vertical.grid_f, i, j);
            
            new_f.points[i][j] = fCellStepUpDown(p, vertical, f, i, j) + fCellStepLeftRight(p, horizontal, f, i, j);
        }
    }

    return new_f;
}

// Вычисляет конечный вид функции f
table_function apply_method(const table_function& f, const computation_params& vertical, const computation_params& horizontal, double time) 
{
    const int periods = time / vertical.delta_t;

    table_function fk, fn;

    fn = f;

    for (int k = 0; k < periods; k++) 
    {
        fk = f_full_step(vertical, horizontal, fn);
        fn = runge_kutta(fk, horizontal.velocity, vertical.velocity, horizontal.delta_t, horizontal.grid_f);
    }

    return fn;
}

