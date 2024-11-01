#include "s21_string.h"

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  int dif = 0;
  if (n > 0) {
    while (--n > 1 && *str1 && *str1 == *str2) {
      ++str1;
      ++str2;
    }
    dif = *str1 - *str2;
  }
  return dif;
}
