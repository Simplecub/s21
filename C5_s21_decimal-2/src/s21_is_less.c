#include "s21_decimal.h"

int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
  int result = 0, over = 0, scale_1 = GETSCALE(value_1),
      scale_2 = GETSCALE(value_2);
  if (!s21_is_equal(value_1, value_2)) {  // если не равны
    //первое отрицательное, второе положительное v1 < v2 -верно
    if (CHECKMINUS(value_1) && !CHECKMINUS(value_2)) {
      result = 1;
    }  //первое положительное, второе отрицательное v1 > v2
    else if (!CHECKMINUS(value_1) && CHECKMINUS(value_2)) {
      result = 0;
    }  //оба положительные вычитание v2-v1);
    else if (!CHECKMINUS(value_1) && !CHECKMINUS(value_2)) {
      if (scale_1 > scale_2) {
        //если вернулось переполнение то число 2 больше
        over = s21_align_10(&value_2, scale_1 - scale_2);
        result = over ? 1 : 0;
      } else if (scale_2 > scale_1) {
        //если вернулось переполнение то число 1 больше
        over = s21_align_10(&value_1, scale_2 - scale_1);
        result = over ? 0 : 1;
      }
      if (!over) {
        s21_decimal diff_num = {0};
        s21_diff(value_1, value_2, &diff_num);
        //если разность v1-v2 отрицательная v1<v2=true res = 1
        result = diff_num.bits[3] & MINUS ? 1 : 0;
      }
    }  //оба отрицательные //result !вычитание v2-v1
    else if (CHECKMINUS(value_1) && CHECKMINUS(value_2)) {
      if (scale_1 > scale_2) {
        //если вернулось переполнение то число 2 больше
        over = s21_align_10(&value_2, scale_1 - scale_2);
        result = over ? 0 : 1;
      } else if (scale_2 > scale_1) {
        //если вернулось переполнение то число 1 больше
        over = s21_align_10(&value_1, scale_2 - scale_1);
        result = over ? 1 : 0;
      }
      if (!over) {
        s21_decimal diff_num = {0};
        s21_diff(value_1, value_2, &diff_num);
        //если разность v1-v2 отрицательная v1>v2=true res = 1
        result = diff_num.bits[3] & MINUS ? 0 : 1;
      }
    }
  } else {
    result = 0;
  }
  return result;
}
