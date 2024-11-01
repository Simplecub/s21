
#include "s21_matrix.h"

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int res = OK;
  if (A != NULL && result != NULL) {
    if (!inf_or_nan(A) && !s21_create_matrix(A->rows, A->columns, result) &&
        isfinite(number)) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] * number;
        }
      }
    } else {
      res = ERROR_CALC;
    }
  } else {
    res = ERROR_INIT;
  }
  return res;
}
