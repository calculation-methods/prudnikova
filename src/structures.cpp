#include "structures.h"


point& point::operator=(const point& other) 
{
    if (this != &other) {
        x = other.x;
        y = other.y;
    }
    return *this;
}

table_function& table_function::operator=(const table_function& other) 
{
    if (this != &other) {
        points = other.points;
    }
    return *this;
}

// Конструктор по умолчанию (без параметров)
table_function::table_function() : points(0) {}

// Конструктор с параметром для инициализации размера вектора
table_function::table_function(int n, int m) : points(n, std::vector<double>(m, 0.0)) {}

line_segment& line_segment::operator=(const line_segment& other) 
{
    if (this != &other) {
        n = other.n;
        rho = other.rho;
    }
    return *this;
}

// Конструктор по умолчанию
grid::grid() {}

// Конструктор с параметрами
grid::grid(double dx, double dy, size_t sizex, size_t sizey) : delta_x(dx), delta_y(dy), x_size(sizex), y_size(sizey) {}

grid::grid(size_t sizex, size_t sizey) : x_size(sizex), y_size(sizey) {}

grid& grid::operator=(const grid& other) {
    if (this != &other) {
        delta_x = other.delta_x;
        delta_y = other.delta_y;
    }
    return *this;
}



// Конструктор по умолчанию (без параметров)
polygon::polygon() : vertex_num(0) {}

// Конструктор с параметром для инициализации размера вектора
polygon::polygon(int n) : vertex_num(n), vertex(n) {}

// Конструктор копирования
polygon::polygon(const polygon& other) : vertex_num(other.vertex_num), vertex(other.vertex) {}

// Конструктор, принимающий вектор точек FunctionPoint
polygon::polygon(const std::vector<point>& points) {
    vertex_num = points.size();
    vertex = points;
}

// Оператор присваивания
polygon& polygon::operator=(const polygon& other) 
{
    if (this != &other) {
        vertex_num = other.vertex_num;
        vertex = other.vertex;
    }
    return *this;
}

// Дефолтный конструктор
computation_params::computation_params() : velocity(), delta_t(0.0), grid_f() {}

// Конструктор с параметрами
computation_params::computation_params(table_function vel, double dt, grid g)
        : velocity(vel), delta_t(dt), grid_f(g) {}

bool operator==(const point& lhs, const point& rhs)
{
    return std::fabs(lhs.x - rhs.x) < 1e-10 && std::fabs(lhs.y - rhs.y) < 1e-10;
}

bool operator==(const table_function& lhs, const table_function& rhs)
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

bool operator==(const line_segment& lhs, const line_segment& rhs)
{
    return lhs.n == rhs.n && std::fabs(lhs.rho - rhs.rho) < 1e-10;
}

bool operator==(const grid& lhs, const grid& rhs)
{
    return std::fabs(lhs.delta_x - rhs.delta_x) < 1e-10
        && std::fabs(lhs.delta_y - rhs.delta_y) < 1e-10
        && lhs.x_size == rhs.x_size
        && lhs.y_size == rhs.y_size;
}

bool operator==(const polygon& lhs, const polygon& rhs)
{
    if (lhs.vertex_num != rhs.vertex_num) return false;
    if (lhs.vertex.size() != rhs.vertex.size()) return false;
    for (size_t i = 0; i < lhs.vertex.size(); ++i)
    {
        if (lhs.vertex[i].x != rhs.vertex[i].x || lhs.vertex[i].y != rhs.vertex[i].y) return false;
    }
    return true;
}

bool operator==(const computation_params& lhs, const computation_params& rhs)
{
    return lhs.velocity == rhs.velocity
        && std::fabs(lhs.delta_t - rhs.delta_t) < 1e-10
        && lhs.grid_f == rhs.grid_f;
}

std::ostream& operator<<(std::ostream& os, const point& fp)
{
    os << "(" << fp.x << ", " << fp.y << ")";
    return os;
}

std::ostream& operator<<(std::ostream& os, const polygon& poly)
{
    os << "Polygon(vertexNum=" << poly.vertex_num << ", vertex=[";
    for (const auto& v : poly.vertex)
    {
        os << v << ", ";
    }
    os << "])";
    return os;
}