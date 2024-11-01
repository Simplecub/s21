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

int s21_sprintf(char *str, const char *format, ...) {
  char *start_str = str;
  va_list args;
  va_start(args, format);
  char all_flags[] = "uiodxXcsnpfFeEgG%";

  while (*format) {
    if (*format == '%') {
      format++;
      Flag flags = {0};
      flags.number_system = 10;
      format = add_flags(&flags, format, &args);  //
      while (!s21_strchr(all_flags, *format)) format++;
      str = parser(flags, format, str, start_str, &args);

    } else {
      *str = *format;
      str++;
    }
    format++;
  }
  *str = '\0';
  va_end(args);

  return (str - start_str);
}

const char *add_flags(Flag *flags, const char *format, va_list *args) {  //
  format = get_flags(flags, format);
  format = get_width(&flags->width, format, args);
  if (flags->width < 0) {
    flags->width = -flags->width;
    flags->minus = 1;
  }

  if (*format == '.') {
    flags->dot = 1;
    format++;
    format = get_width(&flags->accuracy, format, args);
    if (flags->accuracy == 0) {
      flags->accuracy_dot_isnull = -1;
    }
  }
  if (*format == 'L')
    flags->length = 'L';
  else if (*format == 'l')
    flags->length = 'l';
  else if (*format == 'h')
    flags->length = 'h';
  if (flags->length != 0) format++;

  return format;
}

const char *get_flags(
    Flag *flags,
    const char *format) {  // считывание флагов после % до спецификатора

  while (*format) {
    if (*format == '+')
      flags->plus = 1;
    else if (*format == '-')
      flags->minus = 1;
    else if (*format == '#')
      flags->hash = 1;
    else if (*format == ' ')
      flags->space = 1;
    else if (*format == '0')
      flags->zero = 1;
    else
      break;
    format++;
  }
  flags->space =
      (flags->space && !flags->plus);  // ' ' flag ignored with '+' flag /если +
                                       // и " " то space->0
  flags->zero = (flags->zero && !flags->minus);  // '0' flag ignored with '-'
                                                 // flag /если - и 0 то zero ->0
  return format;
}

const char *get_width(int *width, const char *format, va_list *args) {
  *width = 0;
  if (*format == '*') {
    *width = va_arg(*args, int);
    format++;
  }
  while (*format) {
    if (*format >= '0' && *format <= '9') {
      *width *= 10;
      *width += *format - '0';
    } else {
      break;
    }
    format++;
  }

  return format;
}

char *parser(Flag flags, const char *format, char *str, char *start_str,
             va_list *args) {
  if (*format == 'd' || *format == 'i') {
    str = output_di(flags, str, args);

  } else if (*format == 'u' || *format == 'o' || *format == 'x' ||
             *format == 'X') {
    flags = set_num_system(flags, *format);

    str = output_uoxX(str, flags, *(format - 1), args);

  } else if (*format == 'c') {
    int c = va_arg(*args, int);
    str = output_c(str, flags, c);

  } else if (*format == 's') {
    str = output_s(str, flags, args);
  } else if (*format == 'p') {
    str = output_p(str, &flags, args, *(format - 1));
  } else if (*format == 'n') {
    int *n = va_arg(*args, int *);
    *n = (int)(str - start_str);
  } else if (*format == '%') {
    str = output_c(str, flags, '%');

  } else if (*format == 'f' || *format == 'F' || *format == 'e' ||
             *format == 'E' || *format == 'g' || *format == 'G') {
    flags = set_flags_eEfFgG(flags, *format);
    str = output_fF(str, flags, *(format - 1), args);
  } else {
    str = s21_NULL;
  }
  if (!str) {
    *start_str = '\0';
  }
  return str;
}

