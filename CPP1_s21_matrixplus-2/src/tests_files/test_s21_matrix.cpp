
#include <gtest/gtest.h>

#include "../s21_matrix_oop.h"

TEST(MatrixTest, InitConstructorBase) {
  S21Matrix matrix1;
  EXPECT_EQ(2, matrix1.GetRows());
  EXPECT_EQ(2, matrix1.GetCols());
}

TEST(MatrixTest, InitConstructorParam) {
  S21Matrix matrix1(6, 8);
  EXPECT_EQ(6, matrix1.GetRows());
  EXPECT_EQ(8, matrix1.GetCols());
}
TEST(MatrixTest, InitConstructorParamThrow) {
  try {
    S21Matrix a(-3, 2);
  } catch (std::invalid_argument& e) {
    EXPECT_STREQ(
        "CreationError: The number of rows or cols cannot be less than 1",
        e.what());
  }
}

TEST(MatrixTest, InitConstructorCopy) {
  S21Matrix matrix1(4, 14);
  S21Matrix copy(matrix1);
  EXPECT_EQ(4, matrix1.GetRows());
  EXPECT_EQ(14, matrix1.GetCols());
}

TEST(MatrixTest, InitConstructorMove) {
  S21Matrix a(3, 2);
  a(0, 0) = 1.0, a(0, 1) = 4.0;
  a(1, 0) = 2.0, a(1, 1) = 5.0;
  a(2, 0) = 3.0, a(2, 1) = 6.0;
  S21Matrix copy(a);
  S21Matrix b(std::move(a));
  EXPECT_TRUE(b.EqMatrix(copy));
}

TEST(MatrixTest, EqMatrixElementsAreEqual) {
  S21Matrix matrix1;
  S21Matrix matrix2;
  EXPECT_TRUE(matrix1.EqMatrix(matrix2));
}

TEST(MatrixTest, EqMatrixDifferentSize) {
  S21Matrix matrix1(2, 3);
  S21Matrix matrix2(3, 2);
  EXPECT_FALSE(matrix1.EqMatrix(matrix2));
}

TEST(MatrixTest, EqMatrixDifferentMoreAccuracy) {
  S21Matrix matrix1;
  S21Matrix matrix2;
  matrix1(0, 0) = 1.000001;
  matrix2(0, 0) = 1.;
  EXPECT_FALSE(matrix1.EqMatrix(matrix2));
}
TEST(MatrixTest, EqMatrixDifferentLessAccuracy) {
  S21Matrix matrix1;
  S21Matrix matrix2;
  matrix1(0, 0) = 1.00000001;
  matrix2(0, 0) = 1.;
  EXPECT_TRUE(matrix1.EqMatrix(matrix2));
}

TEST(MatrixTest, SumMatrixEq) {
  S21Matrix a(3, 2);
  a(0, 0) = 1.0, a(0, 1) = 4.0;
  a(1, 0) = 2.0, a(1, 1) = 5.0;
  a(2, 0) = 3.0, a(2, 1) = 6.0;
  S21Matrix b(3, 2);
  b(0, 0) = 1.0, b(0, 1) = 4.0;
  b(1, 0) = 2.0, b(1, 1) = 5.0;
  b(2, 0) = 3.0, b(2, 1) = 6.0;
  S21Matrix res(3, 2);
  res(0, 0) = 2.0, res(0, 1) = 8.0;
  res(1, 0) = 4.0, res(1, 1) = 10.0;
  res(2, 0) = 6.0, res(2, 1) = 12.0;
  a.SumMatrix(b);
  EXPECT_TRUE(res.EqMatrix(a));
}

TEST(MatrixTest, SumMatrixDifferentSize) {
  S21Matrix a(3, 2);
  a(0, 0) = 1.0, a(0, 1) = 4.0;
  a(1, 0) = 2.0, a(1, 1) = 5.0;
  a(2, 0) = 3.0, a(2, 1) = 6.0;
  S21Matrix b(2, 2);
  b(0, 0) = 1.0, b(0, 1) = 4.0;
  b(1, 0) = 2.0, b(1, 1) = 5.0;

  try {
    a.SumMatrix(b);
  } catch (std::out_of_range& e) {
    EXPECT_STREQ("Is different size matrix to sum!", e.what());
  }
}

