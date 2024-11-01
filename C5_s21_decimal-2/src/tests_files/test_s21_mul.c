#include "../utils.h"
#include "suits.h"

START_TEST(mul_0) {
  s21_decimal val1 = {{2, 0, 0, ~(MAX_UINT / 2)}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(2, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_1) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, ~(MAX_UINT / 2)}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(2, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_2) {
  s21_decimal val1 = {{2, 0, 0, ~(MAX_UINT / 2)}};
  s21_decimal val2 = {{2, 0, 0, ~(MAX_UINT / 2)}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_3) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_4) {
  s21_decimal val1 = {{8, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_5) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{8, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST
START_TEST(mul_6) {
  s21_decimal val1 = {{8, 0, 0, ~(MAX_UINT / 2)}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(2, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_7) {
  s21_decimal val1 = {{2, 0, 0, ~(MAX_UINT / 2)}};
  s21_decimal val2 = {{8, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(2, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_8) {
  s21_decimal val1 = {{MAX_UINT, MAX_UINT, MAX_UINT, ~(MAX_UINT / 2)}};
  s21_decimal val2 = {{2, 0, 0, ~(MAX_UINT / 2)}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_9) {
  s21_decimal val1 = {{MAX_UINT, MAX_UINT, MAX_UINT, ~(MAX_UINT / 2)}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(2, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_10) {
  s21_decimal val1 = {{MAX_UINT, MAX_UINT, MAX_UINT, 0}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_11) {
  s21_decimal val1 = {{MAX_UINT, MAX_UINT, MAX_UINT, ~(MAX_UINT / 2)}};
  s21_decimal val2 = {{0, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_ne(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_12) {
  s21_decimal val1 = {{MAX_UINT, MAX_UINT, MAX_UINT, ~(MAX_UINT / 2)}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0}};
  setScale(&val1, 1);
  ck_assert_int_ne(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_13) {
  s21_decimal val1 = {{MAX_UINT, MAX_UINT, MAX_UINT, 0}};
  s21_decimal val2 = {{200, 0, 0, 0}};
  s21_decimal res = {{0}};
  setScale(&val2, 1);
  setScale(&val2, 2);
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_14) {
  s21_decimal val2 = {{MAX_UINT, MAX_UINT, MAX_UINT, 0}};
  s21_decimal val1 = {{20, 0, 0, 0}};
  s21_decimal res = {{0}};
  setScale(&val2, 1);
  setScale(&val2, 2);
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

int run_s21_mul() {
  Suite *s = suite_create("\033[45m-=s21_mul=-\033[0m");
  TCase *tc = tcase_create("case_mul");

  SRunner *srunner = srunner_create(s);

  int result;

  suite_add_tcase(s, tc);
  tcase_add_test(tc, mul_0);
  tcase_add_test(tc, mul_1);
  tcase_add_test(tc, mul_2);
  tcase_add_test(tc, mul_3);
  tcase_add_test(tc, mul_4);
  tcase_add_test(tc, mul_5);
  tcase_add_test(tc, mul_6);
  tcase_add_test(tc, mul_7);
  tcase_add_test(tc, mul_8);
  tcase_add_test(tc, mul_9);
  tcase_add_test(tc, mul_10);
  tcase_add_test(tc, mul_11);
  tcase_add_test(tc, mul_12);
  tcase_add_test(tc, mul_13);
  tcase_add_test(tc, mul_14);
  srunner_run_all(srunner, CK_NORMAL);
  result = srunner_ntests_failed(srunner);

  srunner_free(srunner);  // чистка памяти srunner

  return result == 0 ? 0 : 1;
}