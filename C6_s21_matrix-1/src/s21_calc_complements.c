
#include "s21_matrix.h"

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int res = OK, check_temp = 0;
  if (result == NULL || A == NULL || A->matrix == NULL) {
    res = ERROR_INIT;
  } else if (A->rows != A->columns && !res) {
    res = ERROR_CALC;
  }
  if (!res) {
    check_temp = s21_create_matrix(A->rows, A->columns, result);
  }
  res = check_temp ? ERROR_CALC : res;
  //
  matrix_t temp_determinant = {0};
  if (!res && A->rows > 1) {
    s21_create_matrix(A->rows - 1, A->columns - 1, &temp_determinant);

  } else if (!res) {
    result->matrix[0][0] = 1.;
  }

  for (int m = 0; m < A->rows && A->rows > 1 && !res; m++) {
    for (int n = 0; n < A->columns && !res; n++) {
      res = get_determinant_matrix(A, &temp_determinant, m, n);
      s21_determinant(&temp_determinant, &result->matrix[m][n]);
    }
  }

  if (A->rows > 1 && !res) {
    s21_remove_matrix(&temp_determinant);
    for (int m = 0; m < A->rows; m++) {
      for (int n = 0; n < A->columns; n++) {
        result->matrix[m][n] *= pow(-1, (m + n));
      }
    }
  }

  return res;
}