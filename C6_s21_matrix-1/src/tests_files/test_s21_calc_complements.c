#include "suits.h"

START_TEST(s21_calc_complements_1) {
  // failure with INCORRECT_MATRIX
  matrix_t A = {};
  s21_create_matrix(3, 3, &A);
  ck_assert_int_eq(s21_calc_complements(&A, NULL), ERROR_INIT);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_calc_complements_2) {
  // success
  matrix_t A = {};
  matrix_t result = {};
  matrix_t eq_matrix = {};
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &eq_matrix);
  A.matrix[0][0] = 1, A.matrix[0][1] = 2, A.matrix[0][2] = 3;
  A.matrix[1][0] = 0, A.matrix[1][1] = 4, A.matrix[1][2] = 2;
  A.matrix[2][0] = 5, A.matrix[2][1] = 2, A.matrix[2][2] = 1;
  ck_assert_int_eq(s21_calc_complements(&A, &result), OK);
  eq_matrix.matrix[0][0] = 0, eq_matrix.matrix[0][1] = 10,
  eq_matrix.matrix[0][2] = -20;
  eq_matrix.matrix[1][0] = 4, eq_matrix.matrix[1][1] = -14,
  eq_matrix.matrix[1][2] = 8;
  eq_matrix.matrix[2][0] = -8, eq_matrix.matrix[2][1] = -2,
  eq_matrix.matrix[2][2] = 4;
  ck_assert_int_eq(s21_eq_matrix(&result, &eq_matrix), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&eq_matrix);
}
END_TEST

START_TEST(s21_calc_complements_3) {
  int res = 0;
  matrix_t A = {0};
  matrix_t Z = {0};
  s21_create_matrix(4, 3, &A);
  res = s21_calc_complements(&A, &Z);
  s21_remove_matrix(&A);
  ck_assert_int_eq(res, ERROR_CALC);
}
END_TEST

START_TEST(s21_calc_complements_4) {
  int res = 0;
  matrix_t A = {0};
  matrix_t Z = {0};
  s21_create_matrix(2, 2, &A);
  s21_remove_matrix(&A);
  res = s21_calc_complements(&A, &Z);
  ck_assert_int_eq(res, ERROR_INIT);
}
END_TEST

int run_s21_calc_complements() {
  Suite *s = suite_create("\033[45m-=s21_calc_complements=-\033[0m");
  TCase *tc = tcase_create("case_calc_complements");

  SRunner *srunner = srunner_create(s);

  int result;

  suite_add_tcase(s, tc);

  tcase_add_test(tc, s21_calc_complements_1);
  tcase_add_test(tc, s21_calc_complements_2);
  tcase_add_test(tc, s21_calc_complements_3);
  tcase_add_test(tc, s21_calc_complements_4);

  srunner_run_all(srunner, CK_NORMAL);
  result = srunner_ntests_failed(srunner);

  srunner_free(srunner);  // чистка памяти srunner

  return result == 0 ? 0 : 1;
}