#include "s21_decimal.h"

//приведени к  степени scale (умножение на 10 scale раз)
//возвращает 1 если переполнение
int s21_align_10(s21_decimal *value, int scale) {
  int set_scale = (value->bits[3] & SC) >> 16, check_max = 0;
  s21_decimal result = {0};
  while (!check_max && scale) {
    if (!s21_shift(value)) {
      result = *value;
      check_max = s21_shift(value) ? 1 : s21_shift(value);
      if (!check_max) {
        check_max = s21_sum(value, result);
        set_scale++;
        result.bits[3] &= MINUS;  //зануляет все биты кроме крайнего
        result.bits[3] |= (set_scale << 16) & SC;  //записываем scale
      }
    } else {
      check_max = 1;
    }
    scale--;
  }
  value->bits[3] = result.bits[3];
  return check_max;
}

//сдвиг влево всех интов один раз и возвращение переполнения если оно есть
int s21_shift(s21_decimal *value) {
  int over_step = 0;
  int before_step = 0;
  for (int i = 0; i < 3; i++) {
    over_step = (value->bits[i] >> 31) & 0b1;
    value->bits[i] = value->bits[i] << 1;
    value->bits[i] = value->bits[i] | before_step;
    before_step = over_step;
  }
  return before_step;
}

// сложение только мантисс, возвращает переполнение буфера, если есть
int s21_sum(s21_decimal *dst, s21_decimal src) {
  s21_decimal result = {0};
  int s = 0, c = 0, count = 0;
  int check_max = 0;
  for (int j = 0; j < 3; j++) {
    result.bits[j] = 0;
    for (int i = 0; i < 32; i++) {
      int v1 = (src.bits[j] >> i) & 1;
      int v2 = (dst->bits[j] >> i) & 1;
      // c = count ? 1 : c;
      if (c) {
        s = (v1 ^ v2) ^ c;
        c = (v1 & v2 & 1) | ((v1 ^ v2) & c);
      } else {
        s = (v1 ^ v2);
        c = v1 & v2 & 1;
      }
      result.bits[j] |= s << i;
      if ((i == 31) && c) {
        count = 1;
      }
      count = c;
    }
    dst->bits[j] = result.bits[j];
  }
  check_max = count;
  return check_max;
}

//из value_1 вычитает value_2
int s21_diff(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int over_step = 0;  //флаг минуса
  //второе число отрицательным чтобы потом его сложить с первым
  value_2.bits[3] |= MINUS;
  //первое положительным
  value_1.bits[3] &= ~MINUS;
  value_2.bits[0] = ~value_2.bits[0];
  value_2.bits[1] = ~value_2.bits[1];
  value_2.bits[2] = ~value_2.bits[2];
  s21_decimal res = value_1;
  over_step = s21_sum(&res, value_2);
  if (!over_step) {
    res.bits[3] |= MINUS;
  } else {
    s21_decimal one = {0};
    one.bits[0] = 1;
    s21_sum(&res, one);
  }
  result->bits[0] = over_step ? res.bits[0] : ~res.bits[0];
  result->bits[1] = over_step ? res.bits[1] : ~res.bits[1];
  result->bits[2] = over_step ? res.bits[2] : ~res.bits[2];
  result->bits[3] = res.bits[3];
  return 0;
}

/*

1010000
0010100
1100100*/
