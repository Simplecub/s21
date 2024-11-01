#include <stdio.h>

#include "s21_decimal.h"

/*возвращает значение бита по заданному номеру (отсчет с нуля). также подходит
 * для проверки на нулевой бит*/
int get_bit(unsigned int value, int bit_number) {
  return value & (1 << bit_number);
}

/* ставит значение 1 или 0 в позиции bit_number числа. возможно, лучше будет
 * разбить на отдельные функции*/
void set_bit(unsigned int *value, int bit_number, int set_value) {
  if (set_value) {
    *value |= (1 << bit_number);
  } else {
    *value = *value & ~(1 << bit_number);
  }
}

/* здесь должна была быть функция, которая определяет индекс массива bits --
 * децимала -- чтобы понять, какое именно значение передавать. но потом я понял,
 * что ее заменяет банальное i/32*/

/*сдвигает все двоичное число влево. нужно для умножеия*/

/*void s21_shift_left(s21_decimal *number) {
  int prev_bit = 0, current_bit = 0;
  for (int i = 0; i <= 2; i++) {
    for (int j = 0; j <= 31; j++) {
      current_bit = get_bit(number->bits[i], j);
      if (prev_bit) {
        set_bit(&number->bits[i], j, 1);
      } else {
        set_bit(&number->bits[i], j, 0);
      }
      prev_bit = current_bit;
    }
  }
}

void s21_shift_right(s21_decimal *number) {
  int next_bit = 0, current_bit = 0;
  for (int i = 2; i >= 0; i--) {
    for (int j = 31; j >= 0; j--) {
      current_bit = get_bit(number->bits[i], j);
      if (next_bit) {
        set_bit(&number->bits[i], j, 1);
      } else {
        set_bit(&number->bits[i], j, 0);
      }
      next_bit = current_bit;
    }
  }
} */

int get_sign(s21_decimal value) {
  int sign = -1;
  if (get_bit(value.bits[3], 31))
    sign = 1;
  else
    sign = 0;
  return sign;
}

int get_exp(s21_decimal value) {
  unsigned int mask = 0b11111111 << 16;
  return (mask & value.bits[3]) >> 16;
}

void clear_decimal(s21_decimal *value) {  // опустошает децимал
  value->bits[0] = 0;
  value->bits[1] = 0;
  value->bits[2] = 0;
  value->bits[3] = 0;
}
int decimal_is_zero(
    s21_decimal value) {  // проверяет на равенство децимала нулю
  int is_zero = 1;
  if (value.bits[3] || value.bits[2] || value.bits[1] || value.bits[0])
    is_zero = 0;
  return is_zero;
}

int set_exp(s21_decimal *value, int exp) {
  int is_signed = 0;
  if (get_sign(*value)) is_signed = 1;
  unsigned int mask = 0b00000000 << 16;
  int error = 0;
  if (exp < 0 || exp > 28) {
    error = 1;
  } else {
    value->bits[3] &= mask;
    mask = mask >> 16;

    for (int i = 0; i < 8; i++)
      if (exp & (1 << i)) set_bit(&mask, i, 1);

    mask = mask << 16;
    value->bits[3] |= mask;
    if (is_signed) set_bit(&value->bits[3], 31, 1);
  }
  return error;
}

// стащил с гх, чтобы работали тесты
/*
int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  clear_decimal(dst);
  int return_value = 0;
  if (isinf(src) || isnan(src)) {
    return_value = 1;
  } else {
    if (src != 0) {
      int sign = *(int *)&src >> 31;
      int exp = ((*(int *)&src & ~0x80000000) >> 23) - 127;
      double temp = (double)fabs(src);
      int off = 0;
      for (; off < 28 && (int)temp / (int)pow(2, 21) == 0; temp *= 10, off++) {
      }
      temp = round(temp);
      if (off <= 28 && (exp > -94 && exp < 96)) {
        floatbits mant = {0};
        temp = (float)temp;
        for (; fmod(temp, 10) == 0 && off > 0; off--, temp /= 10) {
        }
        mant.fl = temp;
        exp = ((*(int *)&mant.fl & ~0x80000000) >> 23) - 127;
        dst->bits[exp / 32] |= 1 << exp % 32;
        for (int i = exp - 1, j = 22; j >= 0; i--, j--)
          if ((mant.ui & (1 << j)) != 0) dst->bits[i / 32] |= 1 << i % 32;
        dst->bits[3] = (sign << 31) | (off << 16);
      }
    }
  }
  return return_value;
}

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  double result = 0;
  int off = 0;
  for (int i = 0; i < 96; i++) {
    if ((src.bits[i / 32] & (1 << i % 32)) != 0) {
      result += pow(2, i);
    }
  }
  if ((off = (src.bits[3] & ~0x80000000) >> 16) > 0) {
    for (int i = off; i > 0; i--) {
      result /= 10.0;
    }
  }
  *dst = (float)result;
  *dst *= src.bits[3] >> 31 ? -1 : 1;
  return 0;
}
*/