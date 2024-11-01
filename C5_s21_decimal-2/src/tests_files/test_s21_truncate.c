#include "suits.h"

START_TEST(s21_truncateTest1) {
  s21_decimal value = {{}};
  int error = 1;

  ck_assert_int_eq(error, s21_truncate(value, NULL));
}
END_TEST

START_TEST(s21_truncateTest2) {
  s21_decimal value = {{1, 0, 0, 0}};
  s21_decimal res = {{}};
  int result = 1;
  s21_truncate(value, &res);
  ck_assert_int_eq(result, res.bits[0]);
}
END_TEST

START_TEST(s21_truncateTest3) {
  s21_decimal value = {{15, 0, 0, 0}};
  set_exp(&value, 4);  // 0,0015
  s21_decimal res = {{}};
  int result = 0;
  s21_truncate(value, &res);
  ck_assert_int_eq(result, res.bits[0]);
}
END_TEST

START_TEST(s21_truncateTest4) {
  s21_decimal value = {{25, 0, 0, 0}};
  set_exp(&value, 1);  // 1,5
  s21_decimal res = {{}};
  int result = 2;
  s21_truncate(value, &res);
  ck_assert_int_eq(result, res.bits[0]);
}
END_TEST

START_TEST(s21_truncateTest5) {
  s21_decimal value = {{123456, 0, 0, 0}};
  set_exp(&value, 3);
  set_bit(&value.bits[3], 31, 1);  // -123,456
  s21_decimal res = {{}};
  s21_decimal result = {{123}};
  set_bit(&result.bits[3], 31, 1);  // -123
  s21_truncate(value, &res);
  ck_assert_int_eq(res.bits[0], result.bits[0]);
  ck_assert_int_eq(res.bits[1], result.bits[1]);
  ck_assert_int_eq(res.bits[2], result.bits[2]);
  ck_assert_int_eq(res.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_truncateTest6) {
  s21_decimal value = {{MAX_UINT, MAX_UINT, MAX_UINT, 0}};
  set_exp(&value, 1);
  s21_decimal res = {{}};
  s21_decimal result = {{}};
  s21_div_by_ten(value, &result);
  s21_truncate(value, &res);
  ck_assert_int_eq(res.bits[0], result.bits[0]);
  ck_assert_int_eq(res.bits[1], result.bits[1]);
  ck_assert_int_eq(res.bits[2], result.bits[2]);
  ck_assert_int_eq(res.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_truncateTest7) {
  s21_decimal value = {{0, 0, MAX_UINT, 0}};
  s21_decimal result = {{0, 0, MAX_UINT, 0}};
  s21_decimal res = {{}};
  s21_truncate(value, &res);
  ck_assert_int_eq(res.bits[0], result.bits[0]);
  ck_assert_int_eq(res.bits[1], result.bits[1]);
  ck_assert_int_eq(res.bits[2], result.bits[2]);
  ck_assert_int_eq(res.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_truncateTest8) {
  s21_decimal value = {{MAX_UINT, MAX_UINT, MAX_UINT, 0}};
  set_exp(&value, 28);
  s21_decimal res = {{}};
  int result = 7;
  s21_truncate(value, &res);
  ck_assert_int_eq(result, res.bits[0]);
}
END_TEST

// работают, добавить, когда появятся функции перевода
/*
START_TEST(s21_truncateTest9){
    float x = 1.23534636745;
    float y = trunc(x);
    s21_decimal value = {{}};
    s21_decimal result = {{}};
    s21_from_float_to_decimal(x,&value);
    s21_truncate(value,&result);
    float res = 0;
    s21_from_decimal_to_float(result,&res);
    ck_assert_double_eq(res,y);
}
END_TEST

START_TEST(s21_truncateTest10){
    float x = 0.243575878981;
    float y = trunc(x);
    s21_decimal value = {{}};
    s21_decimal result = {{}};
    s21_from_float_to_decimal(x,&value);
    s21_truncate(value,&result);
    float res = 0;
    s21_from_decimal_to_float(result,&res);
    ck_assert_double_eq(res,y);
}
END_TEST

START_TEST(s21_truncateTest11){
    float x = -123244625235.45;
    float y = trunc(x);
    s21_decimal value = {{}};
    s21_decimal result = {{}};
    s21_from_float_to_decimal(x,&value);
    s21_truncate(value,&result);
    float res = 0;
    s21_from_decimal_to_float(result,&res);
    ck_assert_double_eq(res,y);
}
END_TEST

START_TEST(s21_truncateTest12){
    float x = 123.45;
    float y = trunc(x);
    s21_decimal value = {{}};
    s21_decimal result = {{}};
    s21_from_float_to_decimal(x,&value);
    s21_truncate(value,&result);
    float res = 0;
    s21_from_decimal_to_float(result,&res);
    ck_assert_double_eq(res,y);
}
END_TEST

START_TEST(s21_truncateTest13){
    float x = 42949.67295;
    float y = trunc(x);
    s21_decimal value = {{}};
    s21_decimal result = {{}};
    s21_from_float_to_decimal(x,&value);
    s21_truncate(value,&result);
    float res = 0;
    s21_from_decimal_to_float(result,&res);
    ck_assert_double_eq(res,y);
}
END_TEST
*/

int run_s21_truncate() {
  Suite *s = suite_create("\033[45m-=s21_truncate=-\033[0m");
  TCase *tc = tcase_create("case_truncate");

  SRunner *srunner = srunner_create(s);

  int result = 0;

  suite_add_tcase(s, tc);
  tcase_add_test(tc, s21_truncateTest1);
  tcase_add_test(tc, s21_truncateTest2);
  tcase_add_test(tc, s21_truncateTest3);
  tcase_add_test(tc, s21_truncateTest4);
  tcase_add_test(tc, s21_truncateTest5);
  tcase_add_test(tc, s21_truncateTest6);
  tcase_add_test(tc, s21_truncateTest7);
  tcase_add_test(tc, s21_truncateTest8);
  // tcase_add_test(tc, s21_truncateTest9);
  // tcase_add_test(tc, s21_truncateTest10);
  // tcase_add_test(tc, s21_truncateTest11);
  // tcase_add_test(tc, s21_truncateTest12);
  // tcase_add_test(tc, s21_truncateTest13);

  srunner_run_all(srunner, CK_NORMAL);
  result = srunner_ntests_failed(srunner);

  srunner_free(srunner);  // чистка памяти srunner

  return result == 0 ? 0 : 1;
}
