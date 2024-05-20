#include "assemble.h"

// Расчёт новой функции f_(n+1)
TableFunction fFullStep(const ComputationParams& vertical, const ComputationParams& horizontal, const TableFunction& f) {
    if (f.points.size() == 0) {
        return {};
    }

    const int length = f.points.size();
    const int width = f.points[0].size();

    TableFunction new_f(length, width);

    for (int i = 0; i < length; i++) {
        for (int j = 0; j < width; j++) {
            LineSegment approx =  buildLinearApproximation(f, vertical.grid, i, j);

            Polygon p = PLIC::collectPolygonVertices(approx, vertical.grid, i, j);
            
            new_f.points[i][j] = fCellStepUpDown(p, vertical, f, i, j) + fCellStepLeftRight(p, horizontal, f, i, j);
        }
    }

    return new_f;
}

// Вычисляет конечный вид функции f
TableFunction applyMethod(const TableFunction& f, const ComputationParams& vertical, const ComputationParams& horizontal, double time) {
    const int periods = time / vertical.delta_t;

    TableFunction fk;

    for (int k = 0; k < periods; k++) {
        fk = fFullStep(vertical, horizontal, f);
    }

    return fk;
}