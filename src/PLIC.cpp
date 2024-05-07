#include "PLIC.h"

// Функция 1
bool lineLineIntersection(LineSegment f1, LineSegment f2, FunctionPoint& ans) {
    double n1_x = f1.n.x;
    double n1_y = f1.n.y;
    double rho1 = f1.rho;

    double n2_x = f2.n.x;
    double n2_y = f2.n.y;
    double rho2 = f2.rho;

    // Вычисляем определитель
    double det = n1_x * n2_y - n1_y * n2_x;

    // Если определитель равен 0, линии параллельны или совпадают
    if (std::fabs(det) < 1e-10) {
        return false;
    }

    ans.x = (n2_y * rho1 - n1_y * rho2) / det;
    ans.y = (n1_x * rho2 - n2_x * rho1) / det;

    return true;
}

// Функция 2
bool pointLocation(const FunctionPoint& point, const LineSegment& lf) {
    double n_x = lf.n.x;
    double n_y = lf.n.y;
    double x_i = point.x;
    double y_i = linearSolve(lf, x_i);
    double x_v = point.x;
    double y_v = point.y;

    return n_x * (x_v - x_i) + n_y * (y_v - y_i) > 0;
}

// Функция 3: Сбор вершин многоугольника
Polygon collectPolygonVertices(const LineSegment& lf, const Grid& g) {
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