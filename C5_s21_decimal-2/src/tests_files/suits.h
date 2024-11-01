#ifndef SUITS
#define SUITS

#include <check.h>
#include <stdlib.h>

#include "../s21_decimal.h"

#define MAXBITS 4294967295U
#define PLUS 0b00000000000000000000000000000000
#define EXP1 0b00000000000000010000000000000000
// 1 - TRUE
#define TRUE 1
// 0 - FALSE
#define FALSE 0

int run_s21_add();
int run_s21_sub();
int run_s21_mul();
int run_s21_div();

int run_s21_is_less();
int run_s21_is_less_or_equal();
int run_s21_is_greater();
int run_s21_is_greater_or_equal();
int run_s21_is_equal();
int run_s21_is_not_equal();

int run_s21_from_int_to_decimal();
int run_s21_from_float_to_decimal();
int run_s21_from_decimal_to_int();
int run_s21_from_decimal_to_float();

int run_s21_floor();
int run_s21_round();
int run_s21_truncate();
int run_s21_negate();

#endif
