#include "s21_decimal.h"

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int code = 0, pov_who = 0, sign;
  if (!dst || fabs(src) > 79228162514264337593543950335.0) {
    code = 1;
  }
  if (src < 0) {
    sign = -1;
  } else {
    sign = 1;
  }
  dst->bits[0] = 0;
  dst->bits[1] = 0;
  dst->bits[2] = 0;
  dst->bits[3] = 0;
  src = fabs(src);
  float whole_part, fraction_part, *pwhole = &whole_part;
  fraction_part = modff(src, pwhole);
  long double whole = (long double)whole_part;
  for (; (long double)whole_part >= 1; pov_who++) {
    whole_part = (long double)whole_part / 10;
  }
  // for (;(int)fraction_part%10==0;pov_fra++){fraction_part /= 10;}
  // if (pov_who<7){fraction_part *= pow(10,min(7-pov_who,pov_fra));}
  // else{pov_who = 0;}
  // src = fabs(whole_part)*pow(10,pov_who)+fraction_part;
  long double result = whole * pow(10, 6) + fraction_part * pow(10, 6);
  for (int i = 95; i >= 64; i--) {
    if (result / pow(2, i) >= 1) {
      dst->bits[2] = (dst->bits[2] | (0b00000000000000000000000000000001 << i));
      result -= pow(2, i);
    }
  }
  for (int i = 63; i >= 32; i--) {
    if (result / pow(2, i) >= 1) {
      dst->bits[1] = (dst->bits[1] | (0b00000000000000000000000000000001 << i));
      result -= pow(2, i);
    }
  }
  for (int i = 31; i >= 0; i--) {
    if (result / pow(2, i) >= 1) {
      dst->bits[0] = (dst->bits[0] | (0b00000000000000000000000000000001 << i));
      result -= pow(2, i);
    }
  }
  if (sign == 1) {
    dst->bits[3] = 0b00000000000001100000000000000000;
  } else {
    dst->bits[3] = 0b10000000000001100000000000000000;
  }
  return code;
}
