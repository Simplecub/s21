#ifndef SRC_S21_UTILS_H_
#define SRC_S21_UTILS_H_

#include "s21_decimal.h"

int retrieveBit(s21_decimal value, int bit);
int countLastBit(s21_decimal value);
s21_decimal *modifyBit(s21_decimal *value, int pos, int bit);
int addBit(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

int retrieveLevel(s21_decimal value);
s21_decimal *setLevel(s21_decimal *value, int scale);
s21_decimal *scaleUp(s21_decimal *value, int shift);
s21_decimal *scaleDown(s21_decimal *value, int shift);
void equalizeLevels(s21_decimal *value_1, s21_decimal *value_2);

int extractBitSign(s21_decimal value);
s21_decimal *assignSymbol(s21_decimal *value, int bit);

s21_decimal *leftShift(s21_decimal *value, int shift);
void addBigDecimal(s21_big_decimal v_1, s21_big_decimal v_2,
                   s21_big_decimal *res);
void subBigDecimal(s21_big_decimal v_1, s21_big_decimal v_2,
                   s21_big_decimal *res);
void mulBigDecimal(s21_big_decimal v_1, s21_big_decimal v_2,
                   s21_big_decimal *res);
s21_big_decimal divBigDecimal(s21_big_decimal v_1, s21_big_decimal v_2,
                              s21_big_decimal *res);

int getBigBit(s21_big_decimal value, int index);
void setBigBit(s21_big_decimal *value, int index, int bit);
void setSign(s21_decimal *value, unsigned int sign);
void setScale(s21_decimal *value, int scale);
s21_big_decimal getDividendPart(s21_big_decimal dividend, int bitness);
s21_big_decimal getBigDecimal10();
void shiftLeftSide(s21_big_decimal *value);
int isLessBigDecimal(s21_big_decimal v1, s21_big_decimal v2);
int zeroBigDecimal(s21_big_decimal v);
int zeroDecimal(s21_decimal v);

int reduceScale(s21_big_decimal *value, int *scale);

int lastBigBitIndex(s21_big_decimal value);
s21_big_decimal decimalToBig(s21_decimal value);
s21_decimal bigToDecimal(s21_big_decimal value);
void initializeByZeros(s21_decimal *value);
void initializeByBigZeros(s21_big_decimal *value);

#endif