char get_num_to_chr(int number, int upper_case) {
  char res = '0';
  switch (number) {
    case 10:
      res = (char)('a' - upper_case * 32);
      break;
    case 11:
      res = (char)('b' - upper_case * 32);
      break;
    case 12:
      res = (char)('c' - upper_case * 32);
      break;
    case 13:
      res = (char)('d' - upper_case * 32);
      break;
    case 14:
      res = (char)('e' - upper_case * 32);
      break;
    case 15:
      res = (char)('f' - upper_case * 32);
      break;
    default:
      break;
  }
  if (number >= 0 && number <= 9) res = (char)(number + 48);
  return res;
}

char *output_di(Flag flags, char *str, va_list *args) {
  long long int number = 0;
  if (flags.length == 'h') {
    number = (short)va_arg(*args, int);
  } else if (flags.length == 'l') {
    number = (long int)va_arg(*args, long int);
  } else if (flags.length == 'L') {
    number = (long long int)va_arg(*args, long long int);
  } else {
    number = (int)va_arg(*args, int);
  }

  char buffer[sizeof(long long int) * 8] = "0";
  int i = 0, flag_negative = 0, count = 0;
  if (number < 0) {
    number = -number;
    flag_negative = 1;
  }
  if (number == 0 && !flags.dot) {
    buffer[i] = '0';
    i++;
  }

  while (number) {
    buffer[i] = get_num_to_chr(number % flags.number_system, flags.upper_case);
    i++;
    number /= 10;
  }
  count = i;
  if (flags.minus) {
    str = proc_di_flag_minus(str, &flags, buffer, count, flag_negative);
  } else
    str = proc_di(str, &flags, buffer, count, flag_negative);
  return str;
}

Flag set_num_system(Flag flags, char format) {
  if (format == 'o')
    flags.number_system = 8;
  else if (format == 'x' || format == 'X')
    flags.number_system = 16;
  if (format == 'X') flags.upper_case = 1;
  return flags;
}

char *output_uoxX(char *str, Flag flags, char format, va_list *args) {
  unsigned long int number = 0;
  if (format == 'l')
    number = (unsigned long int)va_arg(*args, unsigned long int);
  else if (format == 'h')
    number = (unsigned short)va_arg(*args, unsigned int);
  else
    number = (unsigned int)va_arg(*args, unsigned int);
  char buffer[sizeof(unsigned long int) * 8] = "0";
  int i = 0, count = 0;
  unsigned long int num_copy = number;
  if (number == 0 && !flags.dot) {
    buffer[i] = '0';
    i++;
  }
  while (num_copy) {
    buffer[i] =
        get_num_to_chr(num_copy % flags.number_system, flags.upper_case);
    i++;
    num_copy /= flags.number_system;
  }
  count = i;
  if (flags.minus) {
    if (flags.hash) str = proc_uoxX_flag_hash(str, flags, number);
    str = proc_uoxX_flag_minus(str, buffer, flags, count);
  } else if (!flags.minus) {
    str = proc_uoxX(str, buffer, flags, count, number);
  }
  return str;
}

char *output_c(char *str, Flag flags, int c) {
  char *ptr = s21_NULL;
  while (flags.width - 1 > 0 && !flags.minus) {
    *str = ' ';
    str++;
    flags.width--;
  }

  *str = c;
  str++;
  while (flags.width - 1 > 0 && flags.minus) {
    *str = ' ';
    str++;
    flags.width--;
  }
  ptr = str;

  return ptr;
}

char *copy_reversed_dig(char *str, const char *buffer, int size) {
  for (int j = size - 1; j >= 0; j--) {
    *str = buffer[j];
    str++;
  }
  return str;
}

char *proc_di_flag_minus(char *str, Flag *flags, const char *buffer, int count,
                         int flag_negative) {
  int i = count, accuracy = flags->accuracy, width = flags->width;

  if (flag_negative) {
    flags->space = 0;
    *str = '-';
    str++;
    count++;
  }

  if (flags->plus && !flag_negative) {
    flags->space = 0;
    *str = '+';
    str++;
    count++;
  }

  if (flags->space) {
    *str = ' ';
    str++;
    count++;
  }

  while (accuracy - i > 0) {
    *str = '0';
    str++;
    accuracy--;
    count++;
  }

  str = copy_reversed_dig(str, buffer, i);

  while (width - count > 0) {
    *str = ' ';
    str++;
    count++;
  }

  return str;
}

