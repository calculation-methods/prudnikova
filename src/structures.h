#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <vector>
#include <cmath>

struct FunctionPoint {
    double x;
    double y;

    FunctionPoint& operator=(const FunctionPoint& other);
};

struct TableFunction {
    std::vector<std::vector<double>> points;

    TableFunction& operator=(const TableFunction& other);
};

struct LineSegment {
    FunctionPoint n;
    double rho;

    LineSegment& operator=(const LineSegment& other);
};

struct Grid {
    double delta_x;
    double delta_y;

    size_t x_size;
    size_t y_size;

    Grid(double dx, double dy, size_t sizex, size_t sizey);

    Grid& operator=(const Grid& other);
};

struct Polygon {
    int vertexNum;
    std::vector<FunctionPoint> vertex;

    // Конструктор по умолчанию (без параметров)
    Polygon();

    // Конструктор с параметром для инициализации размера вектора
    Polygon(int n);

    // Конструктор копирования
    Polygon(const Polygon& other);

    // Конструктор, принимающий вектор точек FunctionPoint
    Polygon(const std::vector<FunctionPoint>& points);

    // Оператор присваивания
    Polygon& operator=(const Polygon& other);
};

struct Conditions {
    TableFunction velocity;
    double delta_t; 
    Grid grid;
};

#endif
