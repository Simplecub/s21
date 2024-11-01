#include "./test.h"

int main() {
  int number_filed = 0;
  number_filed = run_test_back();

  return (number_filed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
