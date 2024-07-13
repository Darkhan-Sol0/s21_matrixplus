#ifndef MATRIX_PLUS_HPP
#define MATRIX_PLUS_HPP

#include <algorithm>
#include <cmath>
#include <iostream>

using namespace std;

class S21Matrix {
 private:
  int row_, cols_;
  double** matrix_;

 public:
  S21Matrix();  // Инициализация матрицы
  S21Matrix(int rows, int cols);  // Параметризированный конструктор с
                                  // количеством строк и столбцов.
  S21Matrix(const S21Matrix& other);  // Конструктор копирования.
  S21Matrix(S21Matrix&& other);  // Конструктор переноса.
  ~S21Matrix();                  // Деструктор

  bool EqMatrix(const S21Matrix& other);  // Проверка равенства
  void SumMatrix(const S21Matrix& other);  // Сложение матрицы
  void SubMatrix(const S21Matrix& other);  // Вычитание матрицы
  void MulNumber(const double num);  // Умножение матрицы на число
  void MulMatrix(const S21Matrix& other);  // Умножения матрицы
  S21Matrix Transpose();  // Создает новую матрицу трансонирует и возвращает ее
  S21Matrix CalcComplements();  // возвращает матрицу алгебраического дополнения
  double Determinant();         // Определитель матрицы
  S21Matrix InverseMatrix();    // Обратная матрица

  S21Matrix Minor(int row, int column);  // minor

  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix& operator*=(const S21Matrix& other);
  S21Matrix& operator*=(const double num);
  double operator()(int i, int j);
  S21Matrix& operator=(const S21Matrix& other);

  int getRows() const;
  int getCols() const;
  double** getMatrix() const;
  double getVal(int row, int col) const;
  bool isValid() const;

  void freeMatrix();
  void createMatrix(int rows, int cols);

  void setRows(int rows);
  void setCols(int cols);
  void setVal(int row, int col, double val);
};

S21Matrix operator+(const S21Matrix& left, const S21Matrix& right);
S21Matrix operator-(const S21Matrix& left, const S21Matrix& right);
S21Matrix operator*(const S21Matrix& left, const S21Matrix& right);
S21Matrix operator*(const S21Matrix& left, const double num);
bool operator==(const S21Matrix& left, const S21Matrix& right);

#endif /* MATRIX_PLUS_HPP */