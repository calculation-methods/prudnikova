#include <cmath>
#include <iostream>
#include <vector>


#include "approximation.h"
#include "area.h"
#include "flux.h"
#include "grids.h"
#include "linear.h"
#include "operations.h"
#include "PLIC.h"
#include "readfile.h"
#include "structures.h"


int main() {
    std::vector<TableFunction> matrices = readMatrices("matrix.txt");

    for (const auto& function : matrices) {
        std::cout << "Matrix" << "\n";
        for (const auto& row : function.points) {
            for (const auto& value : row) {
                std::cout << value << " ";
            }
            std::cout << "\n";
        }
        std::cout << "\n";
    }

    return 0;
}