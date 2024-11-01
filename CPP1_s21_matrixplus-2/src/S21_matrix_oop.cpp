#include "s21_matrix_oop.h"

// Default constructor
S21Matrix::S21Matrix() : rows_(2), cols_(2) {
  matrix_ = new double *[rows_]();
  // выделяем память под double
  for (int i = 0; i < rows_; i++) (matrix_[i]) = new double[cols_]();
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; ++j) matrix_[i][j] = 0.0;
  }
}

// parameterized constructor
S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows <= 0 || cols <= 0) {
    throw std::invalid_argument(
        "CreationError: The number of rows or cols cannot be less than 1");
  }
  matrix_ = new double *[rows_]();
  // выделяем память под double
  for (int i = 0; i < rows_; i++) (matrix_[i]) = new double[cols_]();
}

// copy constructor
S21Matrix::S21Matrix(const S21Matrix &other)
    : rows_(other.rows_), cols_(other.cols_) {
  matrix_ = new double *[rows_]();
  // выделяем память под double
  for (int i = 0; i < rows_; i++) (matrix_[i]) = new double[cols_]();
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; ++j) matrix_[i][j] = other.matrix_[i][j];
  }
}

// move constructor
S21Matrix::S21Matrix(S21Matrix &&o) noexcept
    : rows_(o.rows_), cols_(o.cols_), matrix_(o.matrix_) {
  o.matrix_ = nullptr;
  o.rows_ = 0;
  o.cols_ = 0;
}

// destructor
S21Matrix::~S21Matrix() noexcept {
  for (int i = 0; i < rows_; i++) delete[] matrix_[i];
  delete[] matrix_;
  rows_ = 0;
  cols_ = 0;
  matrix_ = nullptr;
}

// Main functions
// сравнение
bool S21Matrix::EqMatrix(const S21Matrix &other) const noexcept {
  bool res = false;
  if (rows_ == other.rows_ && cols_ == other.cols_) {
    res = true;
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        if (fabs(matrix_[i][j] - other.matrix_[i][j]) > eq_accuracy) {
          res = false;
        }
      }
    }
  }
  return res;
}

// сложение
void S21Matrix::SumMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::out_of_range("Is different size matrix to sum!");
  }

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) matrix_[i][j] += other.matrix_[i][j];
  }
}

// вычитание
void S21Matrix::SubMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::out_of_range("Is different size matrix to sub!");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) matrix_[i][j] -= other.matrix_[i][j];
  }
}

// умножение на число
void S21Matrix::MulNumber(const double num) noexcept {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) matrix_[i][j] = matrix_[i][j] * num;
  }
}

// умножение двух матриц
void S21Matrix::MulMatrix(const S21Matrix &other) {
  if (rows_ == other.cols_) {
    S21Matrix res(rows_, other.cols_);
    for (int i = 0; i < res.rows_; i++) {
      for (int j = 0; j < res.cols_; j++) {
        for (int k = 0; k < cols_; k++)
          res.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }

    *this = std::move(res);
  } else {
    throw std::out_of_range("Wrong MulMatrix: rowsA != colsB");
  }
}

// транспонирование
S21Matrix S21Matrix::Transpose() const {
  S21Matrix res(cols_, rows_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) res.matrix_[j][i] = matrix_[i][j];
  }
  return res;
}

// + вычисление матрицы алгебраических дополнений
S21Matrix S21Matrix::CalcComplements() const {
  if (rows_ != cols_) {
    throw std::out_of_range("The matrix for CalcComplements must be square");
  }
  S21Matrix result(rows_, cols_);
  if (rows_ <= 1) {
    result(0, 0) = 1.;
  } else {
    S21Matrix temp_determinant(rows_ - 1, cols_ - 1);

    for (int m = 0; m < rows_ && rows_ > 1; m++) {
      for (int n = 0; n < cols_; n++) {
        this->_get_determinant_matrix(temp_determinant, m, n);
        result(m, n) = temp_determinant.Determinant();
      }
    }

    for (int m = 0; m < rows_; m++) {
      for (int n = 0; n < cols_; n++) result.matrix_[m][n] *= pow(-1, (m + n));
    }
  }
  return result;
}

// вычисление определителя
double S21Matrix::Determinant() const {
  if (rows_ != cols_) {
    throw std::out_of_range("The matrix for Determinant must be square");
  }
  double *copy_row = new double[cols_]();
  double result = 1.;
  //создание временной матрицы и копия в нее исходной
  S21Matrix temp(*this);
  int find_not_zero = 0, all_zero = 1, znak = 1;
  for (int i = 0; i < temp.rows_ - 1 && result; i++) {
    // находим не нулевой элемент
    for (find_not_zero = i, all_zero = 1; find_not_zero < temp.rows_;
         find_not_zero += 1) {
      if (temp.matrix_[find_not_zero][i]) {
        for (int c = 0; c < temp.cols_; c++) {
          copy_row[c] = temp.matrix_[find_not_zero][c];
        }
        all_zero = 0;
        break;
      }
    }
    // убираем ноль из диагонали
    if (temp.matrix_[i][i] == 0. && !all_zero) {
      for (int c = 0; c < temp.cols_; c++) {
        temp.matrix_[find_not_zero][c] = temp.matrix_[i][c];
      }
      for (int c = 0; c < temp.cols_; c++) {
        temp.matrix_[i][c] = copy_row[c];
      }
      znak *= -1;
    }
    // если все нули то det = 0
    if (all_zero) {
      result = 0.;
    } else {
      for (int t = i + 1; t < temp.rows_; t++) {
        double temp_mult = temp.matrix_[t][i] / temp.matrix_[i][i];
        for (int k = i; k < temp.cols_; k++)
          temp.matrix_[t][k] -= temp.matrix_[i][k] * temp_mult;
      }
    }
  }
  for (int m = 0; m < this->rows_; m++) result *= temp.matrix_[m][m];
  result = result ? (result * znak) : result;
  delete[] copy_row;
  return result;
}

