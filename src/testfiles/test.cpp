#include "test.h"

TEST(MatrixTest, Defaut_func_0) {
  S21Matrix mat;
  ASSERT_EQ(mat.getRows(), 0);
  ASSERT_EQ(mat.getCols(), 0);
  ASSERT_EQ(mat.getMatrix(), nullptr);
}

TEST(MatrixTest, Defaut_func_1) {
  S21Matrix mat(3, 3);
  ASSERT_EQ(mat.getRows(), 3);
  ASSERT_EQ(mat.getCols(), 3);
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      ASSERT_EQ(mat.getVal(i, j), 0.0);
}

TEST(MatrixTest, Defaut_func_2) {
  S21Matrix mat(3, 3);
  mat.freeMatrix();
  ASSERT_EQ(mat.getRows(), 0);
  ASSERT_EQ(mat.getCols(), 0);
  ASSERT_EQ(mat.getMatrix(), nullptr);
}

TEST(MatrixTest, Defaut_func_3) {
  S21Matrix mat(3, 3);
  double val = 0;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      mat.setVal(i, j, val++);
  S21Matrix mat2(mat);
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      ASSERT_EQ(mat2.getVal(i, j), mat.getVal(i, j));
}

TEST(MatrixTest, Defaut_func_4) {
  S21Matrix mat(3, 3);
  double val = 0;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      mat.setVal(i, j, val++);
  S21Matrix mat2(std::move(mat));
  val = 0;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      ASSERT_EQ(mat2.getVal(i, j), val++);
}

TEST(MatrixTest, Defaut_func_5) {
  S21Matrix mat(3, 3);
  mat.setRows(5);
  mat.setCols(5);
  ASSERT_EQ(mat.getRows(), 5);
  ASSERT_EQ(mat.getCols(), 5);
  mat.setRows(1);
  mat.setCols(1);
  ASSERT_EQ(mat.getRows(), 1);
  ASSERT_EQ(mat.getCols(), 1);
}

TEST(MatrixTest, Eq_func_0) {
  S21Matrix mat(3, 3);
  S21Matrix mat2(3, 3);
  ASSERT_EQ(mat.EqMatrix(mat2), 1);
}

TEST(MatrixTest, Eq_func_1) {
  S21Matrix mat(3, 3);
  S21Matrix mat2(2, 3);
  ASSERT_EQ(mat.EqMatrix(mat2), 0);
}

TEST(MatrixTest, Eq_func_2) {
  S21Matrix mat(3, 3);
  S21Matrix mat2(3, 2);
  ASSERT_EQ(mat.EqMatrix(mat2), 0);
}

TEST(MatrixTest, Eq_func_3) {
  S21Matrix mat(3, 3);
  S21Matrix mat2(2, 2);
  ASSERT_EQ(mat.EqMatrix(mat2), 0);
}

TEST(MatrixTest, Eq_func_4) {
  S21Matrix mat(3, 3);
  double val = 0;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      mat.setVal(i, j, val++);
  S21Matrix mat2(3, 3);
  ASSERT_EQ(mat.EqMatrix(mat2), 0);
}

TEST(MatrixTest, Sum_func_0) {
  S21Matrix mat(3, 3);
  double val = 0;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      mat.setVal(i, j, val++);
  S21Matrix mat2(3, 3);
  val = 0;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      mat2.setVal(i, j, val++);
  mat.SumMatrix(mat2);
  val = 0;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      ASSERT_EQ(mat.getVal(i, j), 2 * val++);
}

TEST(MatrixTest, Sum_func_1) {
  S21Matrix mat(3, 3);
  double val = 0;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      mat.setVal(i, j, val++);
  S21Matrix mat2(3, 2);
  val = 0;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 2; j++)
      mat2.setVal(i, j, val++);
  ASSERT_THROW(mat.SumMatrix(mat2), std::logic_error);
}
TEST(MatrixTest, Sum_func_2) {
  S21Matrix mat(3, 3);
  double val = 0;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      mat.setVal(i, j, val++);
  S21Matrix mat2;
  ASSERT_THROW(mat.SumMatrix(mat2), std::logic_error);
}

TEST(MatrixTest, Sub_func_0) {
  S21Matrix mat(3, 3);
  double val = 0;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      mat.setVal(i, j, val++);
  S21Matrix mat2(3, 3);
  val = 0;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      mat2.setVal(i, j, val++);
  mat.SubMatrix(mat2);
  val = 0;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      ASSERT_EQ(mat.getVal(i, j), 0);
}

TEST(MatrixTest, Sub_func_1) {
  S21Matrix mat(3, 3);
  double val = 0;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      mat.setVal(i, j, val++);
  S21Matrix mat2(3, 2);
  val = 0;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 2; j++)
      mat2.setVal(i, j, val++);
  ASSERT_THROW(mat.SubMatrix(mat2), std::logic_error);
}
TEST(MatrixTest, Sub_func_2) {
  S21Matrix mat(3, 3);
  double val = 0;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      mat.setVal(i, j, val++);
  S21Matrix mat2;
  ASSERT_THROW(mat.SubMatrix(mat2), std::logic_error);
}

