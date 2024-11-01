
#include "s21_matrix.h"

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int res = OK;
  if (result == NULL || A == NULL || A->matrix == NULL) {
    res = ERROR_INIT;
  } else if (A->rows != A->columns && !res) {
    res = ERROR_CALC;
  }

  double d = 0.;
  if (!res) {
    res = s21_determinant(A, &d);
  }

  if (!res && d) {
    matrix_t t, c;
    s21_calc_complements(A, &c);
    s21_transpose(&c, &t);
    s21_mult_number(&t, 1 / d, result);

    s21_remove_matrix(&t);
    s21_remove_matrix(&c);
  } else if (!res) {
    res = ERROR_CALC;
  }

  return res;
}
