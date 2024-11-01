#include "./suits.h"

int main() {
  int number_filed = 0;
  number_filed = run_s21_create_matrix();
  +run_s21_remove_matrix();
  +run_s21_eq_matrix();
  +run_s21_sum_matrix();
  +run_s21_sub_matrix();
  +run_s21_mult_number();
  +run_s21_mult_matrix();
  +run_s21_transpose();
  +run_s21_calc_complements();
  +run_s21_determinant();
  +run_s21_inverse_matrix();
  return (number_filed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
