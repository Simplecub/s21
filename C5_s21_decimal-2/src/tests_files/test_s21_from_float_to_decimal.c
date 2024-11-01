#include "suits.h"

START_TEST(s21_from_float_to_decimal1) {
  s21_decimal result;
  s21_decimal *prom = &result;
  float src = 12.0;
  s21_from_float_to_decimal(src, prom);
  s21_decimal origin;
  origin.bits[0] = 0b00000000101101110001101100000000;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000001100000000000000000;
  ck_assert_uint_eq(origin.bits[0], result.bits[0]);
  ck_assert_uint_eq(origin.bits[1], result.bits[1]);
  ck_assert_uint_eq(origin.bits[2], result.bits[2]);
  ck_assert_uint_eq(origin.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_from_float_to_decimal2) {
  s21_decimal result;
  s21_decimal *prom = &result;
  float src = -42.0;
  s21_from_float_to_decimal(src, prom);
  s21_decimal origin;
  origin.bits[0] = 0b00000010100000001101111010000000;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000001100000000000000000;
  ck_assert_uint_eq(origin.bits[0], result.bits[0]);
  ck_assert_uint_eq(origin.bits[1], result.bits[1]);
  ck_assert_uint_eq(origin.bits[2], result.bits[2]);
  ck_assert_uint_eq(origin.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_from_float_to_decimal3) {
  s21_decimal result;
  s21_decimal *prom = &result;
  float src = -4.2;
  s21_from_float_to_decimal(src, prom);
  s21_decimal origin;
  origin.bits[0] = 0b00000000010000000001011000111111;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000001100000000000000000;
  ck_assert_uint_eq(origin.bits[0], result.bits[0]);
  ck_assert_uint_eq(origin.bits[1], result.bits[1]);
  ck_assert_uint_eq(origin.bits[2], result.bits[2]);
  ck_assert_uint_eq(origin.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_from_float_to_decimal4) {
  s21_decimal result;
  s21_decimal *prom = &result;
  float src = -4096;
  s21_from_float_to_decimal(src, prom);
  s21_decimal origin;
  origin.bits[0] = 0b11110100001001000000000000000000;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000001100000000000000000;
  ck_assert_uint_eq(origin.bits[0], result.bits[0]);
  ck_assert_uint_eq(origin.bits[1], result.bits[1]);
  ck_assert_uint_eq(origin.bits[2], result.bits[2]);
  ck_assert_uint_eq(origin.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_from_float_to_decimal5) {
  s21_decimal result;
  s21_decimal *prom = &result;
  float src = 2.0;
  s21_from_float_to_decimal(src, prom);
  s21_decimal origin;
  origin.bits[0] = 0b00000000000111101000010010000000;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000001100000000000000000;
  ck_assert_uint_eq(origin.bits[0], result.bits[0]);
  ck_assert_uint_eq(origin.bits[1], result.bits[1]);
  ck_assert_uint_eq(origin.bits[2], result.bits[2]);
  ck_assert_uint_eq(origin.bits[3], result.bits[3]);
}
END_TEST

int run_s21_from_float_to_decimal() {
  Suite *s = suite_create("\033[45m-=s21_from_float_to_decimal=-\033[0m");
  TCase *tc = tcase_create("case_from_float_to_decimal");

  SRunner *srunner = srunner_create(s);

  int result = 0;

  suite_add_tcase(s, tc);
  tcase_add_test(tc, s21_from_float_to_decimal1);
  tcase_add_test(tc, s21_from_float_to_decimal2);
  tcase_add_test(tc, s21_from_float_to_decimal3);
  tcase_add_test(tc, s21_from_float_to_decimal4);
  tcase_add_test(tc, s21_from_float_to_decimal5);

  srunner_run_all(srunner, CK_NORMAL);
  result = srunner_ntests_failed(srunner);

  srunner_free(srunner);  // чистка памяти srunner

  return result == 0 ? 0 : 1;
}
