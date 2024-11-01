#ifndef SRC_S21_SPRINTF_H_
#define SRC_S21_SPRINTF_H_
#include <math.h>
#include <stdarg.h>

#include "s21_string.h"

int s21_sprintf(char *str, const char *format,
                ...);  // - отправляет форматированный вывод в строку, на
                       // которую указывает str.
typedef struct {
  int plus;   // знак
  int minus;  // прижать к  левому краю
  int space;  // добавить символ под знак
  int hash;   // разрядность 16->0х, 8->0
  int zero;   // заполнить 0 вместо space
  int width;
  int accuracy;
  char length;        // тип переменной
  int number_system;  // система счисления
  int add_size;       // если + " " -
  int dot;            // если . значить будет точность
  int upper_case;     // строчный спецификатор
  int g;              // в кратком написании
  int e;              // в научнай нотации
  int accuracy_dot_isnull;  // если точность 0
} Flag;

typedef struct {
  int negative;
  int to_dot;
  int to_plus;
  int count;
  int i;
  int f;
  int is_space;
  int is_int;
  int is_frac;
  int format_L;
  int e;
  int count_exp;
  int inf_nan;
} Float;

const char *add_flags(Flag *flags, const char *format, va_list *args);  //
const char *get_flags(Flag *flags, const char *format);
const char *get_width(int *width, const char *format, va_list *args);
char *parser(Flag flags, const char *format, char *str, char *start_str,
             va_list *args);
char get_num_to_chr(int number, int upper_case);
char *output_di(Flag flags, char *str, va_list *args);

Flag set_num_system(Flag flags, char format);
char *output_uoxX(char *str, Flag flags, char format, va_list *args);

char *output_c(char *str, Flag flags, int c);
char *output_s(char *str, Flag flags, va_list *args);
char *output_p(char *str, Flag *flags, va_list *args, char format);

//
char *copy_reversed_dig(char *str, const char *buffer, int size);
void fill_buffer(char *buffer, int *i, long int dig, Flag flags);
char *proc_di_flag_minus(char *str, Flag *flags, const char *buffer, int count,
                         int flag_negative);
char *proc_di(char *str, Flag *flags, const char *buffer, int count,
              int flag_negative);
char *proc_uoxX_flag_hash(char *str, Flag flags, int number);
char *proc_uoxX_flag_minus(char *str, char *buffer, Flag flags, int count);
char *proc_uoxX(char *str, char *buffer, Flag flags, int count, int number);

void divide_float(long double *number, long double *integer, long double *frac,
                  Float *floats, Flag *flags);
void round_float(long double *frac, long double *integer, Float *floats,
                 Flag flags);
void set_param_f(Flag *flags, Float *floats);
char *proc_f(char *str, Flag flags, Float *floats, const char *buffer_int,
             const char *buffer_frac, const char *buffer_e);
char *proc_f_flag_minus(char *str, Flag flags, Float *floats,
                        const char *buffer_int, const char *buffer_frac,
                        const char *buffer_e);

void proc_g(long double *number, Flag *flags, Float *floats);

char *add_sign(char *str, char c);

Flag set_flags_eEfFgG(Flag flags, char format);
char *output_fF(char *str, Flag flags, char format, va_list *args);

int inf_or_nan(char *buffer, long double num, Flag flags, Float *floats);

Flag set_flags_eEfFgG(Flag flags, char format);
/// eE
long double normalize_e(long double *num, Flag *flags);
int output_e(int e, s21_size_t *size_buffer, char *buffer, Flag flags, int *i);
s21_size_t add_sum_to_str(char *buffer, int *i, int c);

#endif