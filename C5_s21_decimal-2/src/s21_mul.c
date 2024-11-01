#include "s21_decimal.h"
#include "utils.h"

int s21_mul(s21_decimal first, s21_decimal second, s21_decimal *answer) {
  answer->bits[0] = answer->bits[1] = answer->bits[2] = answer->bits[3] = 0;
  int answer_sign = (extractBitSign(first) != extractBitSign(second))
                        ? 1
                        : 0;  // Определение знака результата
  assignSymbol(&first, 0);  // Установка знаков аргументов в положительные
  assignSymbol(&second, 0);

  for (int i = 0; i <= countLastBit(first); i++) {
    if (retrieveBit(first, i)) {
      s21_decimal tmp_res = second;
      leftShift(&tmp_res, i);
      addBit(*answer, tmp_res, answer);
    }
  }

  while (retrieveLevel(first) > 0 || retrieveLevel(second) > 0) {
    s21_decimal *first_1 =
        (countLastBit(first) > countLastBit(second) && retrieveLevel(first) > 0)
            ? &first
            : &second;
    s21_decimal *second_1 = (countLastBit(second) > countLastBit(first) &&
                             retrieveLevel(second) > 0)
                                ? &first
                                : &second;

    if (retrieveLevel(*first_1) <= 0) break;

    scaleDown(first_1, 1);
    int scale2 = retrieveLevel(*first_1);
    setLevel(first_1, scale2);
    s21_mul(*first_1, *second_1, answer);
  }

  setLevel(answer, retrieveLevel(first) + retrieveLevel(second));
  assignSymbol(answer, answer_sign);

  return (extractBitSign(*answer) && answer_sign) ? 2 : 0;
}