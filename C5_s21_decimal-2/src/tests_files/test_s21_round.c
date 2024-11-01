#include "suits.h"

START_TEST(s21_roundTest1) {
  s21_decimal value = {{}};
  int error = 1;

  ck_assert_int_eq(error, s21_round(value, NULL));
}
END_TEST

START_TEST(s21_roundTest2) {
  s21_decimal value = {{1, 0, 0, 0}};
  s21_decimal res = {{}};
  int result = 1;
  s21_round(value, &res);
  ck_assert_int_eq(result, res.bits[0]);
}
END_TEST

START_TEST(s21_roundTest3) {
  s21_decimal value = {{12345, 0, 0, 0}};
  set_exp(&value, 2);  // 123,45
  s21_decimal res = {{}};
  int result = 123;
  s21_round(value, &res);
  ck_assert_int_eq(result, res.bits[0]);
}
END_TEST

START_TEST(s21_roundTest4) {
  s21_decimal value = {{123456789, 0, 0, 0}};
  set_exp(&value, 3);  // 123456,789
  s21_decimal res = {{}};
  int result = 123457;
  s21_round(value, &res);
  ck_assert_int_eq(result, res.bits[0]);
}
END_TEST

START_TEST(s21_roundTest5) {
  s21_decimal value = {{123456789, 0, 0, 0}};
  set_bit(&value.bits[3], 31, 1);
  set_exp(&value, 3);  // -123456,789
  s21_decimal res = {{}};
  s21_decimal result = {{123457}};
  set_bit(&result.bits[3], 31, 1);  // -123457
  s21_round(value, &res);
  ck_assert_int_eq(result.bits[0], res.bits[0]);
  ck_assert_int_eq(result.bits[3], res.bits[3]);
}
END_TEST

START_TEST(s21_roundTest6) {
  s21_decimal value = {{123456789, 0, 0, 0}};
  set_bit(&value.bits[3], 31, 1);
  set_exp(&value, 9);  // -0.123456789
  s21_decimal res = {{}};
  s21_decimal result = {{}};
  s21_round(value, &res);
  ck_assert_int_eq(result.bits[0], res.bits[0]);
  ck_assert_int_eq(result.bits[3], res.bits[3]);
}
END_TEST

START_TEST(s21_roundTest7) {
  s21_decimal value = {{MAX_UINT, 0, 0, 0}};
  set_bit(&value.bits[3], 31, 1);
  set_exp(&value, 1);
  s21_decimal res = {{}};
  s21_decimal result = {{429496730}};
  set_bit(&result.bits[3], 31, 1);
  s21_round(value, &res);
  ck_assert_int_eq(result.bits[0], res.bits[0]);
  ck_assert_int_eq(result.bits[1], res.bits[1]);
  ck_assert_int_eq(result.bits[2], res.bits[2]);
  ck_assert_int_eq(result.bits[3], res.bits[3]);
}
END_TEST

START_TEST(s21_roundTest8) {
  s21_decimal value = {{56789, 0, 0, 0}};
  set_exp(&value, 5);  // 0.56789
  s21_decimal res = {{}};
  s21_decimal result = {{1}};
  s21_round(value, &res);
  ck_assert_int_eq(result.bits[0], res.bits[0]);
  ck_assert_int_eq(result.bits[1], res.bits[1]);
  ck_assert_int_eq(result.bits[2], res.bits[2]);
  ck_assert_int_eq(result.bits[3], res.bits[3]);
}
END_TEST

START_TEST(s21_roundTest9) {
  s21_decimal value = {{46789, 0, 0, 0}};
  set_exp(&value, 5);  // 0.46789
  s21_decimal res = {{}};
  s21_decimal result = {{0}};
  s21_round(value, &res);
  ck_assert_int_eq(result.bits[0], res.bits[0]);
  ck_assert_int_eq(result.bits[1], res.bits[1]);
  ck_assert_int_eq(result.bits[2], res.bits[2]);
  ck_assert_int_eq(result.bits[3], res.bits[3]);
}
END_TEST

START_TEST(s21_roundTest10) {
  s21_decimal value = {{14, 0, 0, 0}};
  set_bit(&value.bits[3], 31, 1);
  set_exp(&value, 1);  // -1.4
  s21_decimal res = {{}};
  s21_decimal result = {{1}};
  set_bit(&result.bits[3], 31, 1);  // -1
  s21_round(value, &res);
  ck_assert_int_eq(result.bits[0], res.bits[0]);
  ck_assert_int_eq(result.bits[1], res.bits[1]);
  ck_assert_int_eq(result.bits[2], res.bits[2]);
  ck_assert_int_eq(result.bits[3], res.bits[3]);
}
END_TEST

START_TEST(s21_roundTest11) {
  s21_decimal value = {{17, 0, 0, 0}};
  set_bit(&value.bits[3], 31, 1);
  set_exp(&value, 1);  // -1.7
  s21_decimal res = {{}};
  s21_decimal result = {{2}};
  set_bit(&result.bits[3], 31, 1);  // -2
  s21_round(value, &res);
  ck_assert_int_eq(result.bits[0], res.bits[0]);
  ck_assert_int_eq(result.bits[1], res.bits[1]);
  ck_assert_int_eq(result.bits[2], res.bits[2]);
  ck_assert_int_eq(result.bits[3], res.bits[3]);
}
END_TEST

