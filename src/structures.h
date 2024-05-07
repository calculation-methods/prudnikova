#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <vector>
#include <cmath>


struct FunctionPoint {
    double x;
    double y;

    FunctionPoint& operator=(const FunctionPoint& other) {
        if (this != &other) {
            x = other.x;
            y = other.y;
        }
        return *this;
    }
};

struct TableFunction {
    std::vector<FunctionPoint> points;

    TableFunction& operator=(const TableFunction& other) {
        if (this != &other) {
            points = other.points;
        }
        return *this;
    }
};

struct LineSegment {
    FunctionPoint n;
    double rho;

    LineSegment& operator=(const LineSegment& other) {
        if (this != &other) {
            n = other.n;
            rho = other.rho;
        }
        return *this;
    }
};

struct Grid {
    double delta_x;
    double delta_y;

    size_t x_size;
    size_t y_size;

    Grid(double dx, double dy, size_t sizex, size_t sizey) : delta_x(dx), delta_y(dy), x_size(sizex), y_size(sizey) {}

    Grid& operator=(const Grid& other) {
        if (this != &other) {
            delta_x = other.delta_x;
            delta_y = other.delta_y;
        }
        return *this;
    }
};


struct Polygon {
    int vertexNum;
    std::vector<FunctionPoint> vertex;

    // Конструктор по умолчанию (без параметров)
    Polygon() : vertexNum(0) {}

    // Конструктор с параметром для инициализации размера вектора
    Polygon(int n) : vertexNum(n), vertex(n) {}

    // Конструктор копирования
    Polygon(const Polygon& other) : vertexNum(other.vertexNum), vertex(other.vertex) {}

    // Оператор присваивания
    Polygon& operator=(const Polygon& other) {
        if (this != &other) {
            vertexNum = other.vertexNum;
            vertex = other.vertex;
        }
        return *this;
    }
};

#endif