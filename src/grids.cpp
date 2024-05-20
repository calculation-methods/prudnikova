#include "grids.h"

// Функция, вычисляющая координаты вершин ij-ой ячейки сетки g
Polygon gridCellCoodrs(Grid g, int i, int j) {
    FunctionPoint lu, ld, ru, rd;

    // Левый нижний угол
    ld.x = g.delta_x * i;
    ld.y = g.delta_y * j;
    // Правый нижний угол
    rd.x = g.delta_x * i + 1;
    rd.y = g.delta_y * j; 
    // Правый верхний угол
    ru.x = g.delta_x * i + 1;
    ru.y = g.delta_y * j + 1; 
    // Левый верхний угол
    lu.x = g.delta_x * i;
    lu.y = g.delta_y * j + 1;

    Polygon cell(4);
    cell.vertex[0] = lu;
    cell.vertex[1] = ld;
    cell.vertex[2] = rd;
    cell.vertex[3] = ru;

    return cell;
}

// Функция, находящая точки пересечения прямой с ij-ой ячейкой сетки
std::vector<FunctionPoint> gridCellLinearIntersection(const LineSegment& lf, const Grid& g, int i, int j) {
    std::vector<FunctionPoint> intersectionPoints;

    if (lf.n.x == 0 && (linearSolve(lf, g.delta_x * i) == g.delta_y * j || linearSolve(lf, g.delta_x * i) == g.delta_y * (j + 1))) {
        FunctionPoint left, right;

        left.x = g.delta_x * i;
        left.y = linearSolve(lf, g.delta_x * i);

        right.x = g.delta_x * (i + 1);
        right.y = linearSolve(lf, g.delta_x * (i + 1));

        intersectionPoints.push_back(left);
        intersectionPoints.push_back(right);

        return intersectionPoints;
    }

    if (lf.n.y == 0 && (linearFindX(lf, g.delta_y * j) == g.delta_x * i || linearFindX(lf, g.delta_y * j) == g.delta_x * (i + 1))) {
        FunctionPoint left, right;

        left.y = g.delta_y * j;
        left.x = linearFindX(lf, g.delta_y * j);

        right.y = g.delta_y * (j + 1);
        right.x = linearFindX(lf, g.delta_y * (j + 1));

        intersectionPoints.push_back(left);
        intersectionPoints.push_back(right);

        return intersectionPoints;
    }

    // Получаем координаты вершин ячейки
    Polygon cell = gridCellCoodrs(g, i, j);

    // Проверяем пересечение с каждой стороной ячейки
    for (int curIndex = 0; curIndex < 4; curIndex++) {
        int nextIndex = (curIndex + 1) % 4;

        // Находим уравнение прямой, проходящей через две вершины
        const double dx = cell.vertex[nextIndex].x - cell.vertex[curIndex].x;
        const double dy = cell.vertex[nextIndex].y - cell.vertex[curIndex].y;

        double x = 0.0, y = 0.0;
        if (dx == 0) {
            // Линия параллельна OY
            x = cell.vertex[curIndex].x;
            y = linearSolve(lf, x);
        } else {
            // Линия параллельна OX
            y = cell.vertex[curIndex].y;
            x = linearFindX(lf, y);
        }

        //Проверяем, принадлежит ли точка пересечения отрезку стороны ячейки
        if (x >= std::min(cell.vertex[curIndex].x, cell.vertex[nextIndex].x) &&
            x <= std::max(cell.vertex[curIndex].x, cell.vertex[nextIndex].x) &&
            y >= std::min(cell.vertex[curIndex].y, cell.vertex[nextIndex].y) &&
            y <= std::max(cell.vertex[curIndex].y, cell.vertex[nextIndex].y)) {
            intersectionPoints.push_back({x, y});
        }
    }

    return intersectionPoints;
}
