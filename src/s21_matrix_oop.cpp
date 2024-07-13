#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() : row_(0), cols_(0), matrix_(nullptr) {}

S21Matrix::S21Matrix(int rows, int cols) {
  if (rows < 0 || cols < 0) throw ::logic_error("Invalid values");
  this->createMatrix(rows, cols);
}

S21Matrix::S21Matrix(const S21Matrix& other) {
  this->createMatrix(other.row_, other.cols_);
  for (int i = 0; i < this->row_; i++)
    for (int j = 0; j < this->cols_; j++)
      this->matrix_[i][j] = other.matrix_[i][j];
}

S21Matrix::S21Matrix(S21Matrix&& other) {
  if (!other.isValid()) throw ::logic_error("Invalid matrix");
  this->row_ = other.row_;
  this->cols_ = other.cols_;
  this->matrix_ = other.matrix_;
  other.row_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
}

S21Matrix::~S21Matrix() { this->freeMatrix(); }

void S21Matrix::freeMatrix() {
  for (int i = 0; i < this->row_; i++) delete[] this->matrix_[i];
  delete[] matrix_;
  this->row_ = 0;
  this->cols_ = 0;
  this->matrix_ = nullptr;
}

void S21Matrix::createMatrix(int rows, int cols) {
  this->row_ = rows;
  this->cols_ = cols;
  this->matrix_ = new double*[this->row_]();
  for (int i = 0; i < this->row_; i++)
    this->matrix_[i] = new double[this->cols_]();
}

int S21Matrix::getRows() const { return this->row_; }

int S21Matrix::getCols() const { return this->cols_; }

double** S21Matrix::getMatrix() const { return this->matrix_; }

double S21Matrix::getVal(int row, int col) const {
  return this->matrix_[row][col];
}

void S21Matrix::setRows(int rows) {
  if (rows < 0) throw ::logic_error("Invalid rows value!");
  if (this->row_ != rows) {
    S21Matrix temp(rows, this->cols_);
    for (int i = 0; i < std::min(this->row_, rows); i++)
      for (int j = 0; j < temp.cols_; j++)
        temp.matrix_[i][j] = this->matrix_[i][j];
    *this = temp;
  }
}

void S21Matrix::setCols(int cols) {
  if (cols < 0) throw ::logic_error("Invalid cols value!");
  if (this->cols_ != cols) {
    S21Matrix temp(this->row_, cols);
    for (int i = 0; i < temp.row_; i++)
      for (int j = 0; j < std::min(this->cols_, cols); j++)
        temp.matrix_[i][j] = this->matrix_[i][j];
    *this = temp;
  }
}

void S21Matrix::setVal(int row, int col, double val) {
  this->matrix_[row][col] = val;
}

bool S21Matrix::isValid() const { return this->matrix_ != nullptr; }

bool S21Matrix::EqMatrix(const S21Matrix& other) {
  bool result = true;
  if (this->row_ != other.row_ || this->cols_ != other.cols_ ||
      !this->isValid() || !other.isValid())
    result = false;
  else
    for (int i = 0; i < this->row_; i++)
      for (int j = 0; j < this->cols_; j++)
        if (this->matrix_[i][j] != other.matrix_[i][j]) {
          result = false;
          i = this->row_;
          break;
        }
  return result;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (!other.isValid() || !this->isValid())
    throw ::logic_error("Invalid matrix");
  if (this->row_ != other.row_ || this->cols_ != other.cols_)
    throw ::logic_error("Incorrect matrix");
  else
    for (int i = 0; i < this->row_; i++)
      for (int j = 0; j < this->cols_; j++)
        this->matrix_[i][j] += other.matrix_[i][j];
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (!other.isValid() || !this->isValid())
    throw ::logic_error("Invalid matrix");
  if (this->row_ != other.row_ || this->cols_ != other.cols_)
    throw ::logic_error("Incorrect matrix");
  else
    for (int i = 0; i < this->row_; i++)
      for (int j = 0; j < this->cols_; j++)
        this->matrix_[i][j] -= other.matrix_[i][j];
}

void S21Matrix::MulNumber(const double num) {
  if (!this->isValid()) throw ::logic_error("Invalid matrix");
  for (int i = 0; i < this->row_; i++)
    for (int j = 0; j < this->cols_; j++) this->matrix_[i][j] *= num;
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (!other.isValid() || !this->isValid())
    throw ::logic_error("Invalid matrix");
  if (this->cols_ != other.row_)
    throw ::logic_error("Incorrect matrix");
  else {
    S21Matrix temp(this->row_, other.cols_);
    for (int i = 0; i < temp.row_; i++)
      for (int j = 0; j < temp.cols_; j++) {
        int temp_value = 0;
        for (int k = 0; k < other.row_; k++)
          temp_value += this->matrix_[i][k] * other.matrix_[k][j];
        temp.matrix_[i][j] = temp_value;
      }
    *this = temp;
  }
}

S21Matrix S21Matrix::Transpose() {
  if (!this->isValid()) throw ::logic_error("Invalid matrix");
  S21Matrix result(this->cols_, this->row_);
  for (int i = 0; i < result.row_; i++)
    for (int j = 0; j < result.cols_; j++)
      result.matrix_[i][j] = this->matrix_[j][i];
  return result;
}

S21Matrix S21Matrix::CalcComplements() {
  if (!this->isValid()) throw ::logic_error("Invalid matrix");
  S21Matrix result(this->row_, this->cols_);
  if (this->row_ != this->cols_) throw ::logic_error("Incorrect matrix");
  if (this->row_ == 1)
    result.matrix_[0][0] = 1;
  else {
    for (int i = 0; i < this->row_; i++) {
      for (int j = 0; j < this->cols_; j++) {
        S21Matrix Minor = this->Minor(i, j);
        if (Minor.matrix_ != nullptr) {
          int sign = (i + j) % 2 == 0 ? 1 : -1;
          double det = Minor.Determinant();
          result.matrix_[i][j] = sign * det;
        }
      }
    }
  }
  return result;
}

