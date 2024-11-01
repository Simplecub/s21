#include "suits.h"

START_TEST(add_0) {
  s21_decimal val1 = {{15, 0, 0, ~(MAX_UINT / 2)}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_1) {
  s21_decimal val1 = {{15, 0, 0, 0}};
  s21_decimal val2 = {{15, 0, 0, ~(MAX_UINT / 2)}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_2) {
  s21_decimal val1 = {{MAX_UINT, MAX_UINT, MAX_UINT, MAX_UINT}};
  s21_decimal val2 = {{1, 0, 0, MAX_UINT}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_3) {
  s21_decimal val1 = {{MAX_UINT, MAX_UINT, ~(MAX_UINT / 2), 65537}};
  s21_decimal val2 = {{MAX_UINT, MAX_UINT, ~(MAX_UINT / 2), 65537}};
  s21_decimal res;
  ck_assert_int_eq(1, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_4) {
  s21_decimal val1 = {{8, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST
START_TEST(add_6) {
  s21_decimal val1 = {{8, 0, 0, ~(MAX_UINT / 2)}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
  //    printf("6: %d\n", addBit(val1, val2, 0));
}
END_TEST
START_TEST(add_5) {
  s21_decimal val1 = {{2, 1, 1, 0}};
  s21_decimal val2 = {{8, 1, 1, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_7) {
  s21_decimal val1 = {{2, 0, 0, ~(MAX_UINT / 2)}};
  s21_decimal val2 = {{8, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
  //    printf("7: %d\n", addBit(val1, val2,  NULL));
}
END_TEST

START_TEST(add_8) {
  s21_decimal val1 = {{0}};
  s21_decimal val2 = {{0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
  //    printf("8: %d\n", addBit(val1, val2, answer));
}
END_TEST

int run_s21_add() {
  Suite *s = suite_create("\033[45m-=s21_add=-\033[0m");
  TCase *tc = tcase_create("case_add");

  SRunner *srunner = srunner_create(s);

  int result;

  suite_add_tcase(s, tc);
  tcase_add_test(tc, add_0);
  tcase_add_test(tc, add_1);
  tcase_add_test(tc, add_2);
  tcase_add_test(tc, add_3);
  tcase_add_test(tc, add_4);
  tcase_add_test(tc, add_5);
  tcase_add_test(tc, add_6);
  tcase_add_test(tc, add_7);
  tcase_add_test(tc, add_8);

  srunner_run_all(srunner, CK_NORMAL);
  result = srunner_ntests_failed(srunner);

  srunner_free(srunner);  // чистка памяти srunner

  return result == 0 ? 0 : 1;
}