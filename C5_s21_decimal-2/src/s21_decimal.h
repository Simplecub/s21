#ifndef S21_DECIMAL_H
#define S21_DECIMAL_H

#define MAX_UINT 4294967295  // нужно для смещения на 32 бита влево
#define TRUE 1
#define FALSE 0
#define PLUS 0b00000000000000000000000000000000

#include <math.h>  // необхлжима для ftoi
#include <stdio.h>
#include <stdlib.h>  // для тестов

typedef struct {
  unsigned int bits[4];
} s21_decimal;

typedef struct {
  unsigned int bits[6];
} s21_big_decimal;

#define SC 0x00ff0000
#define MINUS 0x80000000
#define GETSCALE(v) ((v.bits[3] & SC) >> 16)
#define CHECKMINUS(v) ((v.bits[3] & MINUS) >> 31)

// доп функции

// приведение к  степени scale (умножение на 10 scale раз)
// возвращает 1 если переполнение
int s21_align_10(s21_decimal *value, int scale);
// сдвиг влево всех интов один раз и возвращение переполнения если оно есть
int s21_shift(s21_decimal *value);
// сложение только мантисс, возвращает переполнение буфера, если есть
int s21_sum(s21_decimal *dst, s21_decimal src);
// из value_1 вычитает value_2
int s21_diff(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

//
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);  //
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);  //
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);  //
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);  //

int s21_is_less(s21_decimal, s21_decimal);              //+
int s21_is_less_or_equal(s21_decimal, s21_decimal);     //+
int s21_is_greater(s21_decimal, s21_decimal);           //+
int s21_is_greater_or_equal(s21_decimal, s21_decimal);  //+
int s21_is_equal(s21_decimal, s21_decimal);             //+
int s21_is_not_equal(s21_decimal, s21_decimal);         //+

int s21_from_int_to_decimal(int src, s21_decimal *dst);      //
int s21_from_float_to_decimal(float src, s21_decimal *dst);  //
int s21_from_decimal_to_int(s21_decimal src, int *dst);      //
int s21_from_decimal_to_float(s21_decimal src, float *dst);  //

int s21_floor(s21_decimal value, s21_decimal *result);     //
int s21_round(s21_decimal value, s21_decimal *result);     //
int s21_truncate(s21_decimal value, s21_decimal *result);  //
int s21_negate(s21_decimal value, s21_decimal *result);    //

// tools
int get_bit(unsigned int value, int bit_number);  // проверить бит по номеру
void set_bit(unsigned int *value, int bit_number,
             int set_value);  // установить значение бита
                              // set_value 0 или 1
int get_sign(
    s21_decimal value);  // 1 -- число отрицательное, 2 -- положительное
int get_exp(s21_decimal value);  // узнать степень десятки
int set_exp(s21_decimal *value, int exp);
void clear_decimal(s21_decimal *value);  // очистить децимал
int decimal_is_zero(
    s21_decimal value);  // проверить, является ли децимал нулевым
void s21_shift_left(s21_decimal *number);
void s21_shift_right(s21_decimal *number);
int s21_div_by_ten(s21_decimal value, s21_decimal *result);
int rem_div_by_ten(s21_decimal value);
void add_one(s21_decimal *value);

// для тестов
typedef union {
  int ui;
  float fl;
} floatbits;
// int s21_from_float_to_decimal(float src, s21_decimal *dst);
// int s21_from_decimal_to_float(s21_decimal src, float *dst);

#endif