double S21Matrix::Determinant() {
  if (!this->isValid()) throw ::logic_error("Invalid matrix");
  double result = 0;
  if (this->row_ != this->cols_) throw ::logic_error("Incorrect matrix");
  if (this->row_ == 1) {
    result = this->matrix_[0][0];
  } else if (this->row_ == 2) {
    result = this->matrix_[0][0] * this->matrix_[1][1] -
             this->matrix_[1][0] * this->matrix_[0][1];
  } else if (this->row_ > 2) {
    for (int i = 0; i < this->cols_; i++) {
      S21Matrix Minor = this->Minor(0, i);
      if (Minor.matrix_ != nullptr) {
        int sign = i % 2 == 0 ? 1 : -1;
        result += sign * this->matrix_[0][i] * Minor.Determinant();
      }
    }
  }
  return result;
}

S21Matrix S21Matrix::InverseMatrix() {
  if (!this->isValid() || this->row_ <= 0 || this->cols_ <= 0)
    throw ::logic_error("Invalid matrix");
  if (this->row_ != this->cols_) throw ::logic_error("Incorrect matrix");
  double det = this->Determinant();
  if (det == 0) throw ::logic_error("Invalid determinant");
  S21Matrix result;
  if (this->row_ == 1) {
    result = S21Matrix(1, 1);
    result.matrix_[0][0] = 1 / this->matrix_[0][0];
  } else {
    result = this->CalcComplements();
    result = result.Transpose();
    for (int i = 0; i < result.row_; i++)
      for (int j = 0; j < result.cols_; j++) result.matrix_[i][j] /= det;
  }
  return result;
}

S21Matrix S21Matrix::Minor(int row, int column) {
  if (!this->isValid()) throw ::logic_error("Invalid matrix");
  S21Matrix result(this->row_ - 1, this->cols_ - 1);
  int minor_row = 0;
  for (int i = 0; i < this->row_; i++) {
    if (i != row) {
      int minor_column = 0;
      for (int j = 0; j < this->cols_; j++) {
        if (j != column) {
          result.matrix_[minor_row][minor_column] = this->matrix_[i][j];
          minor_column++;
        }
      }
      minor_row++;
    }
  }
  return result;
}

S21Matrix operator+(const S21Matrix& value_1, const S21Matrix& value_2) {
  if (!value_1.isValid() || !value_2.isValid())
    throw ::logic_error("Invalid matrix");
  S21Matrix result;
  if (value_1.getRows() != value_2.getRows() ||
      value_1.getCols() != value_2.getCols())
    throw ::logic_error("Incorrect matrix");
  else {
    result = value_1;
    result += value_2;
  }
  return result;
}

S21Matrix operator-(const S21Matrix& value_1, const S21Matrix& value_2) {
  if (!value_1.isValid() || !value_2.isValid())
    throw ::logic_error("Invalid matrix");
  S21Matrix result;
  if (value_1.getRows() != value_2.getRows() ||
      value_1.getCols() != value_2.getCols())
    throw ::logic_error("Incorrect matrix");
  else {
    result = value_1;
    result -= value_2;
  }
  return result;
}

S21Matrix operator*(const S21Matrix& value_1, const S21Matrix& value_2) {
  if (!value_1.isValid() || !value_2.isValid())
    throw ::logic_error("Invalid matrix");
  S21Matrix result;
  if (value_1.getCols() != value_2.getRows())
    throw ::logic_error("Incorrect matrix");
  else {
    result = value_1;
    result *= value_2;
  }
  return result;
}

S21Matrix operator*(const S21Matrix& value_1, const double num) {
  if (!value_1.isValid()) throw ::logic_error("Invalid matrix");
  S21Matrix result = value_1;
  result *= num;
  return result;
}

bool operator==(const S21Matrix& value_1, const S21Matrix& value_2) {
  if (!value_1.isValid() || !value_2.isValid())
    throw ::logic_error("Invalid matrix");
  S21Matrix temp = value_1;
  return temp.EqMatrix(value_2);
}

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  if (!other.isValid()) throw ::logic_error("Invalid matrix!");
  this->freeMatrix();
  this->createMatrix(other.row_, other.cols_);
  for (int i = 0; i < this->row_; i++)
    for (int j = 0; j < this->cols_; j++)
      this->matrix_[i][j] = other.matrix_[i][j];
  return *this;
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
  if (!this->isValid() || !other.isValid())
    throw ::logic_error("Invalid matrix!");
  if (this->getRows() != other.getRows() || this->getCols() != other.getCols())
    throw ::logic_error("Incorrect matrix!");
  this->SumMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
  if (!this->isValid() || !other.isValid())
    throw ::logic_error("Invalid matrix!");
  if (this->getRows() != other.getRows() || this->getCols() != other.getCols())
    throw ::logic_error("Incorrect matrix!");
  this->SubMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
  if (!this->isValid() || !other.isValid())
    throw ::logic_error("Invalid matrix!");
  if (this->getCols() != other.getRows())
    throw ::logic_error("Incorrect matrix!");
  this->MulMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator*=(const double num) {
  if (!this->isValid()) throw ::logic_error("Invalid matrix!");
  this->MulNumber(num);
  return *this;
}

double S21Matrix::operator()(int i, int j) {
  if (!this->isValid()) throw ::logic_error("Invalid matrix!");
  if ((i >= this->getRows() || i < 0) || (j >= this->getCols() || j < 0))
    throw ::logic_error("Out of range matrix!");
  return this->matrix_[i][j];
}