char *proc_di(char *str, Flag *flags, const char *buffer, int count,
              int flag_negative) {
  int width = flags->width, accuracy = flags->accuracy, i = count;
  if (flags->width < flags->accuracy) {
    width = 0;
  }
  int c;
  while (width - (count = count > flags->accuracy ? count : flags->accuracy) >
         0 + (c = flags->plus ? flags->plus : flag_negative)) {
    if (flags->zero) {
      break;
    }
    *str = ' ';
    str++;
    count++;
  }
  if (flags->plus && !flag_negative) {
    flags->space = 0;
    *str = '+';
    str++;
    width--;
  }
  if (flag_negative) {
    flags->space = 0;
    *str = '-';
    str++;
    count++;
  }
  if (flags->space) {
    *str = ' ';
    str++;
    count++;
  }
  while (accuracy > i || width - count > 0) {
    *str = '0';
    str++;
    count++;
    accuracy--;
  }
  str = copy_reversed_dig(str, buffer, i);
  return str;
}

char *proc_uoxX_flag_hash(char *str, Flag flags, int number) {
  if (flags.hash && flags.number_system == 8 && number != 0) {
    *str = '0';
    str++;

  } else if (flags.hash && flags.number_system == 16 && flags.upper_case &&
             number != 0) {
    *str = '0';
    str++;
    *str = 'X';
    str++;

  } else if (flags.hash && flags.number_system == 16 && !flags.upper_case &&
             number != 0) {
    *str = '0';
    str++;
    *str = 'x';
    str++;
  }
  return str;
}

char *proc_uoxX_flag_minus(char *str, char *buffer, Flag flags, int count) {
  int i = count, accuracy = flags.accuracy;

  if (flags.hash && flags.number_system == 16) count += 2;
  if (flags.hash && flags.number_system == 8) {
    count += 1;
    accuracy -= 1;
  }
  while (accuracy - i > 0) {
    *str = '0';
    str++;
    accuracy--;
    count++;
  }

  str = copy_reversed_dig(str, buffer, i);
  while (flags.width - count > 0) {
    *str = ' ';
    str++;
    count++;
  }
  return str;
}

char *proc_uoxX(char *str, char *buffer, Flag flags, int count, int number) {
  int i = count, width = flags.width, accuracy = flags.accuracy;
  if (flags.hash && flags.number_system == 16) count += 2;
  if (flags.hash && flags.number_system == 8) count += 1;
  while (width - (count = count > flags.accuracy ? count : flags.accuracy) >
         0) {
    *str = flags.zero ? '0' : ' ';
    str++;
    count++;
  }

  if (flags.hash) {
    str = proc_uoxX_flag_hash(str, flags, number);
  }

  if (flags.hash && flags.number_system == 8) accuracy -= 1;
  while (accuracy - i > 0) {
    *str = '0';
    str++;
    accuracy--;
    count++;
  }
  str = copy_reversed_dig(str, buffer, i);

  return str;
}

char *output_s(char *str, Flag flags, va_list *args) {
  char *ptr = str;
  char *string = va_arg(*args, char *);
  if (string == s21_NULL) string = "(null)";

  if (string && *string != '\0') {
    int width_copy = flags.width;
    // если ширина меньше строки, то  длина строки
    if ((s21_size_t)flags.width < s21_strlen(string))
      flags.width = s21_strlen(string);
    // иначе, кол-во " " с учетом ширины и точности
    int count_space = flags.width - s21_strlen(string);
    if (flags.accuracy == 0 && !flags.dot) flags.accuracy = flags.width;

    if ((flags.accuracy != 0 || flags.dot) && flags.accuracy < width_copy)
      count_space = width_copy - flags.accuracy;

    while (count_space && !flags.minus) {
      *str = ' ';
      str++;
      count_space--;
    }
    while (*string) {
      if (!flags.accuracy) break;
      *str = *string;
      string++;
      str++;
      flags.accuracy--;
    }
    while (count_space && flags.minus) {
      *str = ' ';
      str++;
      count_space--;
    }
  }
  if (ptr) ptr = str;
  return ptr;
}

