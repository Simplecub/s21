
#include "s21_matrix.h"

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = (A && A->matrix != NULL && B && B->matrix != NULL && result != NULL)
                ? OK
                : ERROR_INIT;
  if (!res && A->columns == B->rows) {
    if (!(res = s21_create_matrix(A->rows, B->columns, result))) {
      res = s21_mult_matrix_cycle(A, B, result);
    }
  } else if (!res) {
    res = ERROR_CALC;
  }
  return res;
}