#include "suits.h"

START_TEST(s21_floorTest1) {
  s21_decimal value = {{}};
  int error = 1;

  ck_assert_int_eq(error, s21_floor(value, NULL));
}
END_TEST

START_TEST(s21_floorTest2) {
  s21_decimal value = {{1, 0, 0, 0}};
  s21_decimal res = {{}};
  int result = 1;
  s21_floor(value, &res);
  ck_assert_int_eq(result, res.bits[0]);
}
END_TEST

START_TEST(s21_floorTest3) {
  s21_decimal value = {{15, 0, 0, 0}};
  set_exp(&value, 4);  // 0,0015
  s21_decimal res = {{}};
  int result = 0;
  s21_floor(value, &res);
  ck_assert_int_eq(result, res.bits[0]);
}
END_TEST

START_TEST(s21_floorTest4) {
  s21_decimal value = {{15, 0, 0, 0}};
  set_bit(&value.bits[3], 31, 1);
  set_exp(&value, 4);  // -0,0015
  s21_decimal res = {{}};
  s21_decimal answer = {{1}};
  set_bit(&answer.bits[3], 31, 1);  // -1
  s21_floor(value, &res);
  ck_assert_int_eq(answer.bits[3], res.bits[3]);
  ck_assert_int_eq(answer.bits[0], res.bits[0]);
}
END_TEST

START_TEST(s21_floorTest5) {
  s21_decimal value = {{35, 0, 0, 0}};
  s21_decimal res = {{}};
  s21_decimal answer = {{35}};
  s21_floor(value, &res);
  ck_assert_int_eq(answer.bits[0], res.bits[0]);
}
END_TEST

START_TEST(s21_floorTest6) {
  s21_decimal value = {{12345, 0, 0, 0}};
  set_exp(&value, 2);
  set_bit(&value.bits[3], 31, 1);  // -123,45
  s21_decimal res = {{}};
  s21_decimal answer = {{124}};
  set_bit(&answer.bits[3], 31, 1);  // -124
  s21_floor(value, &res);
  ck_assert_int_eq(answer.bits[0], res.bits[0]);
}
END_TEST

START_TEST(s21_floorTest7) {
  s21_decimal value = {{35, 0, 0, 0}};
  set_bit(&value.bits[3], 31, 1);  // -35
  s21_decimal res = {{}};
  s21_decimal answer = {{35}};
  set_bit(&answer.bits[3], 31, 1);  // -35
  s21_floor(value, &res);
  ck_assert_int_eq(answer.bits[0], res.bits[0]);
  ck_assert_int_eq(answer.bits[3], res.bits[3]);
}
END_TEST

START_TEST(s21_floorTest8) {
  s21_decimal value = {{0}};
  s21_decimal res = {{}};
  int result = 0;
  s21_floor(value, &res);
  ck_assert_int_eq(result, res.bits[0]);
}
END_TEST

START_TEST(s21_floorTest9) {
  s21_decimal value = {{MAX_UINT, MAX_UINT, MAX_UINT, 0}};
  s21_decimal res = {{}};
  s21_decimal answer = {{MAX_UINT, MAX_UINT, MAX_UINT, 0}};
  s21_floor(value, &res);
  ck_assert_int_eq(answer.bits[0], res.bits[0]);
  ck_assert_int_eq(answer.bits[1], res.bits[1]);
  ck_assert_int_eq(answer.bits[2], res.bits[2]);
  ck_assert_int_eq(answer.bits[3], res.bits[3]);
}
END_TEST

START_TEST(s21_floorTest10) {
  s21_decimal value = {{MAX_UINT, MAX_UINT, MAX_UINT, 0}};
  set_exp(&value, 1);
  s21_decimal res = {{}}, answer = {{}};
  s21_decimal pre_answer = {{MAX_UINT, MAX_UINT, MAX_UINT, 0}};
  s21_div_by_ten(pre_answer, &answer);
  s21_floor(value, &res);
  ck_assert_int_eq(answer.bits[0], res.bits[0]);
  ck_assert_int_eq(answer.bits[1], res.bits[1]);
  ck_assert_int_eq(answer.bits[2], res.bits[2]);
  ck_assert_int_eq(answer.bits[3], res.bits[3]);
}
END_TEST

int run_s21_floor() {
  Suite *s = suite_create("\033[45m-=s21_floor=-\033[0m");
  TCase *tc = tcase_create("case_floor");

  SRunner *srunner = srunner_create(s);

  int result = 0;

  suite_add_tcase(s, tc);
  tcase_add_test(tc, s21_floorTest1);
  tcase_add_test(tc, s21_floorTest2);
  tcase_add_test(tc, s21_floorTest3);
  tcase_add_test(tc, s21_floorTest4);
  tcase_add_test(tc, s21_floorTest5);
  tcase_add_test(tc, s21_floorTest6);
  tcase_add_test(tc, s21_floorTest7);
  tcase_add_test(tc, s21_floorTest8);
  tcase_add_test(tc, s21_floorTest9);
  tcase_add_test(tc, s21_floorTest10);

  srunner_run_all(srunner, CK_NORMAL);
  result = srunner_ntests_failed(srunner);

  srunner_free(srunner);  // чистка памяти srunner

  return result == 0 ? 0 : 1;
}
