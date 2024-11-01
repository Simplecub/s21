#include "suits.h"

START_TEST(s21_determinant_1) {
  // failure with INCORRECT_MATRIX
  matrix_t A = {};
  double det = 0;

  ck_assert_int_eq(s21_determinant(&A, &det), ERROR_INIT);
}
END_TEST

START_TEST(s21_determinant_2) {
  // failure with non-square matrix
  matrix_t A = {};
  double det = 0;
  s21_create_matrix(3, 2, &A);
  ck_assert_int_eq(s21_determinant(&A, &det), ERROR_CALC);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_determinant_3) {
  // success
  matrix_t A = {};
  double det = 0;
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 1, A.matrix[0][1] = 2, A.matrix[0][2] = 3;
  A.matrix[1][0] = 0, A.matrix[1][1] = 0, A.matrix[1][2] = 4;
  A.matrix[2][0] = 5, A.matrix[2][1] = 2, A.matrix[2][2] = 1;
  ck_assert_int_eq(s21_determinant(&A, &det), OK);
  ck_assert_double_eq(det, 32);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_determinant_4) {
  // success with all zero col
  matrix_t A = {};
  double det = 0;
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 0, A.matrix[0][1] = 2, A.matrix[0][2] = 3;
  A.matrix[1][0] = 0, A.matrix[1][1] = 0, A.matrix[1][2] = 4;
  A.matrix[2][0] = 0, A.matrix[2][1] = 2, A.matrix[2][2] = 1;
  ck_assert_int_eq(s21_determinant(&A, &det), OK);
  ck_assert_double_eq(det, 0);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_determinant_5) {
  double determ = 0.0;
  matrix_t A = {0};

  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 4000.87;
  A.matrix[0][1] = 454.0;
  A.matrix[0][2] = 4.0;
  A.matrix[1][0] = 2.0;
  A.matrix[1][1] = 1.897;
  A.matrix[1][2] = 3.0;
  A.matrix[2][0] = 0.000087;
  A.matrix[2][1] = 2.5668;
  A.matrix[2][2] = 1.0;

  s21_determinant(&A, &determ);
  ck_assert_double_eq(determ, -24105.996724156);
  s21_remove_matrix(&A);
}
END_TEST

int run_s21_determinant() {
  Suite *s = suite_create("\033[45m-=s21_determinant=-\033[0m");
  TCase *tc = tcase_create("case_determinant");

  SRunner *srunner = srunner_create(s);

  int result;

  suite_add_tcase(s, tc);

  tcase_add_test(tc, s21_determinant_1);
  tcase_add_test(tc, s21_determinant_2);
  tcase_add_test(tc, s21_determinant_3);
  tcase_add_test(tc, s21_determinant_4);
  tcase_add_test(tc, s21_determinant_5);

  srunner_run_all(srunner, CK_NORMAL);
  result = srunner_ntests_failed(srunner);

  srunner_free(srunner);  // чистка памяти srunner

  return result == 0 ? 0 : 1;
}