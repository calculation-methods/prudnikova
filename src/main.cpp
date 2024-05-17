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
#include "structures.h"


int main() {
    Parameters params = readParameters("input.txt");

    Grid grid(params.delta_x, params.delta_y, params.f.points.size(), params.f.points[0].size());

    ComputationParams vertical(params.v, params.delta_t, grid);
    ComputationParams horizontal(params.u, params.delta_t, grid);

    TableFunction result = applyMethod(params.f, vertical, horizontal, params.T);

    printTableFunctionToFile(result);
    return 0;
}