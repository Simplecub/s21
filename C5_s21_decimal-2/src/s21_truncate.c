#include "s21_decimal.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
  int error = 0;
  if (result == NULL) {
    error = 1;
  } else {
    s21_decimal buf = {};
    int sign = get_sign(value), exp = get_exp(value);
    for (int i = 0; i < exp; i++) {
      s21_div_by_ten(value, &buf);
      value = buf;
      clear_decimal(&buf);
    }
    if (sign) set_bit(&value.bits[3], 31, 1);
    *result = value;
  }
  return error;
}

int s21_div_by_ten(s21_decimal value, s21_decimal *result) {
  int order = 0, rem = 0;
  unsigned long buf = 0;

  for (int i = 0; i < 3; i++)  // определяем с какими битами работать
    if (value.bits[i]) order = i;

  buf = value.bits[order];
  while (order >= 0) {
    rem = buf % 10;
    result->bits[order] = buf / 10;
    buf = rem * (MAX_UINT + 1) + value.bits[order - 1];
    order--;
  }
  return 0;
}