char *output_p(char *str, Flag *flags, va_list *args, char format) {
  flags->number_system = 16;
  flags->hash = 1;
  flags->upper_case = 0;
  format = 'l';

  if (flags->space && !flags->plus) {
    *str = ' ';
    str++;

  } else if (!flags->space && flags->plus) {
    *str = '+';
    str++;
  }

  str = output_uoxX(str, *flags, format, args);

  return str;
}

Flag set_flags_eEfFgG(Flag flags, char format) {
  if (format == 'e' || format == 'E') flags.e = 1;
  if (format == 'g' || format == 'G') flags.g = 1;
  if (format == 'E' || format == 'G' || format == 'F') flags.upper_case = 1;
  return flags;
}

char *output_fF(char *str, Flag flags, char format, va_list *args) {
  long double number = 0, integer = 0, frac = 0;
  Float floats = {};
  floats.to_plus = flags.plus;
  if (format == 'L') {
    number = va_arg(*args, long double);
    floats.format_L = 1;
  } else {
    number = va_arg(*args, double);
  }
  s21_size_t size_eg = 2;
  char buffer_int[sizeof(long double) * 8] = "0";
  char buffer_frac[sizeof(long double) * 8] = "0";
  char buffer_e[sizeof(long double) * 8] = "0";
  floats.inf_nan = inf_or_nan(buffer_int, number, flags, &floats);

  if (!floats.inf_nan) {
    if (flags.g) proc_g(&number, &flags, &floats);

    if (flags.e) {
      floats.e = normalize_e(&number, &flags);
      if (floats.e < 100) {
        size_eg += 2;
      } else {
        size_eg += 3;
      }
      output_e(floats.e, &size_eg, buffer_e, flags, &floats.count_exp);
    }
    divide_float(&number, &integer, &frac, &floats, &flags);
    round_float(&frac, &integer, &floats, flags);
    long int int_integer = (long int)integer;
    fill_buffer(buffer_int, &floats.i, int_integer, flags);
    fill_buffer(buffer_frac, &floats.f, (long int)frac, flags);
    set_param_f(&flags, &floats);
  }
  if (!flags.minus) {
    str = proc_f(str, flags, &floats, buffer_int, buffer_frac, buffer_e);
  } else {
    str = proc_f_flag_minus(str, flags, &floats, buffer_int, buffer_frac,
                            buffer_e);
  }
  return str;
}

int inf_or_nan(char *buffer, long double num, Flag flags, Float *floats) {
  int flag = 0;
  if (isnan(num) != 0) {
    if (flags.upper_case) {
      buffer = s21_memcpy(buffer, "NAN", 3);
    } else {
      buffer = s21_memcpy(buffer, "nan", 3);
    }
    buffer += 3;
    flag = 1;
    floats->count = 3;
    floats->i = 3;
  } else if (isinf(num) != 0) {
    if (flags.upper_case) {
      buffer = s21_memcpy(buffer, "FNI", 3);
    } else {
      buffer = s21_memcpy(buffer, "fni", 3);
    }
    flag = 1;
    buffer += 3;
    floats->count = 3;
    floats->i = 3;
  }
  return flag;
}

// eE
long double normalize_e(long double *num, Flag *flags) {
  int i = 0;
  if (fabsl(*num) > 1) {
    while (fabsl(*num) > 10) {
      *num /= 10;
      i++;
      flags->e = 2;  // флаг что степень положительная
    }

  } else {
    while (fabsl(*num) < 0.999999) {
      if (*num == 0) {
        flags->e = 2;
        break;
      }
      *num *= 10;
      i++;
      flags->e = 1;  // флаг что степень отрицательная
    }
  }
  return i;
}