START_TEST(s21_roundTest12) {
  s21_decimal value = {{MAX_UINT, 0, 0, 0}};
  set_bit(&value.bits[3], 31, 1);
  set_exp(&value, 10);
  s21_decimal res = {{}};
  s21_decimal result = {{}};
  s21_round(value, &res);
  ck_assert_int_eq(result.bits[0], res.bits[0]);
  ck_assert_int_eq(result.bits[1], res.bits[1]);
  ck_assert_int_eq(result.bits[2], res.bits[2]);
  ck_assert_int_eq(result.bits[3], res.bits[3]);
}
END_TEST

START_TEST(s21_roundTest13) {
  s21_decimal value = {{MAX_UINT, MAX_UINT, MAX_UINT, 0}};
  s21_decimal res = {{}};
  s21_decimal result = {{MAX_UINT, MAX_UINT, MAX_UINT, 0}};
  s21_round(value, &res);
  ck_assert_int_eq(result.bits[0], res.bits[0]);
  ck_assert_int_eq(result.bits[1], res.bits[1]);
  ck_assert_int_eq(result.bits[2], res.bits[2]);
  ck_assert_int_eq(result.bits[3], res.bits[3]);
}
END_TEST

START_TEST(s21_roundTest14) {
  s21_decimal value = {{MAX_UINT, MAX_UINT, MAX_UINT, 0}};
  set_bit(&value.bits[3], 31, 1);
  s21_decimal res = {{}};
  s21_decimal result = {{MAX_UINT, MAX_UINT, MAX_UINT, 0}};
  set_bit(&result.bits[3], 31, 1);
  s21_round(value, &res);
  ck_assert_int_eq(result.bits[0], res.bits[0]);
  ck_assert_int_eq(result.bits[1], res.bits[1]);
  ck_assert_int_eq(result.bits[2], res.bits[2]);
  ck_assert_int_eq(result.bits[3], res.bits[3]);
}
END_TEST

START_TEST(s21_roundTest15) {
  s21_decimal value = {{46, 0, 0, 0}};
  set_exp(&value, 1);  // 4.6
  s21_decimal res = {{}};
  s21_decimal result = {{5}};
  s21_round(value, &res);
  ck_assert_int_eq(result.bits[0], res.bits[0]);
  ck_assert_int_eq(result.bits[1], res.bits[1]);
  ck_assert_int_eq(result.bits[2], res.bits[2]);
  ck_assert_int_eq(result.bits[3], res.bits[3]);
}
END_TEST

START_TEST(s21_roundTest16) {
  s21_decimal value = {{0, MAX_UINT, 0, 0}};
  s21_decimal res = {{}};
  s21_decimal result = {{0, MAX_UINT, 0, 0}};
  s21_round(value, &res);
  ck_assert_int_eq(result.bits[0], res.bits[0]);
  ck_assert_int_eq(result.bits[1], res.bits[1]);
  ck_assert_int_eq(result.bits[2], res.bits[2]);
  ck_assert_int_eq(result.bits[3], res.bits[3]);
}
END_TEST

START_TEST(s21_roundTest17) {
  s21_decimal value = {{1, 0, MAX_UINT, 0}};
  set_bit(&value.bits[3], 31, 1);
  s21_decimal res = {{}};
  s21_decimal result = {{1, 0, MAX_UINT, 0}};
  set_bit(&result.bits[3], 31, 1);
  s21_round(value, &res);
  ck_assert_int_eq(result.bits[0], res.bits[0]);
  ck_assert_int_eq(result.bits[1], res.bits[1]);
  ck_assert_int_eq(result.bits[2], res.bits[2]);
  ck_assert_int_eq(result.bits[3], res.bits[3]);
}
END_TEST

int run_s21_round() {
  Suite *s = suite_create("\033[45m-=s21_round=-\033[0m");
  TCase *tc = tcase_create("case_round");

  SRunner *srunner = srunner_create(s);

  int result = 0;

  suite_add_tcase(s, tc);
  tcase_add_test(tc, s21_roundTest1);
  tcase_add_test(tc, s21_roundTest2);
  tcase_add_test(tc, s21_roundTest3);
  tcase_add_test(tc, s21_roundTest4);
  tcase_add_test(tc, s21_roundTest5);
  tcase_add_test(tc, s21_roundTest6);
  tcase_add_test(tc, s21_roundTest7);
  tcase_add_test(tc, s21_roundTest8);
  tcase_add_test(tc, s21_roundTest9);
  tcase_add_test(tc, s21_roundTest10);
  tcase_add_test(tc, s21_roundTest11);
  tcase_add_test(tc, s21_roundTest12);
  tcase_add_test(tc, s21_roundTest13);
  tcase_add_test(tc, s21_roundTest14);
  tcase_add_test(tc, s21_roundTest15);
  tcase_add_test(tc, s21_roundTest16);
  tcase_add_test(tc, s21_roundTest17);

  srunner_run_all(srunner, CK_NORMAL);
  result = srunner_ntests_failed(srunner);

  srunner_free(srunner);  // чистка памяти srunner

  return result == 0 ? 0 : 1;
}