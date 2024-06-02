#ifndef SLAU_H
#define SLAU_H

#include <array>

using matrix_2x2 = std::array<std::array<double,2>,2>;
using matrix_2x1 = std::array<double,2>;

namespace matrix2x2
{
  using matrix = matrix_2x2;
  using column = matrix_2x1;

  det(const matrix &A);
  std::pair<double, double> kramer_method (const matrix &A, const column &b);
}

#endif
