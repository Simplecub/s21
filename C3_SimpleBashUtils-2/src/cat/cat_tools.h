#ifndef CAT_TOOLS_H
#define CAT_TOOLS_H

typedef struct {
  int b;
  int e;
  int n;
  int s;
  int t;
  int v;
} Flags;

Flags parser_flags(int argc, char *argv[]);
void print_file(char *name, Flags flags);

#endif