#include "slau.h"

double slau::det(const matrix &M) const
{
  return M[0][0] * M[1][1] - M[0][1] * M[1][0];
}

column slau::kramer_method (const matrix &A, const column &b) const
{
  const matrix A1 = {{{{b[0], A[0][1]}},
                      {{b[1], A[1][1]}}}};
  const matrix A2 = {{{{A[0][0], b[0]}},
                      {{A[1][0], b[1]}}}};

  const double x = det(A1) / det(A);
  const double y = det(A2) / det(A);

  return {x, y};
}

column slau::solve() const
{
  const matrix_extended &M = extended_system_matrix;

  const matrix A = {{{{M[0][0],M[0][1]}},
                     {{M[1][0],M[1][1]}}}};

  const column b = {{M[0][2],M[1][2]}};

  return kramer_method(A, b);
}

bool slau::is_consistent() const
{
  const matrix_extended &M = extended_system_matrix;

  const matrix A = {{{{M[0][0],M[0][1]}},
                     {{M[1][0],M[1][1]}}}};

  return det(A) != 0.;
}

