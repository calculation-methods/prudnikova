#include "area.h"

double polygonArea(const Polygon& p) {
    double area = 0.0;

    int n = p.vertexNum;

    // Обработка случая, когда количество вершин меньше 3 (не многоугольник)
    if (n < 3) {
        return 0.0;
    }

    // Вычисление площади с помощью формулы Гаусса
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        area += p.vertex[i].x * p.vertex[j].y - p.vertex[j].x * p.vertex[i].y;
    }

    area = std::abs(area) / 2.0;

    return area;
}


// Подсчёт занимаемой фазой площади 
double phaseArea(const TableFunction& func, Grid g, int i) {
    double area = 0.0;

    FunctionPoint leftHalf, rightHalf;

    leftHalf.x = 0.0;
    leftHalf.y = 0.0;
    rightHalf.x = 0.0;
    rightHalf.y = 0.0;

    if (i == 0 && (i + 1) < func.points.size()) {
        leftHalf.x = func.points[i].x;
        leftHalf.y = func.points[i].y;
        rightHalf.x = (func.points[i].x + func.points[i + 1].x) / 2.0;
        rightHalf. y= (func.points[i].y + func.points[i + 1].y) / 2.0;
    } else if (i > 0 && (i + 1) < func.points.size()) {
        leftHalf.x = (func.points[i].x + func.points[i - 1].x) / 2.0;
        leftHalf.y = (func.points[i].y + func.points[i - 1].y) / 2.0;
        rightHalf.x = (func.points[i].x + func.points[i + 1].x) / 2.0;
        rightHalf. y= (func.points[i].y + func.points[i + 1].y) / 2.0;
    } else if (i > 0 && i == func.points.size() - 1) {
        leftHalf.x = (func.points[i].x + func.points[i - 1].x) / 2.0;
        leftHalf.y = (func.points[i].y + func.points[i - 1].y) / 2.0;
        rightHalf.x = func.points[i].x;
        rightHalf. y= func.points[i].y;
    } else {
        throw std::invalid_argument("Ошибка в построении нелинейной функции: недостаточно точек");
    }

    Polygon cell, p;
    cell = gridCellCoodrs(g, i);

    // !! здесь нужно посчитать площадь именно первой фазы, исходя из её положения. Пока что полагаю, что она находится снизу
    p.vertex.push_back(cell.vertex[1]);
    p.vertex.push_back(cell.vertex[2]);
    p.vertex.push_back(leftHalf);
    p.vertex.push_back(rightHalf);

    p.vertexNum = 4;

    area = polygonArea(p);

    return area;
}

// Функция, вычисляющая отношение изначальной площади первой фазы к площади ячейки сетки
double calculatePhaseRatio(const TableFunction& func, Grid g, int i) {
    double cellArea = g.delta_x * g.delta_y;
    double phase_Area = phaseArea(func, g, i);
    
    return phase_Area / cellArea;
}

double approxArea(const Grid& g, double rho, const FunctionPoint& n, int i, double value) {
    // Создаем линейную функцию f(x) = n.x * x + rho
    LineSegment lf;
    lf.n = n;
    lf.rho = rho;

    // Находим точки пересечения прямой с ячейкой сетки
    std::vector<FunctionPoint> intersections = gridCellLinearIntersection(lf, g, i);

    // Создаем многоугольник из точек пересечения
    Polygon p(intersections.size());
    for (int j = 0; j < intersections.size(); j++) {
        p.vertex[j] = intersections[j];
    }

    // Вычисляем площадь многоугольника и сравниваем ее с заданным значением
    double area = polygonArea(p);
    return area - value;
}
