#include "./suits.h"

int main() {
  int number_filed = 0;
  number_filed =
      +run_s21_add() + run_s21_sub() + run_s21_mul() + run_s21_div() +
      run_s21_is_less() + run_s21_is_less_or_equal() + run_s21_is_greater() +
      run_s21_is_greater_or_equal() + run_s21_is_equal() +
      run_s21_is_not_equal() + run_s21_from_int_to_decimal() +
      run_s21_from_float_to_decimal() + run_s21_from_decimal_to_int() +
      run_s21_from_decimal_to_float() + run_s21_floor() + run_s21_round() +
      run_s21_truncate() + run_s21_negate();
  return (number_filed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
