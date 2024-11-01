#include "utils.h"

s21_decimal *assignSymbol(s21_decimal *number, int bit) {
  number->bits[3] =
      (bit) ? (number->bits[3] | (1u << 31)) : (number->bits[3] & ~(1u << 31));
  return number;
}

int extractBitSign(s21_decimal number) {
  int result = (number.bits[3] & (1u << 31)) != 0;
  return result;
}

int retrieveBit(s21_decimal number, int bit) {
  return (number.bits[bit / 32] & (1u << (bit % 32))) != 0;
}

int countLastBit(s21_decimal number) {
  int counter = 95;
  while ((counter >= 0) && (!retrieveBit(number, counter))) {
    counter -= 1;
  }
  return counter;
}

int retrieveLevel(s21_decimal number) { return (char)(number.bits[3] >> 16); }

s21_decimal *modifyBit(s21_decimal *number, int pos, int bit) {
  if (pos / 32 < 4 && bit)
    number->bits[pos / 32] |= (1u << (pos % 32));
  else if (pos / 32 < 4 && !bit)
    number->bits[pos / 32] &= ~(1u << (pos % 32));
  return number;
}

int addBit(s21_decimal number_1, s21_decimal number_2, s21_decimal *result) {
  int fresh = 0, exp = 0;
  for (int i = 0; i < 96; i++) {
    int bitValue_1 = retrieveBit(number_1, i),
        bitValue_2 = retrieveBit(number_2, i);
    int sum = bitValue_1 + bitValue_2 + exp;
    modifyBit(result, i, sum % 2);
    exp = (bitValue_1 && bitValue_2) || (bitValue_1 && exp) ||
          (bitValue_2 && exp);
    fresh = fresh || (i == 95 && exp == 1 && !retrieveBit(number_1, 97) &&
                      !retrieveBit(number_2, 97));
  }
  return fresh;
}

s21_decimal *setLevel(s21_decimal *number, int scale) {
  if (scale >= 0 && scale <= 28) {
    number->bits[3] = (number->bits[3] & ~(0xFF << 16)) | (scale << 16);
    extractBitSign(*number) ? assignSymbol(number, 1) : number;
  }
  return number;
}

s21_decimal *leftShift(s21_decimal *number, int shift) {
  int lastBitIndex = countLastBit(*number);
  if (lastBitIndex + shift <= 95) {
    for (int y = 0; y < shift; y++) {
      int bitTransfer_1 = retrieveBit(*number, 31);
      int bitTransfer_2 = retrieveBit(*number, 63);
      for (int x = 0; x < 3; x++) number->bits[x] <<= 1;
      if (bitTransfer_1) modifyBit(number, 32, 1);
      if (bitTransfer_2) modifyBit(number, 64, 1);
    }
  }
  return number;
}

s21_decimal *scaleUp(s21_decimal *number, int shift) {
  if (retrieveLevel(*number) + shift < 29) {
    setLevel(number, retrieveLevel(*number) + shift);
    s21_decimal auxValue_1 = *number, auxValue_2 = *number;
    if (addBit(*leftShift(&auxValue_1, 1), *leftShift(&auxValue_2, 3), number))
      modifyBit(number, 96, 1);
  }
  return number;
}

s21_decimal *scaleDown(s21_decimal *number, int shift) {
  for (int y = 0; y < shift; y++) {
    unsigned long long overflow = 0;
    for (int x = 0; x < 3; x++) {
      overflow = overflow * (MAX_UINT + 1) + number->bits[x];
      number->bits[x] = overflow / 10;
      overflow %= 10;
    }
  }
  setLevel(number, retrieveLevel(*number) - shift);
  return number;
}

void equalizeLevels(s21_decimal *number_1, s21_decimal *number_2) {
  int level_1 = retrieveLevel(*number_1);
  int level_2 = retrieveLevel(*number_2);

  if (level_1 != level_2) {
    if (level_1 < level_2) {
      equalizeLevels(number_2, number_1);
      return;
    }

    int scaleLow = level_2;
    int scaleHigh = level_1;

    while (scaleHigh > scaleLow && !retrieveBit(*number_2, 96)) {
      scaleUp(number_2, 1);
      scaleLow++;
    }

    while (scaleHigh > scaleLow) {
      scaleDown(number_1, scaleHigh - scaleLow);
      setLevel(number_1, scaleLow);
      scaleHigh--;
    }
  }
}

