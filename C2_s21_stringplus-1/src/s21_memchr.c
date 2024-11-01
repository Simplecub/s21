#include "s21_string.h"

void *s21_memchr(const void *str, int c, s21_size_t n) {
  s21_size_t i;
  char *result = s21_NULL;
  for (i = 0; i < n; i++) {
    if (*((char *)str + i) == c) {
      result = (char *)str + i;
      break;
    }
  }
  return result;
}