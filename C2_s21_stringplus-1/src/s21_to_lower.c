#include "s21_string.h"

void* s21_to_lower(const char* str) {
  s21_size_t size = s21_strlen(str);
  char* fin = (char*)calloc(size + 1, sizeof(char));
  if (fin != s21_NULL) {
    for (s21_size_t i = 0; str[i] != 0; i++) {
      if (str[i] >= 'A' && str[i] <= 'Z') {
        fin[i] = str[i] + 32;
      } else {
        fin[i] = str[i];
      }
    }
  }
  return fin;
}
