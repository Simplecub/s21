#include "s21_decimal.h"
#include "utils.h"

int s21_add(s21_decimal first, s21_decimal second, s21_decimal *answer) {
  int condition = 0;
  int first_sign = extractBitSign(first);
  int second_sign = extractBitSign(second);
  int x = 0;

  while (x < 4) {
    answer->bits[x] = 0;
    ++x;
  }
  if (first_sign == second_sign) {
    equalizeLevels(&first, &second);
    if (addBit(first, second, answer)) {
      if (!retrieveLevel(first) || !retrieveLevel(second))
        condition = first_sign ? 2 : 1;
      else if (retrieveLevel(first) > 0 && retrieveLevel(second) > 0) {
        setLevel(scaleDown(&first, 1), retrieveLevel(first) - 1);
        setLevel(scaleDown(&second, 1), retrieveLevel(second) - 1);
        condition = s21_add(first, second, answer);
      }
    } else
      setLevel(assignSymbol(answer, first_sign), retrieveLevel(first));
  } else {
    condition =
        s21_sub(first_sign ? second : first,
                *assignSymbol(first_sign ? &first : &second, 0), answer);
  }
  return condition;
}
