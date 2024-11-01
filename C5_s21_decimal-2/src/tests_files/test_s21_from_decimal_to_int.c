#include "suits.h"

START_TEST(s21_from_decimal_to_int1) {
  s21_decimal src;
  src.bits[0] = 0b00000000000000000000000000001000;
  src.bits[1] = 0b00000000000000000000000000000000;
  src.bits[2] = 0b00000000000000000000000000000000;
  src.bits[3] = 0b00000000000000000000000000000000;
  int prom;
  int *result = &prom;
  s21_from_decimal_to_int(src, result);
  int origin = 8;
  ck_assert_int_eq(prom, origin);
}
END_TEST

START_TEST(s21_from_decimal_to_int2) {
  s21_decimal src;
  src.bits[0] = 0b00000000000000000000000010000111;
  src.bits[1] = 0b00000000000000000000000000000000;
  src.bits[2] = 0b00000000000000000000000000000000;
  src.bits[3] = 0b00000000000000000000000000000000;
  int prom;
  int *result = &prom;
  s21_from_decimal_to_int(src, result);
  int origin = 135;
  ck_assert_int_eq(prom, origin);
}
END_TEST

START_TEST(s21_from_decimal_to_int3) {
  s21_decimal src;
  src.bits[0] = 0b00000000000000000010000000000000;
  src.bits[1] = 0b00000000000000000000000000000000;
  src.bits[2] = 0b00000000000000000000000000000000;
  src.bits[3] = 0b10000000000000000000000000000000;
  int prom;
  int *result = &prom;
  s21_from_decimal_to_int(src, result);
  int origin = -8192;
  ck_assert_int_eq(prom, origin);
}
END_TEST

START_TEST(s21_from_decimal_to_int4) {
  s21_decimal src;
  src.bits[0] = 0b00000000000000000000000000000000;
  src.bits[1] = 0b00000001000000000000000100000000;
  src.bits[2] = 0b00000000000000000000000000000000;
  src.bits[3] = 0b00000000000000000000000000000000;
  int prom;
  int *result = &prom;
  int origin = 1;
  ck_assert_int_eq(s21_from_decimal_to_int(src, result), origin);
}
END_TEST

START_TEST(s21_from_decimal_to_int5) {
  s21_decimal src;
  src.bits[0] = 0b00000000000000000000000000000000;
  src.bits[1] = 0b00000000000000000000000000000000;
  src.bits[2] = 0b00001000001100000110000000000000;
  src.bits[3] = 0b00000000000000000000000000000000;
  int prom;
  int *result = &prom;
  int origin = 1;
  ck_assert_int_eq(s21_from_decimal_to_int(src, result), origin);
}
END_TEST

START_TEST(s21_from_decimal_to_int6) {
  s21_decimal src;
  src.bits[0] = 0b00001100001000000000000000011010;
  src.bits[1] = 0b00000001000000000000000100000000;
  src.bits[2] = 0b00000000000000000000000000000000;
  src.bits[3] = 0b10000000000000000000000000000000;
  int prom;
  int *result = &prom;
  int origin = 1;
  ck_assert_int_eq(s21_from_decimal_to_int(src, result), origin);
}
END_TEST

START_TEST(s21_from_decimal_to_int7) {
  s21_decimal src;
  src.bits[0] = 0b00001100001000000000000000011010;
  src.bits[1] = 0b00000001000000000000000100000000;
  src.bits[2] = 0b00000000000000000000000000000000;
  src.bits[3] = 0b10000000000001110000000000000000;
  int prom;
  int *result = &prom;
  int origin = 1;
  ck_assert_int_eq(s21_from_decimal_to_int(src, result), origin);
}
END_TEST

START_TEST(s21_from_decimal_to_int8) {
  s21_decimal src;
  src.bits[0] = 0b00000000000000000000000000011010;
  src.bits[1] = 0b00000000000000000000000000000000;
  src.bits[2] = 0b00000000000000000000000000000000;
  src.bits[3] = 0b10000000000001110000000000000000;
  int prom;
  int *result = &prom;
  int origin = 0;
  ck_assert_int_eq(s21_from_decimal_to_int(src, result), origin);
}
END_TEST

