#include "suits.h"

START_TEST(s21_mult_number_1) {
  // ERROR_INIT -no init
  matrix_t A = {};
  ck_assert_int_eq(s21_mult_number(&A, 4.5, NULL), ERROR_INIT);
}
END_TEST

START_TEST(s21_mult_number_2) {
  // ERROR_CALC -wrong size
  matrix_t A = {};
  matrix_t result = {};
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 1, A.matrix[0][1] = 2, A.matrix[0][2] = 3;
  A.matrix[1][0] = 0, A.matrix[1][1] = 4, A.matrix[1][2] = 2;
  A.matrix[2][0] = 2, A.matrix[2][1] = 3, A.matrix[2][2] = NAN;
  ck_assert_int_eq(s21_mult_number(&A, 2, &result), ERROR_CALC);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_mult_number_3) {
  //  ERROR_CALC -wrong INFINITY
  matrix_t A = {};
  matrix_t result = {};
  s21_create_matrix(3, 3, &A);

  A.matrix[0][0] = 1;
  A.matrix[2][2] = INFINITY;
  ck_assert_int_eq(s21_mult_number(&A, 1.5, &result), ERROR_CALC);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_mult_number_4) {
  // ERROR_CALC -wrong number
  matrix_t A = {};
  matrix_t result = {};
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 1, A.matrix[0][1] = 2, A.matrix[0][2] = 3;
  A.matrix[1][0] = 0, A.matrix[1][1] = 4, A.matrix[1][2] = 2;
  A.matrix[2][0] = 2, A.matrix[2][1] = 3, A.matrix[2][2] = NAN;
  ck_assert_int_eq(s21_mult_number(&A, INFINITY, &result), ERROR_CALC);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_mult_number_5) {
  // ERROR_INIT -no Matrix
  matrix_t result = {};
  ck_assert_int_eq(s21_mult_number(NULL, 4.5, &result), ERROR_INIT);
}
END_TEST

START_TEST(s21_mult_number_6) {
  // success
  matrix_t A = {};
  matrix_t result = {};
  matrix_t eq = {};
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &eq);
  eq.matrix[0][0] = 2, eq.matrix[0][1] = 4, eq.matrix[0][2] = 6;
  eq.matrix[1][0] = 0, eq.matrix[1][1] = 8, eq.matrix[1][2] = 4;
  eq.matrix[2][0] = 4, eq.matrix[2][1] = 6, eq.matrix[2][2] = 8;

  A.matrix[0][0] = 1, A.matrix[0][1] = 2, A.matrix[0][2] = 3;
  A.matrix[1][0] = 0, A.matrix[1][1] = 4, A.matrix[1][2] = 2;
  A.matrix[2][0] = 2, A.matrix[2][1] = 3, A.matrix[2][2] = 4;
  ck_assert_int_eq(s21_mult_number(&A, 2, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &eq), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&eq);
}
END_TEST

int run_s21_mult_number() {
  Suite *s = suite_create("\033[45m-=s21_mult_number=-\033[0m");
  TCase *tc = tcase_create("case_mult_number");

  SRunner *srunner = srunner_create(s);

  int result;

  suite_add_tcase(s, tc);

  tcase_add_test(tc, s21_mult_number_1);
  tcase_add_test(tc, s21_mult_number_2);
  tcase_add_test(tc, s21_mult_number_3);
  tcase_add_test(tc, s21_mult_number_4);
  tcase_add_test(tc, s21_mult_number_5);
  tcase_add_test(tc, s21_mult_number_6);

  srunner_run_all(srunner, CK_NORMAL);
  result = srunner_ntests_failed(srunner);

  srunner_free(srunner);  // чистка памяти srunner

  return result == 0 ? 0 : 1;
}