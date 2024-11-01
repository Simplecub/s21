#include "suits.h"

START_TEST(s21_is_less_1) {
  s21_decimal dec5 = {
      {12345, 0, 0, 0b00000000000001000000000000000000}};  //  1.2345
  s21_decimal dec6 = {{12, 0, 0, 0b10000000000000010000000000000000}};  // -1.2
  ck_assert_int_eq(s21_is_less(dec5, dec6), 0);
  ck_assert_int_eq(s21_is_less(dec6, dec5), 1);

  s21_decimal dec7 = {
      {12345, 0, 0, 0b10000000000001000000000000000000}};  // -1.2345
  s21_decimal dec8 = {{12, 0, 0, 0b00000000000000010000000000000000}};  //  1.2;
  ck_assert_int_eq(s21_is_less(dec7, dec8), 1);
  ck_assert_int_eq(s21_is_less(dec8, dec7), 0);

  s21_decimal dec1 = {
      {12345, 0, 0, 0b00000000000001000000000000000000}};  //  1.2345
  s21_decimal dec2 = {{12, 0, 0, 0b00000000000000010000000000000000}};  //  1.2;
  ck_assert_int_eq(s21_is_less(dec1, dec2), 0);
  ck_assert_int_eq(s21_is_less(dec2, dec1), 1);

  s21_decimal dec3 = {
      {12345, 0, 0, 0b10000000000001000000000000000000}};  // -1.2345
  s21_decimal dec4 = {
      {12, 0, 0, 0b10000000000000010000000000000000}};  //  -1.2;
  ck_assert_int_eq(s21_is_less(dec3, dec4), 1);
  ck_assert_int_eq(s21_is_less(dec4, dec3), 0);

  s21_decimal dec9 = {{12345, 0, 0, 0}};
  s21_decimal dec10 = {{12345, 0, 0, 0}};
  ck_assert_int_eq(s21_is_less(dec9, dec10), 0);
  ck_assert_int_eq(s21_is_less(dec10, dec9), 0);

  s21_decimal dec11 = {{0, 0, 0, 0}};
  s21_decimal dec12 = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_is_less(dec11, dec12), 0);
  ck_assert_int_eq(s21_is_less(dec12, dec11), 0);
}
END_TEST

START_TEST(s21_is_less_2) {
  s21_decimal src1, src2;
  int val;
  // 7 < 15 = TRUE
  src1.bits[0] = 7;
  src1.bits[1] = 0;
  src1.bits[2] = 0;
  src1.bits[3] = 0;
  src2.bits[0] = 15;
  src2.bits[1] = 0;
  src2.bits[2] = 0;
  src2.bits[3] = 0;
  val = s21_is_less(src1, src2);
  ck_assert_int_eq(val, TRUE);

  // 15 < 7 = FALSE
  src1.bits[0] = 15;
  src1.bits[1] = 0;
  src1.bits[2] = 0;
  src1.bits[3] = 0;
  src2.bits[0] = 7;
  src2.bits[1] = 0;
  src2.bits[2] = 0;
  src2.bits[3] = 0;
  val = s21_is_less(src1, src2);
  ck_assert_int_eq(val, FALSE);

  // -15 < 7 = TRUE
  src1.bits[0] = 15;
  src1.bits[1] = 0;
  src1.bits[2] = 0;
  src1.bits[3] = MINUS;
  src2.bits[0] = 7;
  src2.bits[1] = 0;
  src2.bits[2] = 0;
  src2.bits[3] = 0;
  val = s21_is_less(src1, src2);
  ck_assert_int_eq(val, TRUE);

  // -15 < -7 = TRUE
  src1.bits[0] = 15;
  src1.bits[1] = 0;
  src1.bits[2] = 0;
  src1.bits[3] = MINUS;
  src2.bits[0] = 15;
  src2.bits[1] = 0;
  src2.bits[2] = 0;
  src2.bits[3] = 0;
  val = s21_is_less(src1, src2);
  ck_assert_int_eq(val, TRUE);

  // 0.7 < 0.15 = FALSE
  src1.bits[0] = 7;
  src1.bits[1] = 0;
  src1.bits[2] = 0;
  src1.bits[3] = EXP1;
  src2.bits[0] = 15;
  src2.bits[1] = 0;
  src2.bits[2] = 0;
  src2.bits[3] = 0b10000000000000100000000000000000;
  val = s21_is_less(src1, src2);
  ck_assert_int_eq(val, FALSE);

  // -0.7 < 0.15 = TRUE
  src1.bits[0] = 7;
  src1.bits[1] = 0;
  src1.bits[2] = 0;
  src1.bits[3] = 0b10000000000000010000000000000000;
  src2.bits[0] = 15;
  src2.bits[1] = 0;
  src2.bits[2] = 0;
  src2.bits[3] = 0b10000000000000100000000000000000;
  val = s21_is_less(src1, src2);
  ck_assert_int_eq(val, TRUE);

  // 0 < 6 = TRUE
  src1.bits[0] = 0;
  src1.bits[1] = 0;
  src1.bits[2] = 0;
  src1.bits[3] = 0;
  src2.bits[0] = 6;
  src2.bits[1] = 0;
  src2.bits[2] = 0;
  src2.bits[3] = 0;
  val = s21_is_less(src1, src2);
  ck_assert_int_eq(val, TRUE);

  // 79228162514264337593543950335 < 79228162514264337593543950335 = FALSE
  src1.bits[0] = MAXBITS;
  src1.bits[1] = MAXBITS;
  src1.bits[2] = MAXBITS;
  src1.bits[3] = 0;
  src2.bits[0] = MAXBITS;
  src2.bits[1] = MAXBITS;
  src2.bits[2] = MAXBITS;
  src2.bits[3] = 0;
  val = s21_is_less(src1, src2);
  ck_assert_int_eq(val, FALSE);
}
END_TEST

int run_s21_is_less() {
  Suite *s = suite_create("\033[45m-=s21_is_less=-\033[0m");
  TCase *tc = tcase_create("case_is_less");

  SRunner *srunner = srunner_create(s);

  int result = 0;

  suite_add_tcase(s, tc);

  tcase_add_test(tc, s21_is_less_1);
  tcase_add_test(tc, s21_is_less_2);

  srunner_run_all(srunner, CK_NORMAL);
  result = srunner_ntests_failed(srunner);

  srunner_free(srunner);  // чистка памяти srunner

  return result == 0 ? 0 : 1;
}
