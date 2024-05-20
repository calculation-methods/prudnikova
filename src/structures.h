#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <vector>
#include <cmath>
#include <iostream>

struct FunctionPoint {
    double x;
    double y;

    FunctionPoint& operator=(const FunctionPoint& other);
};

struct TableFunction {
    std::vector<std::vector<double>> points;

    // Конструктор по умолчанию (без параметров)
    TableFunction();

    // Конструктор с параметром для инициализации размера вектора
    TableFunction(int n, int m);

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

    Grid();

    Grid(double dx, double dy, size_t sizex, size_t sizey);

    Grid(size_t sizex, size_t sizey);

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

struct ComputationParams {
    TableFunction velocity;
    double delta_t; 
    Grid grid;

    // Дефолтный конструктор
    ComputationParams();

    // Конструктор с параметрами
    ComputationParams(TableFunction vel, double dt, Grid g);
};

bool operator==(const FunctionPoint& lhs, const FunctionPoint& rhs);

bool operator==(const TableFunction& lhs, const TableFunction& rhs);

bool operator==(const LineSegment& lhs, const LineSegment& rhs);

bool operator==(const Grid& lhs, const Grid& rhs);

bool operator==(const Polygon& lhs, const Polygon& rhs);

bool operator==(const ComputationParams& lhs, const ComputationParams& rhs);

std::ostream& operator<<(std::ostream& os, const FunctionPoint& fp);

std::ostream& operator<<(std::ostream& os, const Polygon& poly);

#endif