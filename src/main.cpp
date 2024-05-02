#include <iostream>
#include <vector>
#include <cmath>

#include "PLIC.h"


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
double phaseArea(const NonlinearFunction& func, Grid g, int i) {
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
double calculatePhaseRatio(const NonlinearFunction& func, Grid g, int i) {
    double cellArea = g.delta_x * g.delta_y;
    double phase_Area = phaseArea(func, g, i);
    
    return phase_Area / cellArea;
}


// Считаем площадь, отсекаемую прямой
// double computeAreaInCell(const LinearFunction& lf, const Grid& g, int i) {
//     Polygon cell;
//     cell.operator=(gridCellCoodrs(g, i));
//     //cell = gridCellCoodrs(g, i);

//     double area = 0.0;
//     // !! проверить случай, где линия проходит по границе ячейки

//     return area;
// }


double approxArea(const Grid& g, double rho, const FunctionPoint& n, int i, double value) {
    // Создаем линейную функцию f(x) = n.x * x + rho
    LinearFunction lf;
    lf.n.push_back(n);
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

double bisectionMethod(const Grid& g, double value, const FunctionPoint& n, int i) {
    double a = -g.delta_x * std::max(std::abs(n.x), std::abs(n.y));
    double b = g.delta_x * std::max(std::abs(n.x), std::abs(n.y));
    double eps = 1e-6;
    double fa = approxArea(g, a, n, i, value);
    double fb = approxArea(g, b, n, i, value);

    if (fa == 0) {
        return a;
    }
    if (fb == 0) {
        return b;
    }
    if (fa * fb > 0) {
        // Решение не существует на данном интервале
        return NAN;
    }

    while (std::abs(b - a) > eps) {
        double c = (a + b) / 2;
        double fc = approxArea(g, c, n, i, value);
        if (fc == 0) {
            return c;
        }
        if (fa * fc < 0) {
            b = c;
        } else {
            a = c;
            fa = fc;
        }
    }

    return (a + b) / 2;
}


// Построение линейной аппроксимации
LinearFunction buildLinearApproximation(const NonlinearFunction& f, Grid g, int i) {
    FunctionPoint n;
    n.x = 0;
    n.y = 0;

    if (i == 0 && i < f.points.size()) {
        for (size_t j = i; j < i + 2; j++) {
            n.x += df_dx(f, g, i);
            n.y += df_dy(f, g, i);
        }
    } else if (i == f.points.size()) {
        for (size_t j = i - 1; j < i; j++) {
            n.x += df_dx(f, g, i);
            n.y += df_dy(f, g, i);
        }
    } else {
        for (size_t j = i - 1; j < i + 2; j++) {
            n.x += df_dx(f, g, i);
            n.y += df_dy(f, g, i);
        }
    }

    n.x /= std::sqrt(n.x * n.x + n.y * n.y);
    n.y /= std::sqrt(n.x * n.x + n.y * n.y);

    double value = calculatePhaseRatio(f, g, i);

    LinearFunction lf;

    double rho = bisectionMethod(g, value, n, i);

    lf.rho = rho;
    // !! надо подвинуть на ро 
    lf.n[0].x = g.delta_x * i;
    lf.n[0].y = g.delta_y * i;
    lf.n[1].x = lf.n[0].x + n.x;
    lf.n[1].y = lf.n[0].y + n.y;

    return lf;
}


// NonlinearFunction step (NonlinearFunction fn, NonlinearFunction u) {
//     NonlinearFunction fn1 = fn;
//     for (int i = 0; i < fn1.points.size(); ++i) {

//     }
// }


int main() {
    NonlinearFunction f, u, v;
    // std::vector<double> cellVerticesX = {0.0, 1.0, 1.0, 0.0};
    // std::vector<double> cellVerticesY = {0.0, 0.0, 1.0, 1.0};
    // std::vector<bool> vertexStates = {true, true, false, true};
    
    // Polygon polygon = polygonCollection(cellVerticesX, cellVerticesY, vertexStates);
    
    // for (int i = 0; i < polygon.verticesX.size(); i++) {
    //     std::cout << "vertex " << i << ": (" << polygon.verticesX[i] << ", " << polygon.verticesY[i] << ")" << "\n";
    // }
    // double area = polygonArea(polygon.verticesX, polygon.verticesY);
    // std::cout << "area: " << area << "\n";
    
    return 0;
}