s21_size_t add_sum_to_str(char *buffer, int *i, int c) {
  *buffer = c;
  *i += 1;
  return 1;
}

int output_e(int e, s21_size_t *size_buffer, char *buffer, Flag flags, int *i) {
  int e_copy = e;
  if (e_copy == 0) {
    *size_buffer -= add_sum_to_str(
        buffer + *i, i,
        get_num_to_chr(e_copy % flags.number_system, flags.upper_case));
  }
  while (e_copy) {
    *size_buffer -= add_sum_to_str(
        buffer + *i, i,
        get_num_to_chr(e_copy % flags.number_system, flags.upper_case));
    e_copy /= 10;
  }
  if (e < 10) {
    *size_buffer -= add_sum_to_str(buffer + *i, i, '0');
  }
  if (flags.e == 2 || e == 0) {
    *size_buffer -= add_sum_to_str(buffer + *i, i, '+');
  } else {
    *size_buffer -= add_sum_to_str(buffer + *i, i, '-');
  }
  if (flags.upper_case) {
    *size_buffer -= add_sum_to_str(buffer + *i, i, 'E');

  } else {
    *size_buffer -= add_sum_to_str(buffer + *i, i, 'e');
  }
  return 0;
}

char *proc_f(char *str, Flag flags, Float *floats, const char *buffer_int,
             const char *buffer_frac, const char *buffer_e) {
  while ((flags.width > floats->count) && !flags.zero) {
    str = add_sign(str, ' ');
    floats->count++;
    floats->is_space = 1;
  }
  if ((!floats->negative && !floats->to_plus) && flags.space &&
      (floats->count < flags.width || !floats->is_space)) {
    str = add_sign(str, ' ');
    floats->count++;
  }
  if (floats->negative) str = add_sign(str, '-');
  if (floats->to_plus) str = add_sign(str, '+');
  while ((flags.width > floats->count) && flags.zero) {
    str = add_sign(str, '0');
    floats->count++;
  }
  if (floats->is_int || floats->inf_nan) {
    str = copy_reversed_dig(str, buffer_int, floats->i);
  } else {
    str = add_sign(str, '0');
  }
  if (floats->to_dot) {
    str = add_sign(str, '.');
    floats->i++;

    for (int z = floats->f; z < flags.accuracy; z++) {
      str = add_sign(str, '0');
    }
  }
  if (floats->is_frac) {
    str = copy_reversed_dig(str, buffer_frac, floats->f);
  } else {
    for (int j = floats->f - 1; j >= 0; j--) {
      str = add_sign(str, '0');
    }
  }

  if (flags.e) str = copy_reversed_dig(str, buffer_e, floats->count_exp);
  return str;
}

char *proc_f_flag_minus(char *str, Flag flags, Float *floats,
                        const char *buffer_int, const char *buffer_frac,
                        const char *buffer_e) {
  if (!floats->negative && !floats->to_plus && flags.space) {
    str = add_sign(str, ' ');
    floats->count++;
  }
  if (floats->negative) str = add_sign(str, '-');

  while ((flags.width > floats->count) && flags.zero) {
    str = add_sign(str, '0');
    floats->count++;
  }
  if (floats->to_plus) str = add_sign(str, '+');

  if (floats->is_int || floats->inf_nan) {
    str = copy_reversed_dig(str, buffer_int, floats->i);
  } else {
    str = add_sign(str, '0');
  }

  if (floats->to_dot) {
    str = add_sign(str, '.');
    floats->i++;
    for (int z = floats->f; z < flags.accuracy; z++) {
      str = add_sign(str, '0');
    }
  }

  if (floats->is_frac) {
    str = copy_reversed_dig(str, buffer_frac, floats->f);
  } else {
    for (int j = floats->f - 1; j >= 0; j--) {
      str = add_sign(str, '0');
    }
  }
  if (flags.e) str = copy_reversed_dig(str, buffer_e, floats->count_exp);

  while ((flags.width > floats->count) && !flags.zero) {
    str = add_sign(str, ' ');
    floats->count++;
  }
  return str;
}

