#include "approximation.h"
#include "time.h"
#include "flux.h"
#include "operations.h"
#include "PLIC.h"
#include "printfile.h"
#include "readfile.h"
#include "structures.h"

int main()
{
    parameters params = read_parameters("/home/nastyapond/dplm/prudnikova/src/input.txt");

    grid f_grid(params.delta_x, params.delta_y, params.f.points.size(), params.f.points[0].size());

    solver vof_method (params.u, params.v, f_grid, params.delta_t);

    table_function result = vof_method.time_integration(params.f, params.T);

    printTableFunctionToFile(result);

    return 0;
}
