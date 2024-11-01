
#include "math.h"
#include "stdio.h"
#include "stdlib.h"

//сравнение
#define SUCCESS 1
#define FAILURE 0
//структура матрицы
typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

#define OK 0
#define ERROR_INIT 1
#define ERROR_CALC 2
// 0 - OK
// 1 - Ошибка, некорректная матрица
// 2 - Ошибка вычисления (несовпадающие размеры матриц; матрица, для которой
// нельзя провести вычисления и т.д.)

// + создание
int s21_create_matrix(int rows, int columns, matrix_t *result);
// + очистка и уничтожение
void s21_remove_matrix(matrix_t *A);
// + сравнение
int s21_eq_matrix(matrix_t *A, matrix_t *B);
// + сложение
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
// + вычитание
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
// + умножение на число
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
// + умножение двух матриц
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
// + транспонирование
int s21_transpose(matrix_t *A, matrix_t *result);
// + вычисление матрицы алгебраических дополнений
int s21_calc_complements(matrix_t *A, matrix_t *result);
// + вычисление определителя
int s21_determinant(matrix_t *A, double *result);
// + поиск обратной матрицы
int s21_inverse_matrix(matrix_t *A, matrix_t *result);

//доп функции
int s21_sum_or_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result, int znak);
int s21_mult_matrix_cycle(matrix_t *A, matrix_t *B, matrix_t *result);
int inf_or_nan(matrix_t *A);
void find_no_zero(int *i, int *find_not_zero, int *all_zero, matrix_t temp,
                  double *copy_row);
int get_determinant_matrix(matrix_t *A, matrix_t *temp_determinant, int m,
                           int n);
int copy_matrix(matrix_t *src, matrix_t *dst);