TEST(MatrixTest, SubMatrixEq) {
  S21Matrix a(3, 2);
  a(0, 0) = 1.0, a(0, 1) = 4.0;
  a(1, 0) = 2.0, a(1, 1) = 5.0;
  a(2, 0) = 3.0, a(2, 1) = 6.0;
  S21Matrix b(3, 2);
  b(0, 0) = 1.0, b(0, 1) = 4.0;
  b(1, 0) = 2.0, b(1, 1) = 5.0;
  b(2, 0) = 3.0, b(2, 1) = 6.0;
  S21Matrix res(3, 2);
  res(0, 0) = 0;
  res(0, 1) = 0;
  res(1, 0) = 0;
  res(1, 1) = 0;
  res(2, 0) = 0;
  res(2, 1) = 0;
  a.SubMatrix(b);
  EXPECT_TRUE(res.EqMatrix(a));
}

TEST(MatrixTest, SubMatrixDifferentSize) {
  S21Matrix a(3, 2);
  a(0, 0) = 1.0, a(0, 1) = 4.0;
  a(1, 0) = 2.0, a(1, 1) = 5.0;
  a(2, 0) = 3.0, a(2, 1) = 6.0;
  S21Matrix b(2, 2);
  b(0, 0) = 1.0, b(0, 1) = 4.0;
  b(1, 0) = 2.0, b(1, 1) = 5.0;

  try {
    a.SubMatrix(b);
  } catch (std::out_of_range& e) {
    EXPECT_STREQ("Is different size matrix to sub!", e.what());
  }
}

TEST(MatrixTest, MulNumber) {
  S21Matrix a(3, 2);
  a(0, 0) = 1.0, a(0, 1) = 4.0;
  a(1, 0) = 2.0, a(1, 1) = 5.0;
  a(2, 0) = 3.0, a(2, 1) = 6.0;
  double num = 2.0;

  a.MulNumber(num);

  S21Matrix res(3, 2);
  res(0, 0) = 2.0, res(0, 1) = 8.0;
  res(1, 0) = 4.0, res(1, 1) = 10.0;
  res(2, 0) = 6.0, res(2, 1) = 12.0;

  EXPECT_TRUE(res.EqMatrix(a));
}

TEST(MatrixTest, MulMatrix) {
  S21Matrix a(3, 2);
  a(0, 0) = 1.0, a(0, 1) = 4.0;
  a(1, 0) = 2.0, a(1, 1) = 5.0;
  a(2, 0) = 3.0, a(2, 1) = 6.0;

  S21Matrix b(2, 3);
  b(0, 0) = 1.0, b(0, 1) = -1., b(0, 2) = 1;
  b(1, 0) = 2.0, b(1, 1) = 3.0, b(1, 2) = 4.0;

  S21Matrix res(3, 3);
  res(0, 0) = 9, res(0, 1) = 11, res(0, 2) = 17;
  res(1, 0) = 12, res(1, 1) = 13, res(1, 2) = 22;
  res(2, 0) = 15, res(2, 1) = 15, res(2, 2) = 27;

  a.MulMatrix(b);
  EXPECT_TRUE(res.EqMatrix(a));
}

TEST(MatrixTest, MulMatrixDifferentSize) {
  S21Matrix a(3, 2);
  a(0, 0) = 1.0, a(0, 1) = 4.0;
  a(1, 0) = 2.0, a(1, 1) = 5.0;
  a(2, 0) = 3.0, a(2, 1) = 6.0;
  S21Matrix b(2, 2);
  b(0, 0) = 1.0, b(0, 1) = 4.0;
  b(1, 0) = 2.0, b(1, 1) = 5.0;

  try {
    a.MulMatrix(b);
  } catch (std::out_of_range& e) {
    EXPECT_STREQ("Wrong MulMatrix: rowsA != colsB", e.what());
  }
}

TEST(MatrixTest, Transpose) {
  S21Matrix a(3, 2);
  a(0, 0) = 1.0, a(0, 1) = 4.0;
  a(1, 0) = 2.0, a(1, 1) = 5.0;
  a(2, 0) = 3.0, a(2, 1) = 6.0;
  S21Matrix t = a.Transpose();
  S21Matrix b(2, 3);
  b(0, 0) = 1, b(0, 1) = 2, b(0, 2) = 3;
  b(1, 0) = 4, b(1, 1) = 5, b(1, 2) = 6;

  EXPECT_TRUE(b.EqMatrix(t));
}

