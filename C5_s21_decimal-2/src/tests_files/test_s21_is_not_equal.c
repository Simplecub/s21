#include "suits.h"

START_TEST(s21_is_not_equal_1) {
  s21_decimal dec1 = {
      {12345, 0, 0, 0b00000000000001000000000000000000}};  //  1.2345
  s21_decimal dec2 = {{12, 0, 0, 0b10000000000000010000000000000000}};  // -1.2;
  ck_assert_int_eq(s21_is_not_equal(dec1, dec2), 1);
}
END_TEST

START_TEST(s21_is_not_equal_2) {
  s21_decimal dec1 = {
      {120000, 0, 0, 0b00000000000001000000000000000000}};  //  12.0000
  s21_decimal dec2 = {{12, 0, 0, 0b00000000000000000000000000000000}};  //
  ck_assert_int_eq(s21_is_not_equal(dec1, dec2), 0);
}
END_TEST

START_TEST(s21_is_not_equal_3) {
  s21_decimal dec1 = {{0, 0, 0, 0b00000000000000000000000000000000}};   //  0
  s21_decimal dec2 = {{00, 0, 0, 0b00000000000000010000000000000000}};  //
  ck_assert_int_eq(s21_is_not_equal(dec1, dec2), 0);
}
END_TEST

START_TEST(s21_is_not_equal_4) {
  s21_decimal dec1 = {{0, 0, 0, 0b00000000000000000000000000000000}};  //   0
  s21_decimal dec2 = {{0, 0, 0, 0b10000000000000000000000000000000}};  //  -0;
  ck_assert_int_eq(s21_is_not_equal(dec1, dec2), 1);
}
END_TEST

START_TEST(s21_is_not_equal_5) {
  s21_decimal dec1 = {{0, 0, 0, 0b10000000000000000000000000000000}};  //   -0
  s21_decimal dec2 = {{0, 0, 0, 0b00000000000000000000000000000000}};  //  0;
  ck_assert_int_eq(s21_is_not_equal(dec1, dec2), 1);
}
END_TEST

START_TEST(s21_is_not_equal_6) {
  s21_decimal src1, src2;
  // src1 = 1;
  // src2 = 98745654321;

  src1.bits[0] = 0b00000000000000000000000000000001;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b11111101101100110001110000110001;
  src2.bits[1] = 0b00000000000000000000000000010110;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_not_equal(src1, src2);
  int origin = 1;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(s21_is_not_equal_7) {
  s21_decimal src1, src2;
  // src1 = 9999999999999999999;
  // src2 = 1;

  src1.bits[0] = 0b10001001111001111111111111111111;
  src1.bits[1] = 0b10001010110001110010001100000100;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_not_equal(src1, src2);
  int origin = 1;
  ck_assert_int_eq(result, origin);
}
END_TEST

int run_s21_is_not_equal() {
  Suite *s = suite_create("\033[45m-=s21_is_not_equal=-\033[0m");
  TCase *tc = tcase_create("case_is_not_equal");

  SRunner *srunner = srunner_create(s);

  int result = 0;

  suite_add_tcase(s, tc);

  tcase_add_test(tc, s21_is_not_equal_1);
  tcase_add_test(tc, s21_is_not_equal_2);
  tcase_add_test(tc, s21_is_not_equal_3);
  tcase_add_test(tc, s21_is_not_equal_4);
  tcase_add_test(tc, s21_is_not_equal_5);
  tcase_add_test(tc, s21_is_not_equal_6);
  tcase_add_test(tc, s21_is_not_equal_7);

  srunner_run_all(srunner, CK_NORMAL);
  result = srunner_ntests_failed(srunner);

  srunner_free(srunner);  // чистка памяти srunner

  return result == 0 ? 0 : 1;
}
