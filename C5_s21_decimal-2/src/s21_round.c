#include "s21_decimal.h"

int s21_round(s21_decimal value, s21_decimal *result) {
  int error = 0, is_signed = 0;
  s21_decimal buf = {{}}, copy_value = value;
  if (result == NULL) {
    error = 1;
  } else {
    for (int i = 0; i < get_exp(value) - 1; i++) {
      s21_div_by_ten(copy_value, &buf);
      copy_value = buf;
      clear_decimal(&buf);
    }
    if (get_sign(value)) {
      set_bit(&value.bits[3], 31, 0);
      is_signed = 1;
    }
    if (rem_div_by_ten(copy_value) < 5) {
      s21_floor(value, &buf);
    } else {
      s21_truncate(value, &buf);
      if (get_exp(value)) add_one(&buf);
    }
    *result = buf;
    if (is_signed) set_bit(&result->bits[3], 31, 1);
    if (!result->bits[0] && !result->bits[1] && !result->bits[2])
      result->bits[3] = 0;
  }
  return error;
}

int rem_div_by_ten(s21_decimal value) {
  int order = 0, rem = 0;
  unsigned long buf = 0;

  for (int i = 0; i < 3; i++)  // определяем с какими битами работать
    if (value.bits[i]) order = i;

  buf = value.bits[order];
  while (order >= 0) {
    rem = buf % 10;
    buf = rem * (MAX_UINT + 1) + value.bits[order - 1];
    order--;
  }
  return rem;
}

void add_one(s21_decimal *value) {  // нужно будет заменить на обычное сложение
  s21_decimal one = {{1}};

  s21_sum(value, one);
}