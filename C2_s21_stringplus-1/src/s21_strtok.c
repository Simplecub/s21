#include "s21_string.h"

char *s21_strtok(char *str, const char *div) {
  static char *next_token = s21_NULL;
  char *token_start = s21_NULL;
  static char *prev_token = s21_NULL;
  if (str != s21_NULL) {
    next_token = str;
    prev_token = s21_NULL;
  }
  if (next_token == NULL || *next_token == '\0') {
    return NULL;
  }
  if (next_token != s21_NULL && *next_token != '\0') {
    token_start = next_token;
    while (*token_start && s21_strchr(div, *token_start) != s21_NULL) {
      token_start++;
    }
    if (*token_start != '\0') {
      prev_token = token_start;
      next_token = s21_strpbrk(token_start, div);
      if (next_token != s21_NULL) {
        *next_token = '\0';
        next_token++;
      }
    } else
      next_token = s21_NULL;
  }
  return prev_token;
}
