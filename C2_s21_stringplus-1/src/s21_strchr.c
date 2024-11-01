#include "s21_string.h"

char *s21_strchr(const char *str, int c) {
  char *flag = s21_NULL;
  if (c != '\0') {
    for (; *str && *str != c; str++)
      ;
    if (*str != '\0') {
      flag = (char *)str;
    }
  } else {
    flag = "\0";
  }
  return flag;
}
