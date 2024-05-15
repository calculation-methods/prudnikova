#include "grids.h"

// Функция, вычисляющая координаты вершин i-ой ячейки сетки g
Polygon gridCellCoodrs (Grid g, int i, int j) {
    FunctionPoint lu, ld, ru, rd;

    // Левый верхний угол
    lu.x = g.delta_x * i;
    lu.y = g.delta_y * j + 1;
    // Левый нижний угол
    ld.x = g.delta_x * i;
    ld.y = g.delta_y * j;
    // Правый нижний угол
    rd.x = g.delta_x * i + 1;
    rd.y = g.delta_y * j; 
    // Правый верхний угол
    ru.x = g.delta_x * i + 1;
    ru.y = g.delta_y * j + 1; 

    Polygon cell(4);
    cell.vertex[0] = lu;
    cell.vertex[1] = ld;
    cell.vertex[2] = rd;
    cell.vertex[3] = ru;

    return cell;
}

// Функция, находящая точки пересечения прямой с i-ой ячейкой сетки
std::vector<FunctionPoint> gridCellLinearIntersection(const LineSegment& lf, const Grid& g, int i, int j) {
    std::vector<FunctionPoint> intersectionPoints;

    // Получаем координаты вершин ячейки
    Polygon cell = gridCellCoodrs(g, i, j);

    // Проверяем пересечение с каждой стороной ячейки
    for (int j = 0; j < 4; j++) {
        int nextIndex = (j + 1) % 4;

        // Находим уравнение прямой, проходящей через две вершины
        const double dx = cell.vertex[nextIndex].x - cell.vertex[j].x;
        const double dy = cell.vertex[nextIndex].y - cell.vertex[j].y;

        double x = 0.0, y = 0.0;
        if (dx == 0) {
            // Линия параллельна OY
            x = cell.vertex[j].x;
            y = linearSolve(lf, x);
        } else {
            // Линия параллельна OX
            y = cell.vertex[j].y;
            x = linearFindX(lf, y);
        }

        //Проверяем, принадлежит ли точка пересечения отрезку стороны ячейки
        if (x >= std::min(cell.vertex[j].x, cell.vertex[nextIndex].x) &&
            x <= std::max(cell.vertex[j].x, cell.vertex[nextIndex].x) &&
            y >= std::min(cell.vertex[j].y, cell.vertex[nextIndex].y) &&
            y <= std::max(cell.vertex[j].y, cell.vertex[nextIndex].y)) {
            intersectionPoints.push_back({x, y});
        }
    }

    return intersectionPoints;
}