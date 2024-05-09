#include "flux.h"

// Функция для расчёта площади, прошедшей через правую грань ячейки
double calculateRightFlux(const Polygon& p, const TableFunction& u, double t, Grid g, int i, int j) {
    Polygon p1;
    p1.vertexNum = 0;
    for (int k = 0; k < p.vertex.size(); k++) {
        double x = p.vertex[k].x + u.points[i + 1][j] * t;
        double y = p.vertex[k].y;
        // Проверяем, прошла ли точка через правую грань ячейки
        if (x > (i + 1) * g.delta_x) {
            p1.vertex.push_back({x, y});
            p1.vertexNum += 1;
        }
    }

    p1.vertex.push_back({(i + 1) * g.delta_x, j * g.delta_y});
    p1.vertex.push_back({(i + 1) * g.delta_x, (j + 1) * g.delta_y});

    return PLIC::polygonArea(p1);
}

// Функция для расчёта площади, прошедшей через верхнюю грань ячейки
double calculateUpperFlux(const Polygon& p, const TableFunction& v, double t, Grid g, int i, int j) {
    Polygon p1;
    p1.vertexNum = 0;
    for (int k = 0; k < p.vertex.size(); k++) {
        double x = p.vertex[k].x;
        double y = p.vertex[k].y + v.points[i][j + 1] * t;
        // Проверяем, прошла ли точка через верхнюю грань ячейки
        if (y > (j + 1) * g.delta_y) {
            p1.vertex.push_back({x, y});
            p1.vertexNum += 1;
        }
    }

    p1.vertex.push_back({i * g.delta_x, (j + 1) * g.delta_y});
    p1.vertex.push_back({(i + 1) * g.delta_x, (j + 1) * g.delta_y});

    return PLIC::polygonArea(p1);
}