void initializeByZeros(s21_decimal *value) {
  (*value).bits[0] = 0;
  (*value).bits[1] = 0;
  (*value).bits[2] = 0;
  (*value).bits[3] = 0;
}

int isLessBigDecimal(s21_big_decimal v1, s21_big_decimal v2) {
  int arg = 0;
  int flag = 0;
  for (int i = 5; i >= 0 && !flag; i--) {
    if (v1.bits[i] > v2.bits[i]) {
      arg = 0;
      flag = 1;
    } else if (v1.bits[i] < v2.bits[i]) {
      arg = 1;
      flag = 1;
    }
  }
  return arg;
}
int zeroDecimal(s21_decimal v) {
  int arg = 0;
  if (!v.bits[0] && !v.bits[1] && !v.bits[2]) arg = 1;
  return arg;
}

void addBigDecimal(s21_big_decimal v_1, s21_big_decimal v_2,
                   s21_big_decimal *res) {
  initializeByBigZeros(res);
  int in_mind = 0;

  for (int i = 0; i < 192; i++) {
    int v1_bit = getBigBit(v_1, i);
    int v2_bit = getBigBit(v_2, i);
    int sum = v1_bit + v2_bit + in_mind;
    int res_bit = sum % 2;
    in_mind = sum > 1 ? 1 : 0;
    setBigBit(res, i, res_bit);
  }
}

void subBigDecimal(s21_big_decimal v_1, s21_big_decimal v_2,
                   s21_big_decimal *res) {
  initializeByBigZeros(res);
  int loaned = 0;
  for (int i = 0; i < 192; i++) {
    int v1_bit = getBigBit(v_1, i);
    int v2_bit = getBigBit(v_2, i);
    int added = v1_bit - v2_bit - loaned < 0 ? 2 : 0;
    int sub = v1_bit - v2_bit - loaned + added;
    loaned = added == 0 ? 0 : 1;
    int res_bit = sub % 2;
    setBigBit(res, i, res_bit);
  }
}

void mulBigDecimal(s21_big_decimal v_1, s21_big_decimal v_2,
                   s21_big_decimal *res) {
  initializeByBigZeros(res);
  s21_big_decimal temp;
  temp = v_1;
  int last_index = lastBigBitIndex(v_2);
  for (int i = 0; i <= last_index; i++) {
    int v2_bit = getBigBit(v_2, i);
    if (v2_bit == 1) addBigDecimal(*res, temp, res);
    shiftLeftSide(&temp);
  }
}

s21_big_decimal divBigDecimal(s21_big_decimal v_1, s21_big_decimal v_2,
                              s21_big_decimal *res) {
  initializeByBigZeros(res);
  int count = 191;
  s21_big_decimal remain, temp_res;
  initializeByBigZeros(&temp_res);
  initializeByBigZeros(&remain);

  int dividend_size = lastBigBitIndex(v_1) + 1;
  int divisor_size = lastBigBitIndex(v_2) + 1;
  int remain_bits = dividend_size - divisor_size;

  s21_big_decimal dividend_part = getDividendPart(v_1, divisor_size);
  if (remain_bits < 0) remain = v_1;
  while (remain_bits >= 0) {
    int bit = getBigBit(v_1, remain_bits - 1);
    if (isLessBigDecimal(dividend_part, v_2)) {
      remain = dividend_part;
      shiftLeftSide(&dividend_part);
      setBigBit(&dividend_part, 0, bit);
      setBigBit(&temp_res, count--, 0);
    } else {
      subBigDecimal(dividend_part, v_2, &dividend_part);
      remain = dividend_part;
      shiftLeftSide(&dividend_part);
      setBigBit(&dividend_part, 0, bit);
      setBigBit(&temp_res, count--, 1);
    }
    remain_bits--;
  }

  for (int i = 191, j = i - count - 1; j >= 0; j--) {
    int bit = getBigBit(temp_res, i--);
    setBigBit(res, j, bit);
  }
  return remain;
}

int getBigBit(s21_big_decimal value, int index) {
  int bits_index = index / 32;
  int int_index = 31 - index % 32;
  int bit = -1;
  if (index > -1 && index < 192) {
    value.bits[bits_index] = value.bits[bits_index] << int_index;
    value.bits[bits_index] = value.bits[bits_index] >> 31;
    bit = value.bits[bits_index] == 0 ? 0 : 1;
  }
  return bit;
}

