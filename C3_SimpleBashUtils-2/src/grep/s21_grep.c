#include "s21_grep.h"

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
  Flag flag = parser_flags(argc, argv);

  for (; optind < argc; optind++) output(argv, flag);
}

Flag parser_flags(int argc, char *argv[]) {
  int currentFlag = 0;
  Flag flag = {};
  while ((currentFlag = getopt_long(argc, argv, "e:ivclnhsf:o", NULL, NULL)) !=
         -1) {
    switch (currentFlag) {
      case 'e':
        flag.e = 1;
        strcat(flag.args, optarg);
        strcat(flag.args, "|");
        break;
      case 'i':
        flag.i = 1;
        break;
      case 'v':
        flag.v = 1;
        break;
      case 'c':
        flag.c = 1;
        break;
      case 'l':
        flag.l = 1;
        break;
      case 'n':
        flag.n = 1;
        break;
      case 'f':
        handle_flagF(&flag);
        flag.f = 1;
        break;
      case 'h':
        flag.h = 1;
        break;
      case 's':
        flag.s = 1;
        break;
      case 'o':
        flag.o = 1;
        break;
    }
  }
  processing_flags_in_reader(&flag, argc, argv);
  return flag;
}

void output(char *argv[], Flag flag) {
  FILE *file;
  regex_t reg;
  int line_number = 1, line_match = 0, file_match = 0, flag_i = REG_EXTENDED;
  if (flag.i) flag_i = REG_EXTENDED | REG_ICASE;
  file = fopen(argv[optind], "rt");
  if (file != NULL) {
    if (!regcomp(&reg, flag.args, flag_i)) {
      while (fgets(flag.buffer, SIZE, file) != NULL) {
        if (flag.o) {
          handle_flagO(flag, reg, line_number, argv);
          line_number++;
          continue;
        }
        handle_match(flag, reg, line_number, &line_match, &file_match, argv);
        line_number++;
      }
      handle_easy_flags(&flag, &file_match, &line_match, argv);
      regfree(&reg);
    }
    fclose(file);
  } else if (!flag.s) {
    fprintf(stderr, "grep: %s: No such file or directory\n", argv[optind]);
  }
}

void handle_flagF(Flag *flag) {
  char f_buffer[SIZE];
  FILE *pattern;
  pattern = fopen(optarg, "rt");
  if (pattern != NULL) {
    while (fgets(f_buffer, SIZE, pattern) != NULL) {
      f_buffer[strcspn(f_buffer, "\n")] = '\0';
      if (strlen(f_buffer) == 0) strcat(f_buffer, ".");

      strcat(flag->args, f_buffer);
      strcat(flag->args, "|");
    }

    fclose(pattern);
  } else if (!flag->s) {
    fprintf(stderr, "grep: %s: No such file or directory\n", optarg);
  }
}

void processing_flags_in_reader(Flag *flag, int argc, char *argv[]) {
  if (!flag->e && !flag->f) {
    if (argc > optind) {
      strcat(flag->args, argv[optind]);
    }
    optind++;
  }
  if ((argc > optind + 1) && !flag->h) flag->print_filename = 1;

  if (flag->e || flag->f) flag->args[strlen(flag->args) - 1] = '\0';

  if (flag->c || flag->l || flag->v) flag->o = 0;
}

void handle_flagO(Flag flag, regex_t reg, int line_number, char *argv[]) {
  regmatch_t regmat[1];
  char *ptr = flag.buffer;
  while (regexec(&reg, ptr, 1, regmat, 0) != REG_NOMATCH) {
    if (flag.print_filename) printf("%s:", argv[optind]);
    if (flag.n) printf("%d:", line_number);
    for (int i = regmat[0].rm_so; i < regmat[0].rm_eo; i++) {
      putchar(ptr[i]);
    }
    ptr += regmat[0].rm_eo;
    printf("\n");
  }
}

void handle_easy_flags(Flag *flag, int *file_match, int *line_match,
                       char *argv[]) {
  if (flag->c) {
    if (flag->print_filename) printf("%s:", argv[optind]);
    if (flag->l && *line_match) *line_match = 1;
    printf("%d\n", *line_match);
  }
  if (flag->l && *file_match) printf("%s\n", argv[optind]);
}

void handle_match(Flag flag, regex_t reg, int line_number, int *line_match,
                  int *file_match, char *argv[]) {
  regmatch_t regmat[1];
  int match = regexec(&reg, flag.buffer, 1, regmat, 0);  // *
  if (flag.v) match = !match;
  if (!match) {
    if (!flag.c && !flag.l && !flag.o) {
      if (flag.print_filename) printf("%s:", argv[optind]);

      if (flag.n) printf("%d:", line_number);
      if (strchr(flag.buffer, '\n') == NULL) strcat(flag.buffer, "\n");
      printf("%s", flag.buffer);
    }
    *file_match = 1;
    (*line_match)++;
  }
}
