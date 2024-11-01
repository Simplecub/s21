#include "s21_string.h"

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  s21_size_t c = n;
  if (src != s21_NULL) {
    s21_size_t i;
    for (i = 0; n > 0 && src[i] != '\0'; i++, n--) {
      dest[i] = src[i];
    }
    if (i < c) {
      dest[i] = '\0';
    }
  } else {
    dest = s21_NULL;
  }
  return dest;
}