char *add_sign(char *str, char c) {
  *str = c;
  str++;
  return str;
}

void fill_buffer(char *buffer, int *i, long int dig, Flag flags) {
  while (dig) {
    buffer[*i] = get_num_to_chr(dig % flags.number_system, flags.upper_case);
    *i += 1;
    dig /= 10;
  }
}

void set_param_f(Flag *flags, Float *floats) {
  floats->to_dot = flags->hash || (flags->dot && flags->accuracy) ||
                           floats->is_frac || floats->format_L ||
                           !floats->is_int
                       ? 1
                       : 0;

  if (floats->negative) floats->to_plus = 0;

  if (!floats->is_int) floats->i = 1;

  if (!floats->is_frac) floats->f = flags->accuracy;

  if (flags->accuracy_dot_isnull && !flags->hash) floats->to_dot = 0;

  floats->count = floats->i + floats->f + floats->to_dot + floats->negative +
                  floats->to_plus + floats->count_exp;
}

void round_float(long double *frac, long double *integer, Float *floats,
                 Flag flags) {
  if (fmodl(fabsl(*frac) * 10, 10.0) > 4) {
    *frac = roundl(*frac);
    long double check = *frac;
    int count_num_frac = 0;

    while ((long)check > 0) {
      check /= 10;
      count_num_frac++;
    }
    if (count_num_frac - flags.accuracy == 1) {
      *frac = 0;
      *integer += 1;
      floats->to_dot = 1;
      floats->is_int = 1;
    }
  }
}

void divide_float(long double *number, long double *integer, long double *frac,
                  Float *floats, Flag *flags) {
  if (*number < 0) {
    floats->negative = 1;
    *number *= -1;
  }
  *frac = modfl(*number, integer);

  if (!flags->dot && !flags->accuracy && !flags->g) flags->accuracy = 6;
  if (flags->dot && !flags->accuracy && flags->g) flags->accuracy = 6;

  if (*frac + 0.000000000000001 >= 1) {
    *frac = 0;
    *integer += 1;
  }
  if (*integer) floats->is_int = 1;
  if (*frac) floats->is_frac = 1;

  for (int x = 0; x < flags->accuracy; x++) *frac *= 10;
}

void proc_g(long double *number, Flag *flags, Float *floats) {
  long double integer = 0, frac = 0;
  int i_c = 0, f_c = 0;
  divide_float(number, &integer, &frac, floats, flags);
  long double i_copy = integer, f_copy = frac;
  if ((long)frac == 0) flags->accuracy = 0;
  //  убирает лишние 0
  while ((long)frac % 10 == 0 && flags->accuracy > 0 && (long)frac != 0 &&
         (!flags->hash)) {
    frac /= 10;
  }
  // считает число цифр
  while ((long)i_copy != 0) {
    i_copy /= 10;
    i_c++;
  }
  while (flags->accuracy > 0 && (long)f_copy != 0) {
    f_copy /= 10;
    f_c++;
  }
  // убирает лишние 0 если флаг #
  while (i_c + f_c < flags->accuracy && (long)frac != 0 && (flags->hash)) {
    frac /= 10;
    flags->accuracy--;
  }
  if (!flags->dot && (6 - i_c > 2)) {
    flags->accuracy = 6 - i_c;
  }
  if (flags->dot && flags->accuracy > flags->width) {
    flags->accuracy = flags->accuracy - i_c;
  }
  if (flags->dot && i_c && flags->accuracy <= 4) {
    flags->e = 1;
    *number = roundl((long)*number);
    flags->accuracy = 0;
    flags->dot = 0;
    floats->is_frac = 0;
  }
  flags->width -= (flags->accuracy + floats->to_dot);
}