// поиск обратной матрицы
S21Matrix S21Matrix::InverseMatrix() const {
  double d = 0;
  d = this->Determinant();
  if (!d) {
    throw std::logic_error(
        "Error Calculate InverseMatrix - Determinant is null");
  }
  S21Matrix c = this->CalcComplements();
  c.MulNumber(1 / d);
  return c.Transpose();
}

// operators overloads
// Сложение двух матриц.
S21Matrix S21Matrix::operator+(const S21Matrix &other) const {
  S21Matrix result = *this;
  result.SumMatrix(other);
  return result;
}

// Вычитание
S21Matrix S21Matrix::operator-(const S21Matrix &other) const {
  S21Matrix result = *this;
  result.SubMatrix(other);
  return result;
}

// Умножение матриц.
S21Matrix S21Matrix::operator*(const S21Matrix &other) const {
  S21Matrix result = *this;
  result.MulMatrix(other);
  return result;
}

// Умножение на число.
S21Matrix S21Matrix::operator*(const double num) noexcept {
  S21Matrix result = *this;
  result.MulNumber(num);
  return result;
}
// Умножение числа.
S21Matrix operator*(const double num, const S21Matrix &matrix) {
  S21Matrix result = matrix;
  result.MulNumber(num);
  return result;
}

//(EqMatrix).
bool S21Matrix::operator==(const S21Matrix &other) const noexcept {
  return EqMatrix(other);
}

// Присвоение значений.
S21Matrix &S21Matrix::operator=(const S21Matrix &other) {
  if (this != &other) {
    this->~S21Matrix();
    rows_ = other.rows_;
    cols_ = other.cols_;

    matrix_ = new double *[rows_];
    for (int i = 0; i < rows_; i++) {
      matrix_[i] = new double[cols_];
      for (int j = 0; j < cols_; j++) matrix_[i][j] = other.matrix_[i][j];
    }
  }
  return *this;
}

// Присвоение сложения.
S21Matrix &S21Matrix::operator+=(const S21Matrix &other) {
  SumMatrix(other);
  return *this;
}

// Присвоение разности.
S21Matrix &S21Matrix::operator-=(const S21Matrix &other) {
  SubMatrix(other);
  return *this;
}

//Присвоение умножения.
S21Matrix &S21Matrix::operator*=(const S21Matrix &other) {
  MulMatrix(other);
  return *this;
}

//Присвоение умножения.
S21Matrix &S21Matrix::operator*=(const double num) noexcept {
  MulNumber(num);
  return *this;
}

// Индексация по элементам.
double &S21Matrix::operator()(int row, int col) const {
  if (row < 0 || row >= rows_ || col < 0 || col >= cols_) {
    throw std::out_of_range("Index is out of range!");
  }
  return matrix_[row][col];
}

double &S21Matrix::operator()(int row, int col) {
  if (row < 0 || row >= rows_ || col < 0 || col >= cols_) {
    throw std::out_of_range("Index is out of range!");
  }
  return matrix_[row][col];
}

// Setters, getters (accessor и mutator).
int S21Matrix::GetRows() const noexcept { return rows_; }

int S21Matrix::GetCols() const noexcept { return cols_; }

void S21Matrix::SetRows(int rows) {
  if (rows < 1) {
    throw std::out_of_range("Rows cannot be less 1");
  }
  if (rows_ != rows) {
    S21Matrix temp(rows, cols_);
    int minRow = std::min(rows_, rows);
    for (int i = 0; i < minRow; i++) {
      for (int j = 0; j < cols_; j++) temp.matrix_[i][j] = matrix_[i][j];
    }

    for (int i = minRow; i < rows; i++) {
      for (int j = 0; j < cols_; j++) temp(i, j) = 0.;
    }
    *this = std::move(temp);
  }
}

void S21Matrix::SetCols(int cols) {
  if (cols < 1) {
    throw std::out_of_range("Columns cannot be less than 1");
  }
  if (cols != cols_) {
    S21Matrix temp(rows_, cols);
    int minCol = std::min(cols_, cols);
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < minCol; j++) temp.matrix_[i][j] = matrix_[i][j];
    }

    for (int i = 0; i < rows_; i++) {
      for (int j = minCol; j < cols; j++) temp(i, j) = 0.;
    }
    *this = std::move(temp);
  }
}

// additional functions
void S21Matrix::_get_determinant_matrix(const S21Matrix &temp_determinant,
                                        int m, int n) const {
  for (int rA = 0, rD = 0; rA < rows_; rA++) {
    for (int cA = 0, cD = 0; cA < cols_; cA++) {
      if (rA != m && cA != n) {
        temp_determinant.matrix_[rD][cD] = matrix_[rA][cA];
        cD++;

        if (cD == temp_determinant.cols_) {
          rD++;
          cD = 0;
        }
      }
    }
  }
}
