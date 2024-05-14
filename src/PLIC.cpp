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

    return n_x * (x_v - x_i) + n_y * (y_v - y_i) > 0;
}

// Функция 3: Сбор вершин многоугольника
Polygon PLIC::collectPolygonVertices(const LineSegment& lf, const Grid& g) {
    Polygon polygon;
    FunctionPoint currPoint;
    bool currState = false;
    bool prevState = false;

    // Проходим по всем ячейкам сетки
    for (int i = 0; i <= g.x_size; ++i) {
        for (int j = 0; j <=  g.y_size; ++j) {
            currPoint.x = i * g.delta_x;
            currPoint.y = j * g.delta_y;

            currState = pointLocation(currPoint, lf);

            // Если текущее состояние отличается от предыдущего, добавляем вершину многоугольника
            if (currState != prevState) {
                FunctionPoint intersection;
                if (lineLineIntersection(lf, LineSegment{{currPoint}, 0.0}, intersection)) {
                    polygon.vertex.push_back(intersection);
                }
                if (lineLineIntersection(lf, LineSegment{{currPoint}, 0.0}, intersection)) {
                    polygon.vertex.push_back(intersection);
                }
            }

            prevState = currState;
        }
    }

    polygon.vertexNum = polygon.vertex.size();

    return polygon;
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