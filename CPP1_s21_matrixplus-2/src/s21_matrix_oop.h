#ifndef CPP1_S21_MATRIXPLUS_SRC_S21_MATRIX_OOP_H_
#define CPP1_S21_MATRIXPLUS_SRC_S21_MATRIX_OOP_H_

#include <cmath>
#include <cstring>
#include <iostream>

class S21Matrix final {
 private:
  int rows_, cols_;  // Rows and columns
  double **matrix_;  // Pointer to the memory where the matrix is allocated
  static constexpr double eq_accuracy = 1e-7;  //
  void _get_determinant_matrix(const S21Matrix &temp_determinant, int m,
                               int n) const;

 public:
  S21Matrix();                            // Default constructor
  S21Matrix(int rows, int cols);          // parameterized constructor
  S21Matrix(const S21Matrix &other);      // copy constructor
  S21Matrix(S21Matrix &&other) noexcept;  // move constructor
  ~S21Matrix() noexcept;                  // Destructor

  // Main functions
  bool EqMatrix(const S21Matrix &other) const noexcept;  // сравнение
  void SumMatrix(const S21Matrix &other);                // сложение
  void SubMatrix(const S21Matrix &other);                // вычитание
  void MulNumber(const double num) noexcept;  // умножение на число
  void MulMatrix(const S21Matrix &other);  // умножение двух матриц
  S21Matrix Transpose() const;             // транспонирование
  // + вычисление матрицы алгебраических дополнений
  S21Matrix CalcComplements() const;
  double Determinant() const;  // вычисление определителя
  S21Matrix InverseMatrix() const;  // поиск обратной матрицы

  // operators overloads
  S21Matrix operator+(const S21Matrix &other) const;  // Сложение двух матриц.
  S21Matrix operator-(const S21Matrix &other) const;  // Вычитание
  S21Matrix operator*(const S21Matrix &other) const;  // Умножение матриц.

  S21Matrix operator*(const double num) noexcept;  // Умножение на число.
  friend S21Matrix operator*(const double num, const S21Matrix &matrix);

  bool operator==(const S21Matrix &other) const noexcept;  //(EqMatrix).
  S21Matrix &operator=(const S21Matrix &other);  // Присвоение значений.
  S21Matrix &operator+=(const S21Matrix &other);  // Присвоение сложения.
  S21Matrix &operator-=(const S21Matrix &other);  // Присвоение разности.
  S21Matrix &operator*=(const S21Matrix &other);  //Присвоение умножения.
  S21Matrix &operator*=(const double num) noexcept;  // Присвоение умножения.
  double &operator()(int row, int col) const;  // Индексация по элементам.
  double &operator()(int row, int col);

  // Setters, getters (accessor и mutator).
  int GetRows() const noexcept;
  int GetCols() const noexcept;
  void SetRows(int rows);
  void SetCols(int cols);
};

#endif /* CPP1_S21_MATRIXPLUS_SRC_S21_MATRIX_OOP_H_ */