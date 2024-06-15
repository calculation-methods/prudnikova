#ifndef LINE_EQUATION_H
#define LINE_EQUATION_H

#include <optional>
#include <vector>

struct point {
    double x;
    double y;

    point() = default;
    point(const double x_ext, const double y_ext) : x(x_ext), y(y_ext) {}

    point& operator=(const point& other);
    bool operator!=(const point& other) const;
    bool operator!() const;
    bool operator==(const point& other) const;
};

class line_equation
{
public:
  double a;
  double b;
  double c;

  void normalize ();

public:
  line_equation() = default;
  line_equation(const double a_ext, const double b_ext, const double c_ext);
  line_equation(const point &start, const point &end);
  ~line_equation() = default;

  double substitute (const double x, const double y) const;
  double substitute (const point &p) const;
  std::optional<point> cross (const line_equation &l) const;
  double compute_y(const double x) const;
  double compute_x(const double y) const;
  double compute_distance (const point &p) const;
};

struct polygon {
    int vertex_num;
    std::vector<point> vertex;

    // Конструктор по умолчанию (без параметров)
    polygon();

    polygon(std::initializer_list<point> points);

    // Конструктор с параметром для инициализации размера вектора
    polygon(int n);

    // Конструктор копирования
    polygon(const polygon& other);

    // Конструктор, принимающий вектор точек FunctionPoint
    polygon(const std::vector<point>& points);
    size_t size() const;

    // Оператор присваивания
    polygon& operator=(const polygon& other);

    const point &operator[](const int index) const;

    auto begin() const { return vertex.begin(); }
    auto end() const { return vertex.end(); }

    double area () const;
};

bool operator==(const polygon& lhs, const polygon& rhs);

point operator-(const point &left, const point &right);

std::ostream& operator<<(std::ostream& os, const point& fp);

std::ostream& operator<<(std::ostream& os, const polygon& poly);

#endif
