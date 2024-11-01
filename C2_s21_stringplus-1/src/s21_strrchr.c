#include "s21_string.h"

char *s21_strrchr(const char *str, int c) {
  char *flag = s21_NULL;
  size_t length = s21_strlen(str);

  for (int i = length; i >= 0; i--) {
    if (str[i] == c) {
      flag = (char *)&str[i];
      break;
    }
  }
  return flag;
}
