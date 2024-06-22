#include "line_equation.h"

#include "structures.h"
#include "slau.h"

#include <cmath>

line_equation::line_equation(const double a_ext, const double b_ext, const double c_ext) :
  a(a_ext), b(b_ext), c(c_ext)
{
  normalize();
}

line_equation::line_equation(const point &start, const point &end)
{
  const point line_vector = {end.x - start.x, end.y - start.y};

  a = line_vector.y;
  b = -line_vector.x;
  c = start.y * line_vector.x - start.x * line_vector.y;

  normalize();
}

void line_equation::normalize ()
{
  const double normalization_mult = std::sqrt (a * a + b * b);

  a /= normalization_mult;
  b /= normalization_mult;
  c /= normalization_mult;
}

double line_equation::substitute (const double x, const double y) const
{
  return a * x + b * y + c;
}

double line_equation::substitute (const point &p) const
{
  return substitute (p.x, p.y);
}

std::optional<point> line_equation::cross (const line_equation &other) const
{
  const matrix_extended extended_system_matrix = {{{{ this->a, this->b, -this->c}},
                                                   {{ other.a, other.b, -other.c}}}};
  const slau system_of_equations(extended_system_matrix);
  const column solution = system_of_equations.solve();

  std::optional<point> result = point (solution[0], solution[1]);

  return result;
}

double line_equation::compute_y(const double x) const
{
    return (-c - a * x) / b;
}

double line_equation::compute_x(const double y) const
{
    return (-c - b * y) / a;
}

double line_equation::compute_distance (const point &p) const
{
  return a * p.x + b * p.y;
}

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
