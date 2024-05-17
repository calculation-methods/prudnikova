#include "area.h"

// Эта функция не требуется для случая с матрично заданной f
// Подсчёт занимаемой фазой площади 
double phaseArea(const TableFunction& func, Grid g, int i, int j) {
    double area = 0.0;

    FunctionPoint leftHalf, rightHalf;

    leftHalf.x = 0.0;
    leftHalf.y = 0.0;
    rightHalf.x = 0.0;
    rightHalf.y = 0.0;

    // Находим среднее арифметическое для значений на границах ячейки
    if (i == 0 && (i + 1) < func.points.size()) {
        leftHalf.x = i * g.delta_x;
        leftHalf.y = func.points[i][j];
        rightHalf.x = ((i + 1) * g.delta_x);
        rightHalf.y = (func.points[i][j] + func.points[i + 1][j]) / 2.0;
    } else if (i > 0 && (i + 1) < func.points.size()) {
        leftHalf.x = (i - 1) * g.delta_x;
        leftHalf.y = (func.points[i][j] + func.points[i - 1][j]) / 2.0;
        rightHalf.x = (i + 1) * g.delta_x;
        rightHalf.y = (func.points[i][j] + func.points[i + 1][j]) / 2.0;
    } else if (i > 0 && i == func.points.size() - 1) {
        leftHalf.x = (i - 1) * g.delta_x;
        leftHalf.y = (func.points[i][j] + func.points[i - 1][j]) / 2.0;
        rightHalf.x = (i + 1) * g.delta_x;
        rightHalf.y = func.points[i][j];
    } else {
        throw std::invalid_argument("Ошибка в построении нелинейной функции: недостаточно точек");
    }

    Polygon cell, p;
    cell = gridCellCoodrs(g, i, j);

    // !! здесь нужно посчитать площадь именно первой фазы, исходя из её положения. Пока что полагаю, что она находится снизу
    p.vertex.push_back(cell.vertex[1]);
    p.vertex.push_back(cell.vertex[2]);
    p.vertex.push_back(leftHalf);
    p.vertex.push_back(rightHalf);

    p.vertexNum = 4;

    area = PLIC::polygonArea(p);

    return area;
}

// Функция, вычисляющая отношение изначальной площади первой фазы к площади ячейки сетки
double calculatePhaseRatio(const TableFunction& func, Grid g, int i, int j) {
    const double cellArea = g.delta_x * g.delta_y;
    const double phase_Area = phaseArea(func, g, i, j);
    
    return phase_Area / cellArea;
}

double approxArea(const Grid& g, double rho, const FunctionPoint& n, int i, int j, double value) {
    // Создаем линейную функцию f(x) = n.x * x + rho
    LineSegment lf;
    lf.n = n;
    lf.rho = rho;

    // Находим точки пересечения прямой с ячейкой сетки
    // std::vector<FunctionPoint> intersections = gridCellLinearIntersection(lf, g, i, j);

    // Создаем многоугольник из точек пересечения
    // Polygon p(intersections.size());
    // for (int j = 0; j < intersections.size(); j++) {
    //     p.vertex[j] = intersections[j];
    //     p.vertexNum += 1;
    // }

    // Polygon cell = gridCellCoodrs(g, i, j);

    // // Руководствуюсь тем, что первая фаза снизу слева
    // for (int k = 0; k < cell.vertex.size(); k++) {
    //     bool inPoly = false;
    //     for (int inter = 0; inter < p.vertex.size(); inter++) {
    //         if (!inPoly && cell.vertex[k].y < p.vertex[inter].y || cell.vertex[k].x < p.vertex[inter].x) {
    //             result.vertex.push_back(cell.vertex[k]);
    //             result.vertexNum += 1;

    //             inPoly = true;
    //         }
    //     }
    // }

    Polygon result = PLIC::collectPolygonVertices(lf, g, i, j);

    // Вычисляем площадь многоугольника и сравниваем ее с заданным значением
    const double area = PLIC::polygonArea(result);
    return area - value;
}
