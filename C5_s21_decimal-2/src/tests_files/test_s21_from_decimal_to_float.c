#include "suits.h"

START_TEST(s21_from_decimal_to_float1) {
  s21_decimal src;
  src.bits[0] = 0b00000000000000000000000000001000;
  src.bits[1] = 0b00000000000000000000000000000000;
  src.bits[2] = 0b00000000000000000000000000000000;
  src.bits[3] = 0b00000000000000000000000000000000;
  float prom;
  float *result = &prom;
  s21_from_decimal_to_float(src, result);
  float origin = 8.0;
  ck_assert_float_eq(prom, origin);
}
END_TEST

START_TEST(s21_from_decimal_to_float2) {
  s21_decimal src;
  src.bits[0] = 0b00000000000000000000000000101000;
  src.bits[1] = 0b00000000000000000000000000000000;
  src.bits[2] = 0b00000000000000000000000000000000;
  src.bits[3] = 0b10000000000000000000000000000000;
  float prom;
  float *result = &prom;
  s21_from_decimal_to_float(src, result);
  float origin = -40.0;
  ck_assert_float_eq(prom, origin);
}
END_TEST

START_TEST(s21_from_decimal_to_float3) {
  s21_decimal src;
  src.bits[0] = 0b00000000000000000000000000001000;
  src.bits[1] = 0b00000000000000000000000000000000;
  src.bits[2] = 0b00000000000000000000000000000000;
  src.bits[3] = 0b00000000000000010000000000000000;
  float prom;
  float *result = &prom;
  s21_from_decimal_to_float(src, result);
  float origin = 0.8;
  ck_assert_float_eq(prom, origin);
}
END_TEST

START_TEST(s21_from_decimal_to_float4) {
  s21_decimal src;
  src.bits[0] = 0b00000000000000000000000000011000;
  src.bits[1] = 0b00000000000000000000000000000000;
  src.bits[2] = 0b00000000000000000000000000000000;
  src.bits[3] = 0b00000000000000010000000000000000;
  float prom;
  float *result = &prom;
  s21_from_decimal_to_float(src, result);
  float origin = 2.4;
  ck_assert_float_eq(prom, origin);
}
END_TEST

START_TEST(s21_from_decimal_to_float5) {
  s21_decimal src;
  src.bits[0] = 0b00000000000000000000000000011000;
  src.bits[1] = 0b00000000000000000000000000000000;
  src.bits[2] = 0b00000000000000000000000000000000;
  src.bits[3] = 0b00000000000000010000000000000000;
  float prom;
  float *result = &prom;
  s21_from_decimal_to_float(src, result);
  float origin = 2.4;
  ck_assert_float_eq(prom, origin);
}
END_TEST

START_TEST(s21_from_decimal_to_float6) {
  s21_decimal src;
  src.bits[0] = 0b00011000000000000010000000010001;
  src.bits[1] = 0b00000000000000000000000000000000;
  src.bits[2] = 0b00000000000000000000000000000000;
  src.bits[3] = 0b10000000000000010000000000000000;
  float prom;
  float *result = &prom;
  s21_from_decimal_to_float(src, result);
  float origin = -40266139.3;
  ck_assert_float_eq(prom, origin);
}
END_TEST

START_TEST(s21_from_decimal_to_float7) {
  s21_decimal src;
  src.bits[0] = 0b00011000000000000010000000010001;
  src.bits[1] = 0b00000000000000000000000000000000;
  src.bits[2] = 0b00000000000000000000000000000000;
  src.bits[3] = 0b10000000000001010000000000000000;
  float prom;
  float *result = &prom;
  s21_from_decimal_to_float(src, result);
  float origin = -4026.61393;
  ck_assert_float_eq(prom, origin);
}
END_TEST

START_TEST(s21_from_decimal_to_float8) {
  s21_decimal src;
  src.bits[0] = 0b00000000000000000000000000000000;
  src.bits[1] = 0b00000000000000000000000000000101;
  src.bits[2] = 0b00000000000000000000000000000000;
  src.bits[3] = 0b00000000000000000000000000000000;
  float prom;
  float *result = &prom;
  s21_from_decimal_to_float(src, result);
  float origin = 21474836480.0;
  ck_assert_float_eq(prom, origin);
}
END_TEST

START_TEST(s21_from_decimal_to_float9) {
  s21_decimal src;
  src.bits[0] = 0b00000000000000000000000000010001;
  src.bits[1] = 0b00000000000000000000000000000101;
  src.bits[2] = 0b00000000000000000000000000000000;
  src.bits[3] = 0b10000000000000100000000000000000;
  float prom;
  float *result = &prom;
  s21_from_decimal_to_float(src, result);
  float origin = -214748364.97;
  ck_assert_float_eq(prom, origin);
}
END_TEST

int run_s21_from_decimal_to_float() {
  Suite *s = suite_create("\033[45m-=s21_from_decimal_to_float=-\033[0m");
  TCase *tc = tcase_create("case_from_decimal_to_float");

  SRunner *srunner = srunner_create(s);

  int result = 0;

  suite_add_tcase(s, tc);
  tcase_add_test(tc, s21_from_decimal_to_float1);
  tcase_add_test(tc, s21_from_decimal_to_float2);
  tcase_add_test(tc, s21_from_decimal_to_float3);
  tcase_add_test(tc, s21_from_decimal_to_float4);
  tcase_add_test(tc, s21_from_decimal_to_float5);
  tcase_add_test(tc, s21_from_decimal_to_float6);
  tcase_add_test(tc, s21_from_decimal_to_float7);
  tcase_add_test(tc, s21_from_decimal_to_float8);
  tcase_add_test(tc, s21_from_decimal_to_float9);

  srunner_run_all(srunner, CK_NORMAL);
  result = srunner_ntests_failed(srunner);

  srunner_free(srunner);  // чистка памяти srunner

  return result == 0 ? 0 : 1;
}