START_TEST(s21_from_decimal_to_int9) {
  s21_decimal src;
  src.bits[0] = 0b11111100001000000000000000011010;
  src.bits[1] = 0b00000000000000000000000000000000;
  src.bits[2] = 0b00000000000000000000000000000000;
  src.bits[3] = 0b10000000000001110000000000000000;
  int prom;
  int *result = &prom;
  int origin = 1;
  ck_assert_int_eq(s21_from_decimal_to_int(src, result), origin);
}
END_TEST

START_TEST(s21_from_decimal_to_int10) {
  s21_decimal src;
  src.bits[0] = 0b00001100001000000000000000011010;
  src.bits[1] = 0b00000001000000000000000100000000;
  src.bits[2] = 0b00000000000000000000000000000000;
  src.bits[3] = 0b10000000000000010000000000000000;
  int prom;
  int *result = &prom;
  int origin = 1;
  ck_assert_int_eq(s21_from_decimal_to_int(src, result), origin);
}
END_TEST

START_TEST(s21_from_decimal_to_int11) {
  s21_decimal src;
  src.bits[0] = 0b00000000000000000000000000000001;
  src.bits[1] = 0b00000000000000000000000000000000;
  src.bits[2] = 0b00000000000000000000000000000000;
  src.bits[3] = 0b00000000000000010000000000000000;
  int prom;
  int *result = &prom;
  s21_from_decimal_to_int(src, result);
  int origin = 0;
  ck_assert_int_eq(prom, origin);
}
END_TEST

START_TEST(s21_from_decimal_to_int12) {
  s21_decimal src;
  src.bits[0] = 0b00000000000000000000000000010000;
  src.bits[1] = 0b00000000000000000000000000000000;
  src.bits[2] = 0b00000000000000000000000000000000;
  src.bits[3] = 0b00000000000000010000000000000000;
  int prom;
  int *result = &prom;
  s21_from_decimal_to_int(src, result);
  int origin = 1;
  ck_assert_int_eq(prom, origin);
}
END_TEST

START_TEST(s21_from_decimal_to_int13) {
  s21_decimal src;
  src.bits[0] = 0b00000000000000000000000010000000;
  src.bits[1] = 0b00000000000000000000000000000000;
  src.bits[2] = 0b00000000000000000000000000000000;
  src.bits[3] = 0b00000000000000010000000000000000;
  int prom;
  int *result = &prom;
  s21_from_decimal_to_int(src, result);
  int origin = 12;
  ck_assert_int_eq(prom, origin);
}
END_TEST

int run_s21_from_decimal_to_int() {
  Suite *s = suite_create("\033[45m-=s21_from_decimal_to_int=-\033[0m");
  TCase *tc = tcase_create("case_from_decimal_to_int");

  SRunner *srunner = srunner_create(s);

  int result = 0;

  suite_add_tcase(s, tc);
  tcase_add_test(tc, s21_from_decimal_to_int1);
  tcase_add_test(tc, s21_from_decimal_to_int2);
  tcase_add_test(tc, s21_from_decimal_to_int3);
  tcase_add_test(tc, s21_from_decimal_to_int4);
  tcase_add_test(tc, s21_from_decimal_to_int5);
  tcase_add_test(tc, s21_from_decimal_to_int6);
  tcase_add_test(tc, s21_from_decimal_to_int7);
  tcase_add_test(tc, s21_from_decimal_to_int8);
  tcase_add_test(tc, s21_from_decimal_to_int9);
  tcase_add_test(tc, s21_from_decimal_to_int10);
  tcase_add_test(tc, s21_from_decimal_to_int11);
  tcase_add_test(tc, s21_from_decimal_to_int12);
  tcase_add_test(tc, s21_from_decimal_to_int13);

  srunner_run_all(srunner, CK_NORMAL);
  result = srunner_ntests_failed(srunner);

  srunner_free(srunner);  // чистка памяти srunner

  return result == 0 ? 0 : 1;
}
