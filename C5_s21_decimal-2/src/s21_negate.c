#include "s21_decimal.h"
int s21_negate(s21_decimal value, s21_decimal *result) {
  int error = 0;
  if (result == NULL) {
    error = 1;
  } else if (decimal_is_zero(value)) {
    *result = value;
  } else {
    if (get_sign(value)) {
      set_bit(&value.bits[3], 31, 0);
    } else {
      set_bit(&value.bits[3], 31, 1);
    }
    *result = value;
  }
  return error;
}