TEST(MatrixTest, Determinant) {
  double determ = 0.0;
  S21Matrix a(3, 3);
  a(0, 0) = 4000.87;
  a(0, 1) = 454.0;
  a(0, 2) = 4.0;
  a(1, 0) = 2.0;
  a(1, 1) = 1.897;
  a(1, 2) = 3.0;
  a(2, 0) = 0.000087;
  a(2, 1) = 2.5668;
  a(2, 2) = 1.0;
  determ = a.Determinant();
  EXPECT_EQ(determ, -24105.996724156);
}
TEST(MatrixTest, Determinant2) {
  double determ = 0.0;
  S21Matrix a(3, 3);
  a(0, 0) = 1;
  a(0, 1) = 2;
  a(0, 2) = 3;
  a(1, 0) = 0;
  a(1, 1) = 0;
  a(1, 2) = 4;
  a(2, 0) = 5;
  a(2, 1) = 2;
  a(2, 2) = 1.0;
  determ = a.Determinant();
  EXPECT_EQ(determ, 32);
}

TEST(MatrixTest, DeterminantZeroColumn) {
  double determ = 0.0;
  S21Matrix a(3, 3);
  a(0, 0) = 0, a(0, 1) = 2, a(0, 2) = 3;
  a(1, 0) = 0, a(1, 1) = 0, a(1, 2) = 4;
  a(2, 0) = 0, a(2, 1) = 0, a(2, 2) = 1.0;
  determ = a.Determinant();
  EXPECT_EQ(determ, 0);
}

TEST(MatrixTest, DeterminantNotSquare) {
  double determ = 0;
  S21Matrix a(2, 3);
  a(0, 0) = 0, a(0, 1) = 2, a(0, 2) = 3;
  a(1, 0) = 0, a(1, 1) = 0, a(1, 2) = 4;
  try {
    determ = a.Determinant();
  } catch (std::out_of_range& e) {
    EXPECT_STREQ("The matrix for Determinant must be square", e.what());
  }
  EXPECT_EQ(determ, 0);
}

TEST(MatrixTest, CalcComplements) {
  S21Matrix a(3, 3);
  a(0, 0) = 1, a(0, 1) = 2, a(0, 2) = 3;
  a(1, 0) = 0, a(1, 1) = 4, a(1, 2) = 2;
  a(2, 0) = 5, a(2, 1) = 2, a(2, 2) = 1;

  S21Matrix eq_matrix(3, 3);
  eq_matrix(0, 0) = 0, eq_matrix(0, 1) = 10, eq_matrix(0, 2) = -20;
  eq_matrix(1, 0) = 4, eq_matrix(1, 1) = -14, eq_matrix(1, 2) = 8;
  eq_matrix(2, 0) = -8, eq_matrix(2, 1) = -2, eq_matrix(2, 2) = 4;

  S21Matrix res = a.CalcComplements();

  EXPECT_TRUE(res.EqMatrix(eq_matrix));
}

TEST(MatrixTest, CalcComplementsMatrix1x1) {
  S21Matrix a(1, 1);
  a(0, 0) = 1;

  S21Matrix eq_matrix(1, 1);
  eq_matrix(0, 0) = 1;

  S21Matrix res = a.CalcComplements();

  EXPECT_TRUE(res.EqMatrix(eq_matrix));
}

TEST(MatrixTest, CalcComplementsNotSquareThrow) {
  S21Matrix a(2, 3);
  try {
    S21Matrix determ = a.CalcComplements();
  } catch (std::out_of_range& e) {
    EXPECT_STREQ("The matrix for CalcComplements must be square", e.what());
  }
}

TEST(MatrixTest, InverseMatrix) {
  S21Matrix a(3, 3);
  a(0, 0) = 2, a(0, 1) = 5, a(0, 2) = 7;
  a(1, 0) = 6, a(1, 1) = 3, a(1, 2) = 4;
  a(2, 0) = 5, a(2, 1) = -2, a(2, 2) = -3;
  S21Matrix eq_matrix(3, 3);
  eq_matrix(0, 0) = 1, eq_matrix(0, 1) = -1, eq_matrix(0, 2) = 1;
  eq_matrix(1, 0) = -38, eq_matrix(1, 1) = 41, eq_matrix(1, 2) = -34;
  eq_matrix(2, 0) = 27, eq_matrix(2, 1) = -29, eq_matrix(2, 2) = 24;

  S21Matrix res = a.InverseMatrix();

  EXPECT_TRUE(res.EqMatrix(eq_matrix));
}

