#include "s21_decimal.h"
int s21_floor(s21_decimal value, s21_decimal *result) {
  int error = 0;
  if (result == NULL) {
    error = 1;
  } else {
    s21_decimal buf = {{}};
    s21_truncate(value, &buf);

    if (get_sign(value) && !s21_is_equal(value, buf)) {
      set_bit(&buf.bits[3], 31, 0);
      add_one(&buf);
      set_bit(&buf.bits[3], 31, 1);
    }
    *result = buf;
  }
  return error;
}