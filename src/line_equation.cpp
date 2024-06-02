#include "line_equaiton.h"

#include "structures.h"

#include <cmath>

line_equation::line_equation(const double a_ext, const double b_ext, const double c_ext) :
  a(a_ext), b(b_ext), c(c_ext)
{
  normalize ();
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

std::optional<point> line_equation::cross (const line_equation &l)
{
}