TEST(MatrixTest, Mul_func_0) {
  S21Matrix mat(3, 3);
  double val = 0;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      mat.setVal(i, j, val++);
  S21Matrix mat2(3, 3);
  val = 0;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      mat2.setVal(i, j, val++);
  mat.MulMatrix(mat2);
  double check_val[9] = {15, 18, 21, 42, 54, 66, 69, 90, 111};
  int kl = 0;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++){
      ASSERT_EQ(mat.getVal(i, j), check_val[kl]);
      kl++;
    }
}

TEST(MatrixTest, Mul_func_1) {
  S21Matrix mat(3, 3);
  double val = 0;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      mat.setVal(i, j, val++);
  S21Matrix mat2(2, 2);
  val = 0;
  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 2; j++)
      mat2.setVal(i, j, val++);
  ASSERT_THROW(mat.MulMatrix(mat2), std::logic_error);
}

TEST(MatrixTest, Mul_func_2) {
  S21Matrix mat(3, 3);
  double val = 0;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      mat.setVal(i, j, val++);
  S21Matrix mat2;
  ASSERT_THROW(mat.MulMatrix(mat2), std::logic_error);
}

TEST(MatrixTest, Mul_num_func_0) {
  S21Matrix mat(3, 3);
  double num = 3;
  double val = 0;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      mat.setVal(i, j, val++);
  mat.MulNumber(num);
  val = 0;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      ASSERT_EQ(mat.getVal(i, j), val++ * num);
}

TEST(MatrixTest, Mul_num_func_1) {
  S21Matrix mat;
  double num = 3;
  ASSERT_THROW(mat.MulNumber(num), std::logic_error);
}

TEST(MatrixTest, Transpose_func_0) {
  S21Matrix mat(3, 3);
  double val = 0;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      mat.setVal(i, j, val++);
  S21Matrix res =  mat.Transpose();
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      ASSERT_EQ(res.getVal(i, j), mat.getVal(j, i));
}

TEST(MatrixTest, Transpose_func_1) {
  S21Matrix mat;
  ASSERT_THROW(mat.Transpose(), std::logic_error);
}

TEST(MatrixTest, CalcComplements_func_0) {
  S21Matrix mat;
  ASSERT_THROW(mat.CalcComplements(), std::logic_error);
}

TEST(MatrixTest, CalcComplements_func_1) {
  S21Matrix mat(2, 4);
  ASSERT_THROW(mat.CalcComplements(), std::logic_error);
}

TEST(MatrixTest, CalcComplements_func_2) {
  S21Matrix mat(3, 3);
  double val = 0;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      mat.setVal(i, j, ++val);
  double check_val[9] = {-3, 6, -3, 6, -12, 6, -3, 6, -3};
  S21Matrix res =  mat.CalcComplements();
  int kl = 0;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++) {
      ASSERT_EQ(res.getVal(i, j), check_val[kl]);
      kl++;
    }  
}

TEST(MatrixTest, CalcComplements_func_3) {
  S21Matrix mat(2, 2);
  double val = 0;
  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 2; j++)
      mat.setVal(i, j, ++val);
  double check_val[4] = {4, -3, -2, 1};
  S21Matrix res =  mat.CalcComplements();
  int kl = 0;
  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 2; j++) {
      ASSERT_EQ(res.getVal(i, j), check_val[kl]);
      kl++;
    }  
}

TEST(MatrixTest, CalcComplements_func_4) {
  S21Matrix mat(1, 1);
  double val = 0;
  for (int i = 0; i < 1; i++)
    for (int j = 0; j < 1; j++)
      mat.setVal(i, j, ++val);
  double check_val[1] = {1};
  S21Matrix res =  mat.CalcComplements();
  int kl = 0;
  for (int i = 0; i < 1; i++)
    for (int j = 0; j < 1; j++) {
      ASSERT_EQ(res.getVal(i, j), check_val[kl]);
      kl++;
    }  
}

TEST(MatrixTest, Determinant_func_0) {
  S21Matrix mat(3, 3);
  mat.setVal(0, 0, 1);
  mat.setVal(0, 1, 5);
  mat.setVal(0, 2, 2);
  mat.setVal(1, 0, 8);
  mat.setVal(1, 1, 3);
  mat.setVal(1, 2, 6);
  mat.setVal(2, 0, 2);
  mat.setVal(2, 1, 8);
  mat.setVal(2, 2, 1);
  double res = mat.Determinant();
  int kl = 0;
  for (int i = 0; i < 1; i++)
    for (int j = 0; j < 1; j++)
      ASSERT_EQ(res, 91);
}

