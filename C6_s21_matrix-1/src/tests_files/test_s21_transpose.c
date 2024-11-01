#include "suits.h"

START_TEST(s21_transpose_1) {
  // ERROR_INIT - no init
  matrix_t A = {};
  matrix_t result = {};
  ck_assert_int_eq(s21_transpose(&A, &result), ERROR_INIT);
}
END_TEST

START_TEST(s21_transpose_2) {
  // success with unininitialized matrix 3x2
  matrix_t A = {};
  matrix_t result = {};
  s21_create_matrix(3, 2, &A);
  ck_assert_int_eq(s21_transpose(&A, &result), OK);
  ck_assert_int_eq(result.rows, 2);
  ck_assert_int_eq(result.columns, 3);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_transpose_3) {
  // success with unininitialized matrix 2x3
  matrix_t A = {};
  matrix_t result = {};
  s21_create_matrix(2, 3, &A);
  ck_assert_int_eq(s21_transpose(&A, &result), OK);
  ck_assert_int_eq(result.rows, 3);
  ck_assert_int_eq(result.columns, 2);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_transpose_4) {
  // 3x2 matrix
  matrix_t A = {};
  matrix_t result = {};
  matrix_t eq = {};
  s21_create_matrix(3, 2, &A);
  s21_create_matrix(2, 3, &eq);
  A.matrix[0][0] = 1, A.matrix[0][1] = 4;
  A.matrix[1][0] = 2, A.matrix[1][1] = 5;
  A.matrix[2][0] = 3, A.matrix[2][1] = 6;
  ck_assert_int_eq(s21_transpose(&A, &result), OK);
  eq.matrix[0][0] = 1, eq.matrix[0][1] = 2, eq.matrix[0][2] = 3;
  eq.matrix[1][0] = 4, eq.matrix[1][1] = 5, eq.matrix[1][2] = 6;
  ck_assert_int_eq(s21_eq_matrix(&result, &eq), SUCCESS);
  ck_assert_int_eq(result.rows, 2);
  ck_assert_int_eq(result.columns, 3);
  s21_remove_matrix(&A);
  s21_remove_matrix(&eq);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_transpose_5) {
  // ERROR_INIT - no init
  matrix_t A = {};
  ck_assert_int_eq(s21_transpose(&A, NULL), ERROR_INIT);
}
END_TEST

START_TEST(s21_transpose_6) {
  // ERROR_INIT - no init
  matrix_t result = {};
  ck_assert_int_eq(s21_transpose(NULL, &result), ERROR_INIT);
}
END_TEST

int run_s21_transpose() {
  Suite *s = suite_create("\033[45m-=s21_transpose=-\033[0m");
  TCase *tc = tcase_create("case_transpose");

  SRunner *srunner = srunner_create(s);

  int result;

  suite_add_tcase(s, tc);

  tcase_add_test(tc, s21_transpose_1);
  tcase_add_test(tc, s21_transpose_2);
  tcase_add_test(tc, s21_transpose_3);
  tcase_add_test(tc, s21_transpose_4);
  tcase_add_test(tc, s21_transpose_5);
  tcase_add_test(tc, s21_transpose_6);

  srunner_run_all(srunner, CK_NORMAL);
  result = srunner_ntests_failed(srunner);

  srunner_free(srunner);  // чистка памяти srunner

  return result == 0 ? 0 : 1;
}