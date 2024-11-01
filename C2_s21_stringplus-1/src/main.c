#include "test_suitcases.h"

int main(void) {
  run_tests();
  return 0;
}

void run_tests(void) {
  Suite *list_cases[] = {
      test_strlen(), test_strcspn(), test_strchr(), test_strtok(),
      test_strpbrk(), test_strncmp(), test_strncpy(), test_strncat(),
      test_strrchr(), test_strstr(), test_memchr(), test_memcmp(),
      test_memset(), test_strerror(), test_memcpy(),

      test_sprintf_signed(), test_sprintf_c(), test_sprintf_e(),
      test_sprintf_f(), test_sprintf_g(), test_sprintf_hex(),
      test_sprintf_HEX(), test_sprintf_signed_i(), test_sprintf_n(),
      test_sprintf_octal(), test_sprintf_percent(), test_sprintf_pointer(),
      test_sprintf_string(), test_sprintf_unsigned(),

      test_to_upper(), test_to_lower(), test_insert(), test_trim(),

      // tests...

      NULL};

  for (Suite **current_testcase = list_cases; *current_testcase != NULL;
       current_testcase++) {
    run_testcase(*current_testcase);
  }
}

void run_testcase(Suite *testcase) {
  int failed = 0;
  Suite *s = testcase;  // из test_root.c - Suite *test_root(void)
  SRunner *runner = srunner_create(s);
  srunner_run_all(runner, CK_NORMAL);

  failed = srunner_ntests_failed(runner);
  srunner_free(runner);

  printf("========= FAILED: %d =========\n", failed);
}