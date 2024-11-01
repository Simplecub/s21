#ifndef TEST_SUITCASES_H
#define TEST_SUITCASES_H

#define LONG_MAX 2147483647L
#define LONG_MIN -214748364L
#define SHRT_MAX 32767
#define SHRT_MIN -32767
#define INT_MAX 2147483647
#define INT_MIN -INT_MAX - 1
#define ULONG_MAX 0xFFFFFFFFUL

#include <check.h>

#include "s21_string.h"

Suite *test_strlen(void);
Suite *test_strcspn(void);
Suite *test_strchr(void);
Suite *test_strtok(void);
Suite *test_strpbrk(void);
Suite *test_strncmp(void);
Suite *test_strncpy(void);
Suite *test_strncat(void);
Suite *test_strrchr(void);
Suite *test_strstr(void);
Suite *test_memchr(void);
Suite *test_memcmp(void);
Suite *test_memset(void);
Suite *test_strerror(void);
Suite *test_memcpy(void);

Suite *test_sprintf_signed(void);
Suite *test_sprintf_c(void);
Suite *test_sprintf_e(void);
Suite *test_sprintf_f(void);
Suite *test_sprintf_g(void);
Suite *test_sprintf_hex(void);
Suite *test_sprintf_HEX(void);
Suite *test_sprintf_signed_i(void);
Suite *test_sprintf_n(void);
Suite *test_sprintf_octal(void);
Suite *test_sprintf_percent(void);
Suite *test_sprintf_pointer(void);
Suite *test_sprintf_string(void);
Suite *test_sprintf_unsigned(void);

Suite *test_to_upper(void);
Suite *test_to_lower(void);
Suite *test_insert(void);
Suite *test_trim(void);

void run_tests(void);
void run_testcase(Suite *testcase);

#endif