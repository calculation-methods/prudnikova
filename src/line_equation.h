#ifndef LINE_EQUATION_H
#define LINE_EQUATION_H

struct point;

class line_equation
{
  double a;
  double b;
  double c;

  void normalize ();

public:
  line_equation(const double a_ext, const double b_ext, const double c_ext);
  ~line_equation() = default;

  double substitute (const double x, const double y)
  double substitute (const point &p);
  std::optional<point> cross (const line_equation &l);
}

#endif