TEST(MatrixTest, InverseMatrixThrow) {
  S21Matrix a(3, 3);
  a(0, 0) = 0, a(0, 1) = 2, a(0, 2) = 3;
  a(1, 0) = 0, a(1, 1) = 0, a(1, 2) = 4;
  a(2, 0) = 0, a(2, 1) = 2, a(2, 2) = 1;
  try {
    S21Matrix iverse = a.InverseMatrix();
  } catch (std::logic_error& e) {
    EXPECT_STREQ("Error Calculate InverseMatrix - Determinant is null",
                 e.what());
  }
}

//  operators overloads
TEST(MatrixTest, OperatorPlus) {
  S21Matrix a(3, 2);
  a(0, 0) = 1.0, a(0, 1) = 4.0;
  a(1, 0) = 2.0, a(1, 1) = 5.0;
  a(2, 0) = 3.0, a(2, 1) = 6.0;
  S21Matrix b(3, 2);
  b(0, 0) = 1.0, b(0, 1) = 4.0;
  b(1, 0) = 2.0, b(1, 1) = 5.0;
  b(2, 0) = 3.0, b(2, 1) = 6.0;
  S21Matrix eq(3, 2);
  eq(0, 0) = 2.0, eq(0, 1) = 8.0;
  eq(1, 0) = 4.0, eq(1, 1) = 10.0;
  eq(2, 0) = 6.0, eq(2, 1) = 12.0;
  S21Matrix res = a + b;

  EXPECT_TRUE(res.EqMatrix(eq));
}

TEST(MatrixTest, OperatorPlusDifferentSize) {
  S21Matrix a(3, 2);
  a(0, 0) = 1.0, a(0, 1) = 4.0;
  a(1, 0) = 2.0, a(1, 1) = 5.0;
  a(2, 0) = 3.0, a(2, 1) = 6.0;
  S21Matrix b(2, 2);
  b(0, 0) = 1.0, b(0, 1) = 4.0;
  b(1, 0) = 2.0, b(1, 1) = 5.0;

  try {
    S21Matrix res = a + b;
  } catch (std::out_of_range& e) {
    EXPECT_STREQ("Is different size matrix to sum!", e.what());
  }
}

TEST(MatrixTest, OperatorMinus) {
  S21Matrix a(3, 2);
  a(0, 0) = 1.0, a(0, 1) = 4.0;
  a(1, 0) = 2.0, a(1, 1) = 5.0;
  a(2, 0) = 3.0, a(2, 1) = 6.0;
  S21Matrix b(3, 2);
  b(0, 0) = 1.0, b(0, 1) = 4.0;
  b(1, 0) = 2.0, b(1, 1) = 5.0;
  b(2, 0) = 3.0, b(2, 1) = 6.0;
  S21Matrix eq(3, 2);
  eq(0, 0) = 0, eq(0, 1) = 0;
  eq(1, 0) = 0, eq(1, 1) = 0;
  eq(2, 0) = 0, eq(2, 1) = 0;
  S21Matrix res = a - b;

  EXPECT_TRUE(res.EqMatrix(eq));
}

TEST(MatrixTest, OperatorMinusDifferentSize) {
  S21Matrix a(3, 2);
  a(0, 0) = 1.0, a(0, 1) = 4.0;
  a(1, 0) = 2.0, a(1, 1) = 5.0;
  a(2, 0) = 3.0, a(2, 1) = 6.0;
  S21Matrix b(2, 2);
  b(0, 0) = 1.0, b(0, 1) = 4.0;
  b(1, 0) = 2.0, b(1, 1) = 5.0;

  try {
    S21Matrix res = a - b;
  } catch (std::out_of_range& e) {
    EXPECT_STREQ("Is different size matrix to sub!", e.what());
  }
}

TEST(MatrixTest, OperatorMulNumber) {
  S21Matrix a(3, 2);
  a(0, 0) = 1.0, a(0, 1) = 4.0;
  a(1, 0) = 2.0, a(1, 1) = 5.0;
  a(2, 0) = 3.0, a(2, 1) = 6.0;
  double num = 2.0;

  S21Matrix eq(3, 2);
  eq(0, 0) = 2.0, eq(0, 1) = 8.0;
  eq(1, 0) = 4.0, eq(1, 1) = 10.0;
  eq(2, 0) = 6.0, eq(2, 1) = 12.0;

  S21Matrix result;
  result = a * num;
  EXPECT_TRUE(result.EqMatrix(eq));
}

