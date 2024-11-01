#include "s21_matrix.h"

int s21_determinant(matrix_t *A, double *result) {
  int res = OK;
  if (result == NULL || A == NULL || A->matrix == NULL) {
    res = ERROR_INIT;
  } else if (A->rows != A->columns)
    res = ERROR_CALC;
  matrix_t temp = {0};
  //создание временной матрицы и копия в нее исходной
  if (!res) res = copy_matrix(A, &temp) ? ERROR_CALC : res;
  if (!res) {
    double *copy_row = (double *)calloc(A->columns, sizeof(double));
    *result = 1.;
    int find_not_zero = 0, all_zero = 1, znak = 1;

    for (int i = 0; i < temp.rows - 1 && *result; i++) {
      // находим не нулевой элемент
      find_no_zero(&i, &find_not_zero, &all_zero, temp, copy_row);
      // убираем ноль из диагонали
      if (temp.matrix[i][i] == 0. && !all_zero) {
        for (int c = 0; c < temp.columns; c++) {
          temp.matrix[find_not_zero][c] = temp.matrix[i][c];
        }
        for (int c = 0; c < temp.columns; c++) {
          temp.matrix[i][c] = copy_row[c];
        }
        znak *= -1;
      }
      // если все нули то det = 0
      if (all_zero) {
        *result = 0.;
      } else {
        for (int t = i + 1; t < temp.rows; t++) {
          double temp_mult = temp.matrix[t][i] / temp.matrix[i][i];
          for (int k = i; k < temp.columns; k++) {
            temp.matrix[t][k] -= temp.matrix[i][k] * temp_mult;
          }
        }
      }
    }

    for (int m = 0; m < A->rows; m++) {
      *result *= temp.matrix[m][m];
    }
    *result = *result ? (*result * znak) : *result;
    free(copy_row);
  }
  if (!res) s21_remove_matrix(&temp);
  return res;
}
