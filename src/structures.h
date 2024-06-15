#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <vector>
#include <cmath>
#include <iostream>

class polygon;

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

enum class orientation
{
  horizontal,
  vertical,
  other
};

struct grid_edge
{
  point start;
  point end;

  orientation get_orientation() const;
};

struct rectangular_grid {
    double delta_x;
    double delta_y;

    size_t x_size;
    size_t y_size;

    rectangular_grid();

    rectangular_grid(double dx, double dy, size_t sizex, size_t sizey);

    rectangular_grid(size_t sizex, size_t sizey);

    polygon get_cell (const int i, const int j) const;

    grid_edge get_vertical_edge (const int i, const int j) const;
    grid_edge get_horizontal_edge (const int i, const int j) const;

    rectangular_grid& operator=(const rectangular_grid& other);
};

struct table_function {
    std::vector<std::vector<double>> points;
    rectangular_grid f_grid;

    // Конструктор по умолчанию (без параметров)
    table_function();

    // Конструктор с параметром для инициализации размера вектора
    table_function(int n, int m);

    table_function& operator=(const table_function& other);

    double value (const int i, const int j) { return points[i][j]; }
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

struct computation_params {
    table_function velocity;
    double delta_t; 
    rectangular_grid grid_f;

    // Дефолтный конструктор
    computation_params();

    // Конструктор с параметрами
    computation_params(table_function vel, double dt, rectangular_grid grid_f);
};



bool operator==(const table_function& lhs, const table_function& rhs);

bool operator==(const rectangular_grid& lhs, const rectangular_grid& rhs);

bool operator==(const polygon& lhs, const polygon& rhs);

bool operator==(const computation_params& lhs, const computation_params& rhs);

std::ostream& operator<<(std::ostream& os, const point& fp);

std::ostream& operator<<(std::ostream& os, const polygon& poly);

point operator-(const point &left, const point &right);

#endif