TEST(MatrixTest, InverseMatrix_func_0) {
  S21Matrix mat(2, 4);
  ASSERT_THROW(mat.InverseMatrix(), std::logic_error);
}

TEST(MatrixTest, InverseMatrix_func_1) {
  S21Matrix mat;
  ASSERT_THROW(mat.InverseMatrix(), std::logic_error); 
}

TEST(MatrixTest, InverseMatrix_func_2) {
  S21Matrix mat(3, 3);
  double val = 0;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      mat.setVal(i, j, ++val);
  ASSERT_THROW(mat.InverseMatrix(), std::logic_error);
}

TEST(MatrixTest, InverseMatrix_func_3) {
  S21Matrix mat(3, 3);
  mat.setVal(0, 0, 1);
  mat.setVal(0, 1, 5);
  mat.setVal(0, 2, 2);
  mat.setVal(1, 0, 8);
  mat.setVal(1, 1, 3);
  mat.setVal(1, 2, 6);
  mat.setVal(2, 0, 2);
  mat.setVal(2, 1, 8);
  mat.setVal(2, 2, 1);
  ASSERT_NO_THROW(mat.InverseMatrix());
}

TEST(MatrixTest, InverseMatrix_func_4) {
  S21Matrix mat(1, 1);
  mat.setVal(0, 0, 4);
  S21Matrix res = mat.InverseMatrix();
  ASSERT_EQ(res.getVal(0, 0), 0.25);
}

TEST(MatrixTest, operator_func_0) {
  S21Matrix mat1(1, 1);
  S21Matrix mat2(1, 1);
  bool res =(mat1 == mat2);
  ASSERT_EQ(res, true);
}

TEST(MatrixTest, operator_func_1) {
  S21Matrix mat1;
  S21Matrix mat2;
  ASSERT_THROW((mat1 == mat2), std::logic_error);
}

TEST(MatrixTest, operator_func_2) {
  S21Matrix mat1(3, 3);
  S21Matrix mat2(3, 3);
  double val = 0;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++){
      mat1.setVal(i, j, ++val);
      mat2.setVal(i, j, val);
    }
  S21Matrix result = mat1 + mat2;
  val = 0;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      ASSERT_EQ(result.getVal(i, j), ++val * 2);
}

TEST(MatrixTest, operator_func_3) {
  S21Matrix mat1;
  S21Matrix mat2;
  ASSERT_THROW((mat1 + mat2), std::logic_error);
}

TEST(MatrixTest, operator_func_4) {
  S21Matrix mat1(1, 2);
  S21Matrix mat2(2, 3);
  ASSERT_THROW((mat1 + mat2), std::logic_error);
}

TEST(MatrixTest, operator_func_5) {
  S21Matrix mat1(3, 3);
  S21Matrix mat2(3, 3);
  double val = 0;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++){
      mat1.setVal(i, j, ++val);
      mat2.setVal(i, j, val);
    }
  S21Matrix result = mat1 - mat2;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      ASSERT_EQ(result.getVal(i, j), 0);
}

TEST(MatrixTest, operator_func_6) {
  S21Matrix mat1;
  S21Matrix mat2;
  ASSERT_THROW((mat1 - mat2), std::logic_error);
}

TEST(MatrixTest, operator_func_7) {
  S21Matrix mat1(1, 2);
  S21Matrix mat2(2, 3);
  ASSERT_THROW((mat1 - mat2), std::logic_error);
}

TEST(MatrixTest, operator_func_8) {
  S21Matrix mat1(3, 3);
  S21Matrix mat2(3, 3);
  double val = 0;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      mat1.setVal(i, j, val++);
  val = 0;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      mat2.setVal(i, j, val++);
  
  S21Matrix result = mat1 * mat2;
  double check_val[9] = {15, 18, 21, 42, 54, 66, 69, 90, 111};
  int kl = 0;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++){
      ASSERT_EQ(result(i, j), check_val[kl]);
      kl++;
    }
}

TEST(MatrixTest, operator_func_9) {
  S21Matrix mat1;
  S21Matrix mat2;
  ASSERT_THROW((mat1 * mat2), std::logic_error);
}

TEST(MatrixTest, operator_func_10) {
  S21Matrix mat1(2, 2);
  S21Matrix mat2(4, 3);
  ASSERT_THROW((mat1 * mat2), std::logic_error);
}

TEST(MatrixTest, operator_func_11) {
  S21Matrix mat(3, 3);
  int num = 2;
  double val = 0;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      mat.setVal(i, j, ++val);
  S21Matrix result = mat * num;
  val = 0;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      ASSERT_EQ(result.getVal(i, j), ++val * num);
}

TEST(MatrixTest, operator_func_12) {
  S21Matrix mat1;
  int num = 2;
  ASSERT_THROW((mat1 * num), std::logic_error);
}

int main() {
  ::testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}