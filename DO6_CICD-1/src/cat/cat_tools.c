#include "cat_tools.h"

#include <getopt.h>
#include <stdio.h>

Flags parser_flags(int argc, char *argv[]) {
  struct option longOptions[] = {

      {"number-nonblank", 0, NULL, 'b'},
      {"number", 0, NULL, 'n'},
      {"squeeze-blank", 0, NULL, 's'},
      {NULL, 0, NULL, 0}

  };
  int currentFlag = getopt_long(argc, argv, "bevntsET", longOptions, NULL);

  Flags flags = {0, 0, 0, 0, 0, 0};
  for (; currentFlag != -1;
       currentFlag = getopt_long(argc, argv, "bevntsET", longOptions, NULL)) {
    switch (currentFlag) {
      case 'b':
        flags.b = 1;
        break;
      case 'e':
        flags.e = 1;
        flags.v = 1;
        break;
      case 'n':
        flags.n = 1;
        break;
      case 's':
        flags.s = 1;
        break;
      case 'E':
        flags.e = 1;
        break;
      case 't':
        flags.v = 1;
        flags.t = 1;
        break;
      case 'T':
        flags.t = 1;
        break;
      case 'v':
        flags.v = 1;
        break;
    }
  }

  if (flags.b == 1) {
    flags.n = 0;
  }

  return flags;
}

void print_file(char *name, Flags flags) {
  FILE *file = fopen(name, "rt");

  if (file != NULL) {
    int c, line_number = 1, prev = '\n', is_blank = -1;

    while ((c = fgetc(file)) != EOF) {
      if (flags.s && c == '\n' && prev == '\n') {
        is_blank++;

        if (is_blank > 0) {
          continue;
        }
      } else {
        is_blank = -1;
      }

      if (flags.n && prev == '\n') printf("%6d\t", line_number++);

      if (flags.b && prev == '\n' && c != '\n') printf("%6d\t", line_number++);

      if (flags.e && c == '\n') {
        printf("$");
      }
      if (flags.t && c == '\t') {
        printf("^");
        c = '\t' + 64;
      }

      if (flags.v &&
          (((c >= 0 && c < 9) || (c > 10 && c < 32)) || (c == 127))) {
        if (c == 127) {
          c -= 64;
        } else {
          c += 64;
        }
        printf("^");
      }
      putchar(c);
      prev = c;
    }
    fclose(file);
  } else {
    fprintf(stderr, "cat: %s: No such file or directory\n", name);
  }
}