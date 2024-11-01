#include "s21_string.h"

char *s21_strstr(const char *haystack, const char *needle) {
  const char *flag = s21_NULL;
  int length_main = s21_strlen(haystack);
  int length_sub = s21_strlen(needle);
  if (*needle == '\0') {
    flag = haystack;
  }

  if (length_sub <= length_main && *needle != '\0') {
    for (int i = 0; i <= length_main - length_sub; i++) {
      int j;
      for (j = 0; needle[j] != '\0'; j++) {
        if (haystack[i + j] != needle[j]) {
          break;
        }
      }
      if (needle[j] == '\0') {
        flag = haystack + i;
        break;
      }
    }
  }
  return (char *)flag;
}
