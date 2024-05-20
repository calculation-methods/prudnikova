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

// Конструктор по умолчанию (без параметров)
TableFunction::TableFunction() : points(0) {}

// Конструктор с параметром для инициализации размера вектора
TableFunction::TableFunction(int n, int m) : points(n, std::vector<double>(m, 0.0)) {}

LineSegment& LineSegment::operator=(const LineSegment& other) {
    if (this != &other) {
        n = other.n;
        rho = other.rho;
    }
    return *this;
}

// Конструктор по умолчанию
Grid::Grid() {}

// Конструктор с параметрами
Grid::Grid(double dx, double dy, size_t sizex, size_t sizey) : delta_x(dx), delta_y(dy), x_size(sizex), y_size(sizey) {}

Grid::Grid(size_t sizex, size_t sizey) : x_size(sizex), y_size(sizey) {}

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

// Дефолтный конструктор
ComputationParams::ComputationParams() : velocity(), delta_t(0.0), grid() {}

// Конструктор с параметрами
ComputationParams::ComputationParams(TableFunction vel, double dt, Grid g)
        : velocity(vel), delta_t(dt), grid(g) {}

bool operator==(const FunctionPoint& lhs, const FunctionPoint& rhs)
{
    return std::fabs(lhs.x - rhs.x) < 1e-10 && std::fabs(lhs.y - rhs.y) < 1e-10;
}

bool operator==(const TableFunction& lhs, const TableFunction& rhs)
{
    if (lhs.points.size() != rhs.points.size()) return false;
    for (size_t i = 0; i < lhs.points.size(); ++i)
    {
        if (lhs.points[i].size() != rhs.points[i].size()) return false;
        for (size_t j = 0; j < lhs.points[i].size(); ++j)
        {
            if (std::fabs(lhs.points[i][j] - rhs.points[i][j]) >= 1e-10) return false;
        }
    }
    return true;
}

bool operator==(const LineSegment& lhs, const LineSegment& rhs)
{
    return lhs.n == rhs.n && std::fabs(lhs.rho - rhs.rho) < 1e-10;
}

bool operator==(const Grid& lhs, const Grid& rhs)
{
    return std::fabs(lhs.delta_x - rhs.delta_x) < 1e-10
        && std::fabs(lhs.delta_y - rhs.delta_y) < 1e-10
        && lhs.x_size == rhs.x_size
        && lhs.y_size == rhs.y_size;
}

bool operator==(const Polygon& lhs, const Polygon& rhs)
{
    if (lhs.vertexNum != rhs.vertexNum) return false;
    if (lhs.vertex.size() != rhs.vertex.size()) return false;
    for (size_t i = 0; i < lhs.vertex.size(); ++i)
    {
        if (lhs.vertex[i].x != rhs.vertex[i].x || lhs.vertex[i].y != rhs.vertex[i].y) return false;
    }
    return true;
}

bool operator==(const ComputationParams& lhs, const ComputationParams& rhs)
{
    return lhs.velocity == rhs.velocity
        && std::fabs(lhs.delta_t - rhs.delta_t) < 1e-10
        && lhs.grid == rhs.grid;
}

std::ostream& operator<<(std::ostream& os, const FunctionPoint& fp)
{
    os << "(" << fp.x << ", " << fp.y << ")";
    return os;
}

std::ostream& operator<<(std::ostream& os, const Polygon& poly)
{
    os << "Polygon(vertexNum=" << poly.vertexNum << ", vertex=[";
    for (const auto& v : poly.vertex)
    {
        os << v << ", ";
    }
    os << "])";
    return os;
}