TEST(MatrixTest, OperatorMulNumberFriend) {
  S21Matrix a(3, 2);
  a(0, 0) = 1.0, a(0, 1) = 4.0;
  a(1, 0) = 2.0, a(1, 1) = 5.0;
  a(2, 0) = 3.0, a(2, 1) = 6.0;
  double num = 2.0;

  S21Matrix eq(3, 2);
  eq(0, 0) = 2.0, eq(0, 1) = 8.0;
  eq(1, 0) = 4.0, eq(1, 1) = 10.0;
  eq(2, 0) = 6.0, eq(2, 1) = 12.0;

  S21Matrix result;
  result = num * a;
  EXPECT_TRUE(result.EqMatrix(eq));
}

TEST(MatrixTest, OperatorMulMatrix) {
  S21Matrix a(3, 2);
  a(0, 0) = 1.0, a(0, 1) = 4.0;
  a(1, 0) = 2.0, a(1, 1) = 5.0;
  a(2, 0) = 3.0, a(2, 1) = 6.0;

  S21Matrix b(2, 3);
  b(0, 0) = 1.0, b(0, 1) = -1., b(0, 2) = 1;
  b(1, 0) = 2.0, b(1, 1) = 3.0, b(1, 2) = 4.0;

  S21Matrix eq(3, 3);
  eq(0, 0) = 9, eq(0, 1) = 11, eq(0, 2) = 17;
  eq(1, 0) = 12, eq(1, 1) = 13, eq(1, 2) = 22;
  eq(2, 0) = 15, eq(2, 1) = 15, eq(2, 2) = 27;

  S21Matrix result = a * b;
  EXPECT_TRUE(result.EqMatrix(eq));
}

TEST(MatrixTest, OperatorEqMatrixDifferentLessAccuracy) {
  S21Matrix matrix1;
  S21Matrix matrix2;
  matrix1(0, 0) = 1.00000001;
  matrix2(0, 0) = 1.;
  EXPECT_TRUE(matrix1 == matrix2);
}

TEST(MatrixTest, OperatorEq) {
  S21Matrix a(3, 2);
  a(0, 0) = 1.0, a(0, 1) = 4.0;
  a(1, 0) = 2.0, a(1, 1) = 5.0;
  a(2, 0) = 3.0, a(2, 1) = 6.0;
  a = a;
  S21Matrix b = a;

  S21Matrix eq(3, 2);
  eq(0, 0) = 1.0, eq(0, 1) = 4.0;
  eq(1, 0) = 2.0, eq(1, 1) = 5.0;
  eq(2, 0) = 3.0, eq(2, 1) = 6.0;

  EXPECT_TRUE(b.EqMatrix(eq));
}

TEST(MatrixTest, OperatorPlusEq) {
  S21Matrix a(3, 2);
  a(0, 0) = 1.0, a(0, 1) = 4.0;
  a(1, 0) = 2.0, a(1, 1) = 5.0;
  a(2, 0) = 3.0, a(2, 1) = 6.0;

  S21Matrix b(3, 2);
  b(0, 0) = 1.0, b(0, 1) = 4.0;
  b(1, 0) = 2.0, b(1, 1) = 5.0;
  b(2, 0) = 3.0, b(2, 1) = 6.0;

  S21Matrix eq(3, 2);
  eq(0, 0) = 2.0, eq(0, 1) = 8.0;
  eq(1, 0) = 4.0, eq(1, 1) = 10.0;
  eq(2, 0) = 6.0, eq(2, 1) = 12.0;

  EXPECT_TRUE(eq.EqMatrix(b += a));
}

TEST(MatrixTest, OperatorMinusEq) {
  S21Matrix a(3, 2);
  a(0, 0) = 1.0, a(0, 1) = 4.0;
  a(1, 0) = 2.0, a(1, 1) = 5.0;
  a(2, 0) = 3.0, a(2, 1) = 6.0;

  S21Matrix b(3, 2);
  b(0, 0) = 1.0, b(0, 1) = 4.0;
  b(1, 0) = 2.0, b(1, 1) = 5.0;
  b(2, 0) = 3.0, b(2, 1) = 6.0;

  S21Matrix eq(3, 2);
  eq(0, 0) = 0, eq(0, 1) = 0;
  eq(1, 0) = 0, eq(1, 1) = 0;
  eq(2, 0) = 0, eq(2, 1) = 0;

  EXPECT_TRUE(eq.EqMatrix(b -= a));
}

