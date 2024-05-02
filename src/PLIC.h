#include "grids.h"

// Функция 1
bool lineLineIntersection(LinearFunction f1, LinearFunction f2, FunctionPoint& ans) {
    FunctionPoint p1 = f1.n[0];
    FunctionPoint p2 = f1.n[1];
    double n1_x = p2.x - p1.x;
    double n1_y = p2.y - p1.y;
    double rho1 = f1.rho;

    FunctionPoint p3 = f2.n[0];
    FunctionPoint p4 = f2.n[1];
    double n2_x = p4.x - p3.x;
    double n2_y = p4.y - p3.y;
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
bool pointLocation(const FunctionPoint& point, const LinearFunction& lf) {
    double n_x = lf.n[1].x - lf.n[0].x;
    double n_y = lf.n[1].y - lf.n[0].y;
    double x_i = point.x;
    double y_i = linearSolve(lf, x_i);
    double x_v = point.x;
    double y_v = point.y;
    // !! не совсем уверена, что правильно поняла обозначения

    return n_x * (x_v - x_i) + n_y * (y_v - y_i) > 0;
}


// Функция 3: Сбор вершин многоугольника
Polygon collectPolygonVertices(const LinearFunction& lf, const Grid& g) {
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
                if (lineLineIntersection(lf, LinearFunction{{currPoint, {currPoint.x + g.delta_x, currPoint.y}}, 0.0}, intersection)) {
                    polygon.vertex.push_back(intersection);
                }
                if (lineLineIntersection(lf, LinearFunction{{currPoint, {currPoint.x, currPoint.y + g.delta_y}}, 0.0}, intersection)) {
                    polygon.vertex.push_back(intersection);
                }
            }

            prevState = currState;
        }
    }

    polygon.vertexNum = polygon.vertex.size();

    return polygon;
}

// Функция 4: Вычисление площади многоугольника
double polygonArea(const Polygon& polygon) {
    double area = 0.0;
    int n = polygon.vertexNum;

    for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n;
        area += polygon.vertex[i].x * polygon.vertex[j].y;
        area -= polygon.vertex[j].x * polygon.vertex[i].y;
    }

    return std::abs(area) / 2.0;
}