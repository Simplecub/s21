#include "suits.h"

START_TEST(s21_mult_matrix_1) {
  // ERROR_INIT -no init
  matrix_t A = {};
  matrix_t result = {};
  s21_create_matrix(3, 3, &A);
  ck_assert_int_eq(s21_mult_matrix(&A, NULL, &result), ERROR_INIT);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_mult_matrix_2) {
  // ERROR_CALC -wrong INFINITY
  matrix_t A = {};
  matrix_t B = {};
  matrix_t result = {};
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);
  B.matrix[1][1] = INFINITY;
  ck_assert_int_eq(s21_mult_matrix(&A, &B, &result), ERROR_CALC);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_mult_matrix_3) {
  // ERROR_CALC -wrong size
  matrix_t A = {};
  matrix_t B = {};
  matrix_t result = {};
  s21_create_matrix(3, 2, &A);
  s21_create_matrix(3, 2, &B);
  ck_assert_int_eq(s21_mult_matrix(&A, &B, &result), ERROR_CALC);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_mult_matrix_4) {
  // SUCCESS with task reference values
  matrix_t A = {};
  matrix_t B = {};
  matrix_t result = {};
  matrix_t eq_matrix = {};
  s21_create_matrix(3, 2, &A);
  A.matrix[0][0] = 1, A.matrix[0][1] = 4;
  A.matrix[1][0] = 2, A.matrix[1][1] = 5;
  A.matrix[2][0] = 3, A.matrix[2][1] = 6;
  s21_create_matrix(2, 3, &B);
  B.matrix[0][0] = 1, B.matrix[0][1] = -1, B.matrix[0][2] = 1;
  B.matrix[1][0] = 2, B.matrix[1][1] = 3, B.matrix[1][2] = 4;
  s21_create_matrix(3, 3, &eq_matrix);
  eq_matrix.matrix[0][0] = 9, eq_matrix.matrix[0][1] = 11,
  eq_matrix.matrix[0][2] = 17;
  eq_matrix.matrix[1][0] = 12, eq_matrix.matrix[1][1] = 13,
  eq_matrix.matrix[1][2] = 22;
  eq_matrix.matrix[2][0] = 15, eq_matrix.matrix[2][1] = 15,
  eq_matrix.matrix[2][2] = 27;
  ck_assert_int_eq(s21_mult_matrix(&A, &B, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &eq_matrix), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&eq_matrix);
}
END_TEST

START_TEST(s21_mult_matrix_5) {
  // ERROR_INIT -no init
  matrix_t A = {};
  matrix_t B = {};
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);
  ck_assert_int_eq(s21_mult_matrix(&A, &B, NULL), ERROR_INIT);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_mult_matrix_6) {
  // ERROR_INIT -no init
  matrix_t result = {};
  matrix_t B = {};
  s21_create_matrix(3, 3, &B);
  ck_assert_int_eq(s21_mult_matrix(NULL, &B, &result), ERROR_INIT);
  s21_remove_matrix(&B);
}
END_TEST

int run_s21_mult_matrix() {
  Suite *s = suite_create("\033[45m-=s21_mult_matrix=-\033[0m");
  TCase *tc = tcase_create("case_mult_matrix");

  SRunner *srunner = srunner_create(s);

  int result;

  suite_add_tcase(s, tc);

  tcase_add_test(tc, s21_mult_matrix_1);
  tcase_add_test(tc, s21_mult_matrix_2);
  tcase_add_test(tc, s21_mult_matrix_3);
  tcase_add_test(tc, s21_mult_matrix_4);
  tcase_add_test(tc, s21_mult_matrix_5);
  tcase_add_test(tc, s21_mult_matrix_6);

  srunner_run_all(srunner, CK_NORMAL);
  result = srunner_ntests_failed(srunner);

  srunner_free(srunner);  // чистка памяти srunner

  return result == 0 ? 0 : 1;
}