TEST(MatrixTest, OperatorMulMatrixEq) {
  S21Matrix a(3, 2);
  a(0, 0) = 1.0, a(0, 1) = 4.0;
  a(1, 0) = 2.0, a(1, 1) = 5.0;
  a(2, 0) = 3.0, a(2, 1) = 6.0;

  S21Matrix b(2, 3);
  b(0, 0) = 1.0, b(0, 1) = -1., b(0, 2) = 1;
  b(1, 0) = 2.0, b(1, 1) = 3.0, b(1, 2) = 4.0;

  S21Matrix eq(3, 3);
  eq(0, 0) = 9, eq(0, 1) = 11, eq(0, 2) = 17;
  eq(1, 0) = 12, eq(1, 1) = 13, eq(1, 2) = 22;
  eq(2, 0) = 15, eq(2, 1) = 15, eq(2, 2) = 27;

  EXPECT_TRUE(eq.EqMatrix(a *= b));
}

TEST(MatrixTest, OperatorMulNumberEQ) {
  S21Matrix a(3, 2);
  a(0, 0) = 1.0, a(0, 1) = 4.0;
  a(1, 0) = 2.0, a(1, 1) = 5.0;
  a(2, 0) = 3.0, a(2, 1) = 6.0;
  double num = 2.0;

  S21Matrix eq(3, 2);
  eq(0, 0) = 2.0, eq(0, 1) = 8.0;
  eq(1, 0) = 4.0, eq(1, 1) = 10.0;
  eq(2, 0) = 6.0, eq(2, 1) = 12.0;

  EXPECT_TRUE(eq.EqMatrix(a *= num));
}

TEST(MatrixTest, OperatorParenthesis) {
  S21Matrix const a(3, 2);
  a(0, 0) = 1.0, a(0, 1) = 4.0;
  a(1, 0) = 2.0, a(1, 1) = 5.0;
  a(2, 0) = 3.0, a(2, 1) = 6.0;

  EXPECT_TRUE(a(0, 0));
  try {
    a(3, 3);
  } catch (std::out_of_range& e) {
    EXPECT_STREQ("Index is out of range!", e.what());
  }
  try {
    a(3, -33);
  } catch (std::out_of_range& e) {
    EXPECT_STREQ("Index is out of range!", e.what());
  }
  try {
    a(-3, 2);
  } catch (std::out_of_range& e) {
    EXPECT_STREQ("Index is out of range!", e.what());
  }
  try {
    a(33, 2);
  } catch (std::out_of_range& e) {
    EXPECT_STREQ("Index is out of range!", e.what());
  }
}

TEST(MatrixTest, OperatorParenthesisThrow) {
  S21Matrix a(3, 2);

  try {
    a(3, 3) = 10;
  } catch (std::out_of_range& e) {
    EXPECT_STREQ("Index is out of range!", e.what());
  }
  try {
    a(3, -33) = 1;
  } catch (std::out_of_range& e) {
    EXPECT_STREQ("Index is out of range!", e.what());
  }
  try {
    a(-3, 2) = 1;
  } catch (std::out_of_range& e) {
    EXPECT_STREQ("Index is out of range!", e.what());
  }
  try {
    a(33, 2) = 1;
  } catch (std::out_of_range& e) {
    EXPECT_STREQ("Index is out of range!", e.what());
  }
}

TEST(MatrixTest, SetRowsGetRows) {
  S21Matrix a(3, 2);
  a(0, 0) = 1.0, a(0, 1) = 4.0;
  a(1, 0) = 2.0, a(1, 1) = 5.0;
  a(2, 0) = 3.0, a(2, 1) = 6.0;
  a.SetRows(20);
  EXPECT_EQ(a.GetRows(), 20);
  a.SetRows(2);
  EXPECT_EQ(a.GetRows(), 2);
}

TEST(MatrixTest, SetRowsThrow) {
  S21Matrix a(3, 2);
  try {
    a.SetRows(0);
  } catch (std::out_of_range& e) {
    EXPECT_STREQ("Rows cannot be less 1", e.what());
  }
}

TEST(MatrixTest, SetColsGetCols) {
  S21Matrix a(3, 2);
  a(0, 0) = 1.0, a(0, 1) = 4.0;
  a(1, 0) = 2.0, a(1, 1) = 5.0;
  a(2, 0) = 3.0, a(2, 1) = 6.0;
  a.SetCols(20);
  EXPECT_EQ(a.GetCols(), 20);
  a.SetCols(2);
  EXPECT_EQ(a.GetCols(), 2);
}

TEST(MatrixTest, SetColsThrow) {
  S21Matrix a(3, 2);
  try {
    a.SetCols(0);
  } catch (std::out_of_range& e) {
    EXPECT_STREQ("Columns cannot be less than 1", e.what());
  }
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
