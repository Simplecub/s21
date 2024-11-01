#include "s21_decimal.h"

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int sign, code = 0;
  double a = 0;
  if (src.bits[3] & 0b10000000000000000000000000000000) {
    sign = -1;
  } else {
    sign = 1;
  }
  a += src.bits[0];
  for (int i = 0; i < 32; i++) {
    if ((src.bits[1] & (0b00000000000000000000000000000001 << i)) ==
        (unsigned int)(0b00000000000000000000000000000001 << i)) {
      a += pow(2, 32 + i);
    }
    if ((src.bits[2] & (0b00000000000000000000000000000001 << i)) ==
        (unsigned int)(0b00000000000000000000000000000001 << i)) {
      a += pow(2, 64 + i);
    }
  }
  if (sign == -1) {
    a /= pow(10, (src.bits[3] >> 16) - pow(2, 15));
  } else {
    a = a / pow(10, src.bits[3] >> 16);
  }
  a *= sign;
  *dst = (float)a;
  return code;
}
