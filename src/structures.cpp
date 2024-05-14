#include "structures.h"

FunctionPoint& FunctionPoint::operator=(const FunctionPoint& other) {
    if (this != &other) {
        x = other.x;
        y = other.y;
    }
    return *this;
}

TableFunction& TableFunction::operator=(const TableFunction& other) {
    if (this != &other) {
        points = other.points;
    }
    return *this;
}

LineSegment& LineSegment::operator=(const LineSegment& other) {
    if (this != &other) {
        n = other.n;
        rho = other.rho;
    }
    return *this;
}

Grid::Grid(double dx, double dy, size_t sizex, size_t sizey) : delta_x(dx), delta_y(dy), x_size(sizex), y_size(sizey) {}

Grid& Grid::operator=(const Grid& other) {
    if (this != &other) {
        delta_x = other.delta_x;
        delta_y = other.delta_y;
    }
    return *this;
}

// Конструктор по умолчанию (без параметров)
Polygon::Polygon() : vertexNum(0) {}

// Конструктор с параметром для инициализации размера вектора
Polygon::Polygon(int n) : vertexNum(n), vertex(n) {}

// Конструктор копирования
Polygon::Polygon(const Polygon& other) : vertexNum(other.vertexNum), vertex(other.vertex) {}

// Конструктор, принимающий вектор точек FunctionPoint
Polygon::Polygon(const std::vector<FunctionPoint>& points) {
    vertexNum = points.size();
    vertex = points;
}

// Оператор присваивания
Polygon& Polygon::operator=(const Polygon& other) {
    if (this != &other) {
        vertexNum = other.vertexNum;
        vertex = other.vertex;
    }
    return *this;
}
