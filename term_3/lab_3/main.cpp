#include "matrix.hpp"

#include <cstdint>
#include <fstream>
#include <ios>
#include <iostream>
#include <ostream>


int main() {
  std::cout << "Test 1:" << std::endl;
  Matrix matrix(5);
  for (int i = 0; i < 5 * 5; ++i) {
    matrix(i / 5, i % 5) = i;
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

  std::cout << "Test 8: Префиксный инкремент" << std::endl;
  Matrix a = Matrix::fill(5, 1);
  (++a).print();
  a.print();
  std::cout << "Test 9: Постфиксный инкремент" << std::endl;
  Matrix b = Matrix::fill(5, 1);
  (b++).print();
  b.print();

  std::cout << "Test 10: Присваивание" << std::endl;
  Matrix c = Matrix::fill(5, 1);
  Matrix d = Matrix::identity(5);

  Matrix e;
  e = c;
  e = d;

  std::cout << "Test 11: operator+" << std::endl;
  (c + d).print();

  std::cout << "Test 12: operator-" << std::endl;
  (c - d).print();

  std::cout << "Test 13: to size_t" << std::endl;
  std::cout << size_t(matrix) << std::endl;

  File otf("./assets/out.txt", std::ios_base::out);
  otf << matrix;
  otf.close();

  File obf("./assets/out.b", std::ios_base::binary | std::ios_base::out);
  obf << matrix;
  obf.close();

  Matrix mmm;
  File ibf("./assets/in.b", std::ios_base::binary | std::ios_base::in);
  ibf >> mmm;
  ibf.close();
  mmm.print();

  return 0;
}
