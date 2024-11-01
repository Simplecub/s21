#include "s21_string.h"

s21_size_t s21_strlen(const char *str);
s21_size_t s21_strcspn(const char *str1, const char *str2);
char *s21_strchr(const char *str, int c);
char *s21_strtok(char *str, const char *div);
char *s21_strpbrk(const char *str1, const char *str2);
int s21_strncmp(const char *str1, const char *str2, s21_size_t n);
char *s21_strncpy(char *destination, const char *source, s21_size_t n);
char *s21_strncat(char *dest, const char *src, s21_size_t n);
char *s21_strrchr(const char *str, int c);
char *s21_strstr(const char *haystack, const char *needle);

void *s21_memchr(const void *str, int c, s21_size_t n);
int s21_memcmp(const void *str1, const void *str2, s21_size_t n);
void *s21_memset(void *str, int c, s21_size_t n);
char *s21_strerror(int errnum);
void *s21_memcpy(void *dest, const void *src, s21_size_t n);

int s21_sprintf(char *str, const char *format, ...);

//....
void *s21_to_upper(const char *str);
void *s21_to_lower(const char *str);
void *s21_insert(const char *src, const char *str, s21_size_t start_index);
void *s21_trim(const char *src, const char *trim_chars);

//...