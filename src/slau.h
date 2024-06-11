#ifndef SLAU_H
#define SLAU_H

#include <array>

using matrix_extended = std::array<std::array<double,3>,2>;
using matrix = std::array<std::array<double,2>,2>;
using column = std::array<double,2>;

class slau
{
  matrix_extended extended_system_matrix;

private:
  double det(const matrix &M) const;
  column kramer_method (const matrix &A, const column &b) const;

public:
  slau(const matrix_extended &M) : extended_system_matrix(M) {}
  ~slau() = default;
  column solve() const;
  bool is_consistent() const;
};

#endif