void setBigBit(s21_big_decimal *value, int index, int bit) {
  int bits_index = index / 32;
  int int_index = 31 - index % 32;

  if (bit == 1) {
    int mask = 1 << (31 - int_index);
    (*value).bits[bits_index] |= mask;
  } else {
    int mask = ~(1 << (31 - int_index));
    (*value).bits[bits_index] &= mask;
  }
}

void setSign(s21_decimal *value, unsigned int sign) {
  unsigned int one = 1;
  if (sign == 1) {
    unsigned int mask = (one << 31);
    value->bits[3] = value->bits[3] | mask;
  } else {
    unsigned int mask = ~(one << 31);
    value->bits[3] = value->bits[3] & mask;
  }
}

void setScale(s21_decimal *value, int scale) {
  for (int i = 20, j = 4; i >= 16; i--, j--) {
    int bit = (scale >> j) & 1;
    if (bit) {
      (*value).bits[3] |= (bit << i);
    } else {
      (*value).bits[3] &= ~(1 << i);
    }
  }
}

s21_big_decimal getDividendPart(s21_big_decimal dividend, int bitness) {
  s21_big_decimal result;
  initializeByBigZeros(&result);
  int start = lastBigBitIndex(dividend);
  int index = bitness - 1;

  for (int i = 0; i < bitness; i++) {
    int bit = getBigBit(dividend, start - i);
    setBigBit(&result, index, bit);
    index--;
  }
  return result;
}

s21_big_decimal getBigDecimal10() {
  s21_big_decimal ten;
  initializeByBigZeros(&ten);
  setBigBit(&ten, 3, 1);
  setBigBit(&ten, 1, 1);
  return ten;
}

int zeroBigDecimal(s21_big_decimal v) {
  int arg = FALSE;
  if (!v.bits[0] && !v.bits[1] && !v.bits[2] && !v.bits[3] && !v.bits[4] &&
      !v.bits[5])
    arg = TRUE;
  return arg;
}

int reduceScale(s21_big_decimal *value, int *scale) {
  int code;
  int prev_zeroes = TRUE;
  int rounder = -1;
  s21_big_decimal remain;

  while (lastBigBitIndex(*value) > 95 && *scale > 0) {
    remain = divBigDecimal(*value, getBigDecimal10(), value);
    (*scale)--;
    if (lastBigBitIndex(*value) < 96) {
      rounder = remain.bits[0] < 5 ? 0 : remain.bits[0] > 5 ? 1 : rounder;
      if (rounder == -1)
        rounder = !prev_zeroes ? 1 : getBigBit(*value, 0) ? 1 : 0;
      s21_big_decimal big_rounder;
      initializeByBigZeros(&big_rounder);
      if (rounder == 1) setBigBit(&big_rounder, 0, 1);
      addBigDecimal(*value, big_rounder, value);
    } else {
      prev_zeroes = zeroBigDecimal(remain) ? TRUE : FALSE;
    }
  }
  code = lastBigBitIndex(*value) < 96 ? 0 : 1;
  return code;
}

int lastBigBitIndex(s21_big_decimal value) {
  int index = -1;
  for (int i = 191; i >= 0 && index == -1; i--) {
    if (getBigBit(value, i) == 1) index = i;
  }
  return index;
}

s21_big_decimal decimalToBig(s21_decimal value) {
  s21_big_decimal result;
  initializeByBigZeros(&result);
  for (int i = 0; i < 3; i++) {
    result.bits[i] = value.bits[i];
  }
  return result;
}
s21_decimal bigToDecimal(s21_big_decimal value) {
  s21_decimal result;
  initializeByZeros(&result);
  for (int i = 0; i < 3; i++) {
    result.bits[i] = value.bits[i];
  }
  return result;
}

void initializeByBigZeros(s21_big_decimal *value) {
  (*value).bits[0] = 0;
  (*value).bits[1] = 0;
  (*value).bits[2] = 0;
  (*value).bits[3] = 0;
  (*value).bits[4] = 0;
  (*value).bits[5] = 0;
}

void shiftLeftSide(s21_big_decimal *value) {
  int shift_bit1 = getBigBit(*value, 31);
  (*value).bits[0] = (*value).bits[0] << 1;
  for (int i = 1; i < 6; i++) {
    int shift_bit2 = getBigBit(*value, (32 * (i + 1) - 1));
    (*value).bits[i] = (*value).bits[i] << 1;
    if (shift_bit1 == 1) setBigBit(value, 32 * i, 1);
    shift_bit1 = shift_bit2;
  }
}
