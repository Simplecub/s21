
#include "s21_matrix.h"

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int res = FAILURE;
  if (A && B && A->rows == B->rows && A->columns == B->columns) {
    res = SUCCESS;
    for (int rA = 0; rA < A->rows && res; rA++) {
      for (int cA = 0; cA < A->columns && res; cA++) {
        if (fabs(A->matrix[rA][cA] - B->matrix[rA][cA]) > 1e-7) {
          res = FAILURE;
        }
      }
    }
  }
  return res;
}
