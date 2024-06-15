#include "structures.h"


// Точки
point operator-(const point &left, const point &right)
{
  point result;
  result.x = left.x - right.x;
  result.y = left.y - right.y;

  return result;
}

point& point::operator=(const point& other) 
{
    if (this != &other) {
        x = other.x;
        y = other.y;
    }
    return *this;
}

bool point::operator!=(const point& other) const {
    return x != other.x || y != other.y;
}

bool point::operator!() const {
    return x == 0.0 && y == 0.0;
}

bool point::operator==(const point& other) const {
    return x == other.x && y == other.y;
}


// Табличные функции
table_function& table_function::operator=(const table_function& other) 
{
    if (this != &other) {
        points = other.points;
        f_grid = other.f_grid;
    }
    return *this;
}

table_function::table_function() : points(0) {}

table_function::table_function(int n, int m) : points(n, std::vector<double>(m, 0.0)), f_grid(n, m) {}

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

// Многоугольники
polygon::polygon() : vertex_num(0) {}

polygon::polygon(std::initializer_list<point> points) : vertex(points) {}

polygon::polygon(int n) : vertex_num(n), vertex(n) {}

polygon::polygon(const polygon& other) : vertex_num(other.vertex_num), vertex(other.vertex) {}

polygon::polygon(const std::vector<point>& points) {
    vertex_num = points.size();
    vertex = points;
}

size_t polygon::size() const
{
  return vertex.size ();
}

polygon& polygon::operator=(const polygon& other) 
{
    if (this != &other) {
        vertex_num = other.vertex_num;
        vertex = other.vertex;
    }
    return *this;
}

const point &polygon::operator[](const int index) const
{
  return vertex[index];
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

double polygon::area () const
{
    auto det = [this] (const int i, const int j) { return vertex[i].x * vertex[j].y - vertex[j].x * vertex[i].y; };

    double area = 0.;
    const int size = vertex.size ();
    for (int i = 0; i < size - 1; i++)
      area += det(i, i + 1);
    area += det(size - 1, 0);

    return 0.5 * std::abs(area);
}

// Параметры
computation_params::computation_params() : velocity(), delta_t(0.0), grid_f() {}

computation_params::computation_params(table_function vel, double dt, rectangular_grid g)
        : velocity(vel), delta_t(dt), grid_f(g) {}

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
