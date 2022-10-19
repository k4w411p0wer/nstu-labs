#include "matrix.hpp"

#include <iostream>


int main() {
  std::cout << "Test 1:" << std::endl;
  Matrix matrix(5);
  for (int i = 0; i < 5 * 5; ++i) {
    matrix.set(i / 5, i % 5, i);
  }
  matrix.print();

  std::cout << "Test 2: Транспонированная матрица" << std::endl;
  Matrix tr = matrix.transpose();
  tr.print();

  std::cout << "Test 3: заполнение матрицы" << std::endl;
  Matrix fill = Matrix::fill(5, 5);
  fill.print();

  std::cout << "Test 4: диагональная матрица" << std::endl;
  Matrix diagonal = Matrix::diagonal(5, 5);
  diagonal.print();
  std::cout << "Test 5: единичная матрица" << std::endl;
  Matrix identity = Matrix::identity(5);
  identity.print();
  std::cout << "Test 6: матрица нулей" << std::endl;
  Matrix zeros = Matrix::zeros(5);
  zeros.print();
  std::cout << "Test 7: копирование и сложение" << std::endl;
  Matrix copy(matrix);

  matrix.plus(copy.plus(Matrix::fill(copy.getSize(), 1))).print();

  return 0;
}
