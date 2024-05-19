#include "PLIC.h"

// Функция 1
bool PLIC::lineLineIntersection(LineSegment f1, LineSegment f2, FunctionPoint& ans) {
    const double n1_x = f1.n.x;
    const double n1_y = f1.n.y;
    const double rho1 = f1.rho;

    const double n2_x = f2.n.x;
    const double n2_y = f2.n.y;
    const double rho2 = f2.rho;

    // Вычисляем определитель
    const double det = n1_x * n2_y - n1_y * n2_x;

    // Если определитель равен 0, линии параллельны или совпадают
    if (std::fabs(det) < 1e-10) {
        return false;
    }

    ans.x = (n2_y * rho1 - n1_y * rho2) / det;
    ans.y = (n1_x * rho2 - n2_x * rho1) / det;

    return true;
}

// Функция 2
bool PLIC::pointLocation(const FunctionPoint& point, const LineSegment& lf) {
    const double n_x = lf.n.x;
    const double n_y = lf.n.y;
    const double x_i = point.x;
    const double y_i = linearSolve(lf, x_i);
    const double x_v = point.x;
    const double y_v = point.y;

    return (n_x * (x_v - x_i) + n_y * (y_v - y_i) > 0);
}

// Функция 3: Сбор вершин многоугольника
Polygon PLIC::collectPolygonVertices(const LineSegment& lf, const Grid& g, const int i, const int j) {
    Polygon result;

    std::vector<FunctionPoint> intersection = gridCellLinearIntersection(lf, g, i, j);

    for (int k = 0; k < intersection.size(); k++) {
        result.vertex.push_back(intersection[k]);
        result.vertexNum += 1;
    }

    Polygon cell = gridCellCoodrs(g, i, j);

    // !! Так ли здесь применяется функция 2?
    for (int k = 0; k < cell.vertex.size(); k++){
        if (pointLocation(cell.vertex[k], lf)) {
            result.vertex.push_back(cell.vertex[k]);
            result.vertexNum += 1;
        }
    }
    
    return result;
}


// Функция 4: расчёт площади многоугольника
double PLIC::polygonArea(const Polygon& p) {
    double area = 0.0;

    // Вычисление площади с помощью формулы Гаусса
    for (int i = 0; i < p.vertex.size(); i++) {
        int j = (i + 1) % p.vertex.size();
        area += p.vertex[i].x * p.vertex[j].y - p.vertex[j].x * p.vertex[i].y;
    }

    area = std::abs(area) / 2.0;

    return area;
}