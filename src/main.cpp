#include <cmath>
#include <iostream>
#include <vector>


#include "approximation.h"
#include "area.h"
#include "assemble.h"
#include "flux.h"
#include "grids.h"
#include "linear.h"
#include "operations.h"
#include "PLIC.h"
#include "printfile.h"
#include "readfile.h"
#include "rungekutta.h"
#include "structures.h"


int main() 
{
    Parameters params = readParameters("/home/nastyapond/dplm/prudnikova/src/input.txt");

    grid grid(params.delta_x, params.delta_y, params.f.points.size(), params.f.points[0].size());

    computation_params vertical(params.v, params.delta_t, grid);
    computation_params horizontal(params.u, params.delta_t, grid);

    table_function result = apply_method(params.f, vertical, horizontal, params.T);

    printTableFunctionToFile(result);
    return 0;
}