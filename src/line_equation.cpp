#include "line_equaiton.h"

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
  c = start.y * line_vector.x - start.x * line_vector.y

  normalize();
}

void line_equation:normalize ()
{
  const double normalization_mult = std::sqrt (a * a + b * b);

  a /= normalization_mult;
  b /= normalization_mult;
  c /= normalization_mult;
}

double line_equation::substitute (const double x, const double y)
{
  return a * x + b * y + c;
}

double line_equation::substitute (const point &p)
{
  return substitute (p.x, p.y);
}

std::optional<point> line_equation::cross (const line_equation &other)
{
  const matrix_2x2 A = {{  this.a,  this.b},
                        { other.a, other.b}};
  const matrix_2x1 b = { -this.c, -other.c};

  if (const matrix_2x1 result = slau::kramer_method (A, b))
    return {result[0], result[1]};

  return std::nullopt;
}

