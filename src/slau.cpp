#include "slau.h"

#include <array>

namespace matrix2x2
{
det(const matrix &A)
{
  return A[0][0] * A[1][1] - A[0][1] * A[1][0];
}

// Ax = b
std::pair<double, double> kramer_method (const matrix &A, const column &b)
{
  const matrix_2x2 A1 = {{b[0], A[0][1]},
                         {b[1], A[1][1]}};
  const matrix_2x2 A2 = {{A[0][0], b[0]},
                         {A[1][0], b[1]}};

  const double x = det(A1) / det(A);
  const double y = det(A2) / det(A);

  return {x, y};
}
}

