#include "s21_decimal.h"
#include "utils.h"

int s21_sub(s21_decimal first, s21_decimal second, s21_decimal *answer) {
  int status = 0, valueSign_1 = extractBitSign(first),
      valueSign_2 = extractBitSign(second);
  for (int x = 0; x < 4; x += 1) answer->bits[x] = 0;
  if (valueSign_1 != valueSign_2) {
    status =
        s21_add(*assignSymbol(&first, 0), *assignSymbol(&second, 0), answer);
    status = status ? (valueSign_1 ? 2 : 1) : status;
    assignSymbol(answer, valueSign_1);
  } else {
    equalizeLevels(&first, &second);
    if (!s21_is_equal(first, second)) {
      assignSymbol(&first, 0);
      assignSymbol(&second, 0);
      s21_decimal res = {{0, 0, 0, 0}};
      s21_decimal add = {{1, 0, 0, 0}};
      for (int i = 0; i < 3; ++i) first.bits[i] = ~first.bits[i];
      addBit(first, add, &res);
      for (int i = 0; i < 3; ++i) first.bits[i] = res.bits[i];
      modifyBit(&first, 97, 1);
      if (s21_is_less(first, second)) {
        status = s21_add(first, second, answer);
        assignSymbol(answer, !valueSign_2);
      } else {
        status = s21_add(second, first, answer);
        assignSymbol(answer, valueSign_1);
      }
    }
  }
  return status;
}
