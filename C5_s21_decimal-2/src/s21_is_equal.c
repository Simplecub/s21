
#include "s21_decimal.h"

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  int result = 0, scale_1 = GETSCALE(value_1), scale_2 = GETSCALE(value_2);
  //проверка что числа одного знака
  if ((value_1.bits[3] & MINUS) >> 31 == (value_2.bits[3] & MINUS) >> 31) {
    //проверка одинаковые степени или нет
    if (scale_1 == scale_2) {
      //проверка что старшие инты равны
      if (value_1.bits[2] == value_2.bits[2]) {
        //проверка что средние инты равны
        if (value_1.bits[1] == value_2.bits[1]) {
          result = value_1.bits[0] == value_2.bits[0] ? 1 : 0;
        } else {
          result = 0;
        }
      } else {
        result = 0;
      }
    }
    //если степени не равны то приведение к одинаковым степеням
    else {
      if (scale_1 > scale_2) {
        // value_2 = //value_2 *10(scale_1-scale_2 - раз)
        //если вернулось переполнение то числа не равны
        result = s21_align_10(&value_2, scale_1 - scale_2) ? 0 : 1;
      } else if (scale_2 > scale_1) {
        // value_1 = //value_1 *10(scale_2-scale_1 - раз)
        //если вернулось переполнение то числа не равны
        result = s21_align_10(&value_1, scale_2 - scale_1) ? 0 : 1;
      }
      if (value_1.bits[3] == value_2.bits[3]) {
        if (value_1.bits[2] == value_2.bits[2]) {
          if (value_1.bits[1] == value_2.bits[1]) {
            result = value_1.bits[0] == value_2.bits[0] ? 1 : 0;
          } else {
            result = 0;
          }
        } else {
          result = 0;
        }
      } else {
        result = 0;
      }
    }
  } else {
    result = 0;
  }
  return result;
}
