#ifndef S21_GREP_H
#include <regex.h>
#define S21_GREP_H

#define SIZE 10000

typedef struct {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int f;
  int h;
  int s;
  int o;
  int print_filename;
  char args[SIZE];
  char buffer[SIZE];
} Flag;

Flag parser_flags(int argc, char *argv[]);
void output(char *argv[], Flag flag);
void handle_flagF(Flag *flag);
void processing_flags_in_reader(Flag *flag, int argc, char *argv[]);
void handle_flagO(Flag flag, regex_t reg, int line_number, char *argv[]);
void handle_easy_flags(Flag *flag, int *file_match, int *line_match,
                       char *argv[]);
void handle_match(Flag flag, regex_t reg, int line_number, int *line_match,
                  int *file_match, char *argv[]);

#endif