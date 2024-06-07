#ifndef LINE_EQUATION_H
#define LINE_EQUATION_H

#include <optional>

struct point;

class line_equation
{
  double a;
  double b;
  double c;

  void normalize ();

public:
  line_equation(const double a_ext, const double b_ext, const double c_ext);
  line_equation(const point &start, const point &end);
  ~line_equation() = default;

  double substitute (const double x, const double y) const;
  double substitute (const point &p) const;
  std::optional<point> cross (const line_equation &l) const;
  double compute_y(const double x) const;
  double compute_x(const double y) const;
}

#endif
