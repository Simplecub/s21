#include "suits.h"

START_TEST(s21_negateTest1) {
  s21_decimal dec = {{MAX_UINT, 0, 0, 0}};
  s21_decimal res = {};
  s21_decimal result = {{MAX_UINT, 0, 0, 0}};
  set_bit(&result.bits[3], 31, 1);

  s21_negate(dec, &res);

  ck_assert_int_eq(result.bits[0], res.bits[0]);
  ck_assert_int_eq(result.bits[1], res.bits[1]);
  ck_assert_int_eq(result.bits[2], res.bits[2]);
  ck_assert_int_eq(result.bits[3], res.bits[3]);
}
END_TEST

START_TEST(s21_negateTest2) {
  s21_decimal dec = {{0, 0, 0, 0}};
  s21_decimal res = {};
  s21_decimal result = {{0, 0, 0, 0}};

  s21_negate(dec, &res);

  ck_assert_int_eq(result.bits[0], res.bits[0]);
  ck_assert_int_eq(result.bits[1], res.bits[1]);
  ck_assert_int_eq(result.bits[2], res.bits[2]);
  ck_assert_int_eq(result.bits[3], res.bits[3]);
}
END_TEST

START_TEST(s21_negateTest3) {
  s21_decimal dec = {{1, 0, 0, 0}};
  s21_decimal res = {};
  s21_decimal result = {{1, 0, 0, 0}};

  set_bit(&result.bits[3], 31, 1);
  s21_negate(dec, &res);

  ck_assert_int_eq(result.bits[0], res.bits[0]);
  ck_assert_int_eq(result.bits[1], res.bits[1]);
  ck_assert_int_eq(result.bits[2], res.bits[2]);
  ck_assert_int_eq(result.bits[3], res.bits[3]);
}
END_TEST

START_TEST(s21_negateTest4) {
  s21_decimal dec = {{MAX_UINT, MAX_UINT, MAX_UINT, 0}};
  s21_decimal res = {};
  s21_decimal result = {{MAX_UINT, MAX_UINT, MAX_UINT, 0}};
  set_bit(&result.bits[3], 31, 1);

  s21_negate(dec, &res);

  ck_assert_int_eq(result.bits[0], res.bits[0]);
  ck_assert_int_eq(result.bits[1], res.bits[1]);
  ck_assert_int_eq(result.bits[2], res.bits[2]);
  ck_assert_int_eq(result.bits[3], res.bits[3]);
}
END_TEST

START_TEST(s21_negateTest5) {
  s21_decimal dec = {{MAX_UINT, MAX_UINT, MAX_UINT, 0}};
  s21_decimal res = {};
  s21_decimal result = {{MAX_UINT, MAX_UINT, MAX_UINT, 0}};
  set_bit(&dec.bits[3], 31, 1);

  s21_negate(dec, &res);

  ck_assert_int_eq(result.bits[0], res.bits[0]);
  ck_assert_int_eq(result.bits[1], res.bits[1]);
  ck_assert_int_eq(result.bits[2], res.bits[2]);
  ck_assert_int_eq(result.bits[3], res.bits[3]);
}
END_TEST

START_TEST(s21_negateTest6) {
  s21_decimal dec = {};
  int error = 1;
  ck_assert_int_eq(error, s21_negate(dec, NULL));
}
END_TEST

int run_s21_negate() {
  Suite *s = suite_create("\033[45m-=s21_negate=-\033[0m");
  TCase *tc = tcase_create("case_negate");

  SRunner *srunner = srunner_create(s);

  int result = 0;

  suite_add_tcase(s, tc);
  tcase_add_test(tc, s21_negateTest1);
  tcase_add_test(tc, s21_negateTest2);
  tcase_add_test(tc, s21_negateTest3);
  tcase_add_test(tc, s21_negateTest4);
  tcase_add_test(tc, s21_negateTest5);
  tcase_add_test(tc, s21_negateTest6);

  srunner_run_all(srunner, CK_NORMAL);
  result = srunner_ntests_failed(srunner);

  srunner_free(srunner);  // чистка памяти srunner

  return result == 0 ? 0 : 1;
}
