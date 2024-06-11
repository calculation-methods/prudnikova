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
  const matrix_extended extended_system_matrix = {{{{ this->a, this->b, this->c}},
                                                   {{ other.a, other.b, other.c}}}};
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
