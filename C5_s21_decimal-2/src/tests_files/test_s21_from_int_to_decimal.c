#include "suits.h"

START_TEST(s21_from_int_to_decimal1) {
  s21_decimal result;
  s21_decimal *prom = &result;
  int src = 12;
  s21_from_int_to_decimal(src, prom);
  s21_decimal origin;
  origin.bits[0] = 0b00000000000000000000000000001100;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_uint_eq(origin.bits[0], result.bits[0]);
  ck_assert_uint_eq(origin.bits[1], result.bits[1]);
  ck_assert_uint_eq(origin.bits[2], result.bits[2]);
  ck_assert_uint_eq(origin.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_from_int_to_decimal2) {
  s21_decimal result;
  s21_decimal *prom = &result;
  int src = -12;
  s21_from_int_to_decimal(src, prom);
  s21_decimal origin;
  origin.bits[0] = 0b00000000000000000000000000001100;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_uint_eq(origin.bits[0], result.bits[0]);
  ck_assert_uint_eq(origin.bits[1], result.bits[1]);
  ck_assert_uint_eq(origin.bits[2], result.bits[2]);
  ck_assert_uint_eq(origin.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_from_int_to_decimal3) {
  s21_decimal result;
  s21_decimal *prom = &result;
  int src = -123;
  s21_from_int_to_decimal(src, prom);
  s21_decimal origin;
  origin.bits[0] = 0b00000000000000000000000001111011;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_uint_eq(origin.bits[0], result.bits[0]);
  ck_assert_uint_eq(origin.bits[1], result.bits[1]);
  ck_assert_uint_eq(origin.bits[2], result.bits[2]);
  ck_assert_uint_eq(origin.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_from_int_to_decimal4) {
  s21_decimal result;
  s21_decimal *prom = &result;
  int src = -21;
  s21_from_int_to_decimal(src, prom);
  s21_decimal origin;
  origin.bits[0] = 0b00000000000000000000000000010101;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_uint_eq(origin.bits[0], result.bits[0]);
  ck_assert_uint_eq(origin.bits[1], result.bits[1]);
  ck_assert_uint_eq(origin.bits[2], result.bits[2]);
  ck_assert_uint_eq(origin.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_from_int_to_decimal5) {
  s21_decimal result;
  s21_decimal *prom = &result;
  int src = 1267;
  s21_from_int_to_decimal(src, prom);
  s21_decimal origin;
  origin.bits[0] = 0b00000000000000000000010011110011;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_uint_eq(origin.bits[0], result.bits[0]);
  ck_assert_uint_eq(origin.bits[1], result.bits[1]);
  ck_assert_uint_eq(origin.bits[2], result.bits[2]);
  ck_assert_uint_eq(origin.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_from_int_to_decimal6) {
  s21_decimal result;
  s21_decimal *prom = &result;
  int src = 212121;
  s21_from_int_to_decimal(src, prom);
  s21_decimal origin;
  origin.bits[0] = 0b00000000000000110011110010011001;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_uint_eq(origin.bits[0], result.bits[0]);
  ck_assert_uint_eq(origin.bits[1], result.bits[1]);
  ck_assert_uint_eq(origin.bits[2], result.bits[2]);
  ck_assert_uint_eq(origin.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_from_int_to_decimal7) {
  s21_decimal result;
  s21_decimal *prom = &result;
  int src = 0;
  s21_from_int_to_decimal(src, prom);
  s21_decimal origin;
  origin.bits[0] = 0b00000000000000000000000000000000;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_uint_eq(origin.bits[0], result.bits[0]);
  ck_assert_uint_eq(origin.bits[1], result.bits[1]);
  ck_assert_uint_eq(origin.bits[2], result.bits[2]);
  ck_assert_uint_eq(origin.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_from_int_to_decimal8) {
  s21_decimal *result = NULL;
  int src = 21;
  ck_assert_int_eq(1, s21_from_int_to_decimal(src, result));
}
END_TEST

START_TEST(s21_from_int_to_decimal9) {
  s21_decimal result;
  s21_decimal *prom = &result;
  int src = 2147483647;
  s21_from_int_to_decimal(src, prom);
  s21_decimal origin;
  origin.bits[0] = 0b01111111111111111111111111111111;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_uint_eq(origin.bits[0], result.bits[0]);
  ck_assert_uint_eq(origin.bits[1], result.bits[1]);
  ck_assert_uint_eq(origin.bits[2], result.bits[2]);
  ck_assert_uint_eq(origin.bits[3], result.bits[3]);
}
END_TEST

int run_s21_from_int_to_decimal() {
  Suite *s = suite_create("\033[45m-=s21_from_int_to_decimal=-\033[0m");
  TCase *tc = tcase_create("case_from_int_to_decimal");

  SRunner *srunner = srunner_create(s);

  int result = 0;

  suite_add_tcase(s, tc);
  tcase_add_test(tc, s21_from_int_to_decimal1);
  tcase_add_test(tc, s21_from_int_to_decimal2);
  tcase_add_test(tc, s21_from_int_to_decimal3);
  tcase_add_test(tc, s21_from_int_to_decimal4);
  tcase_add_test(tc, s21_from_int_to_decimal5);
  tcase_add_test(tc, s21_from_int_to_decimal6);
  tcase_add_test(tc, s21_from_int_to_decimal7);
  tcase_add_test(tc, s21_from_int_to_decimal8);
  tcase_add_test(tc, s21_from_int_to_decimal9);

  srunner_run_all(srunner, CK_NORMAL);
  result = srunner_ntests_failed(srunner);

  srunner_free(srunner);  // чистка памяти srunner

  return result == 0 ? 0 : 1;
}
