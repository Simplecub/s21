
#include "s21_matrix.h"

int s21_sum_or_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result,
                          int znak) {
  int res = OK;
  if (A && A->matrix != NULL && B && B->matrix != NULL && result != NULL) {
    if (A->rows == B->rows && A->columns == B->columns &&
        !s21_create_matrix(A->rows, A->columns, result)) {
      for (int i = 0; i < A->rows && !res; i++) {
        for (int j = 0; j < A->columns && !res; j++) {
          result->matrix[i][j] = znak ? A->matrix[i][j] + B->matrix[i][j]
                                      : A->matrix[i][j] - B->matrix[i][j];
          res = !isfinite(result->matrix[i][j]) ? ERROR_CALC : OK;
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

int s21_mult_matrix_cycle(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = OK;
  for (int i = 0; i < result->rows && !res; i++) {
    for (int j = 0; j < result->columns && !res; j++) {
      for (int k = 0; k < A->columns; k++) {
        result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
      }
      res = !isfinite(result->matrix[i][j]) ? ERROR_CALC : OK;
    }
  }
  return res;
}

int get_determinant_matrix(matrix_t *A, matrix_t *temp_determinant, int m,
                           int n) {
  int res = OK;
  for (int rA = 0, rD = 0; rA < A->rows; rA++) {
    for (int cA = 0, cD = 0; cA < A->columns; cA++) {
      if (rA != m && cA != n) {
        res = (isinf(A->matrix[rA][cA]) || isnan(A->matrix[rA][cA]))
                  ? ERROR_CALC
                  : OK;
        temp_determinant->matrix[rD][cD] = A->matrix[rA][cA];
        cD++;

        if (cD == temp_determinant->columns) {
          rD++;
          cD = 0;
        }
      }
    }
  }
  return res;
}

int inf_or_nan(matrix_t *A) {
  int is_error_calc = 0;
  for (int j = 0; j < A->columns && !is_error_calc; j++) {
    for (int k = 0; k < A->columns && !is_error_calc; k++) {
      if (isinf(A->matrix[j][k]) || isnan(A->matrix[j][k])) {
        is_error_calc = ERROR_CALC;
      }
    }
  }
  return is_error_calc;
}

int copy_matrix(matrix_t *src, matrix_t *dst) {
  int res = OK, check_temp = 0;
  check_temp = s21_create_matrix(src->rows, src->columns, dst);
  if (!check_temp) {
    for (int i = 0; i < dst->rows && !res; i++) {
      for (int j = 0; j < dst->columns && !res; j++) {
        dst->matrix[i][j] = src->matrix[i][j];
        res = (isinf(src->matrix[i][j]) || isnan(src->matrix[i][j]))
                  ? ERROR_CALC
                  : OK;
      }
    }
  }
  return res;
}

void find_no_zero(int *i, int *find_not_zero, int *all_zero, matrix_t temp,
                  double *copy_row) {
  for (*find_not_zero = *i, *all_zero = 1; *find_not_zero < temp.rows;
       *find_not_zero += 1) {
    if (temp.matrix[*find_not_zero][*i]) {
      for (int c = 0; c < temp.columns; c++) {
        copy_row[c] = temp.matrix[*find_not_zero][c];
      }
      *all_zero = 0;
      break;
    }
  }
}