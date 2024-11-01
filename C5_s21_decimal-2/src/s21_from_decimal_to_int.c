#include "s21_decimal.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int code = 0;
  if (src.bits[1] > 0 || src.bits[2] > 0 || src.bits[0] > 2147483647) {
    code = 1;
  }
  int a;
  if (src.bits[3] & 0b10000000000000000000000000000000) {
    a = -1;
  } else {
    a = 1;
  }
  a = a * (src.bits[0] / pow(10, get_exp(src)));
  *dst = a;
  return code;
}
