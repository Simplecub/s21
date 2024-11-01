#include <getopt.h>

#include "cat_tools.h"

int main(int argc, char *argv[]) {
  Flags flags = parser_flags(argc, argv);

  for (int i = optind; i < argc; i++) {
    print_file(argv[i], flags);
  }

  return 0;
}