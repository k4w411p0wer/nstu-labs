#include "matrix.hpp"

#include <cstddef>
#include <cstdint>
#include <fstream>
#include <ios>
#include <iostream>
#include <ostream>

#include "circularqueue.hpp"


static int test_num = 0;

#define TESTCASE_BEGIN(TEXT)                                                   \
  test_num++;                                                                  \
  std::cout << "Test " << test_num << ": " TEXT << std::endl;                  \
  {
#define TESTCASE_END() }


int main() {
  TESTCASE_BEGIN("");
  SquareMatrix m(5);
  for (int i = 0; i < 5 * 5; ++i) {
    m(i / 5, i % 5) = i;
  }
  m.print();
  TESTCASE_END();

  TESTCASE_BEGIN("Транспонированная матрица");
  SquareMatrix m(5);
  for (int i = 0; i < 5 * 5; ++i) {
    m(i / 5, i % 5) = i;
  }
  m.print();
  SquareMatrix tr = m.transpose();
  tr.print();
  TESTCASE_END();

  TESTCASE_BEGIN("Заполнение матрицы");
  Matrix fill = Matrix::fill(5, 5, 5);
  fill.print();
  SquareMatrix sqfill = SquareMatrix::fill(5, 5);
  sqfill.print();
  TESTCASE_END();

  TESTCASE_BEGIN("Диагональная матрица");
  SquareMatrix diagonal = SquareMatrix::diagonal(5, 5);
  diagonal.print();
  TESTCASE_END();

  TESTCASE_BEGIN("Единичная матрица");
  SquareMatrix identity = SquareMatrix::identity(5);
  identity.print();
  TESTCASE_END();

  TESTCASE_BEGIN("Матрица нулей");
  SquareMatrix zeros = Matrix::zeros(5, 5);
  zeros.print();
  SquareMatrix sqzeros = SquareMatrix::zeros(5);
  sqzeros.print();
  TESTCASE_END();

  TESTCASE_BEGIN("Копирование и сложение");
  SquareMatrix m = SquareMatrix::fill(5, 1);
  SquareMatrix copy(m);
  m.plus(copy.plus(SquareMatrix::fill(5, 1))).print();
  TESTCASE_END();

  TESTCASE_BEGIN("Префиксный инкремент");
  SquareMatrix a = SquareMatrix::fill(5, 1);
  (++a).print();
  a.print();
  TESTCASE_END();

  TESTCASE_BEGIN("Постфиксный инкремент")
  SquareMatrix b = SquareMatrix::fill(5, 1);
  (b++).print();
  b.print();
  TESTCASE_END();

  TESTCASE_BEGIN("Присваивание");
  SquareMatrix c = SquareMatrix::fill(5, 1);
  SquareMatrix d = SquareMatrix::identity(5);

  SquareMatrix e;
  e = c;
  e.print();
  e = d;
  e.print();
  TESTCASE_END();

  TESTCASE_BEGIN("operator+");
  SquareMatrix c = SquareMatrix::fill(5, 1);
  SquareMatrix d = SquareMatrix::identity(5);
  (c + d).print();
  TESTCASE_END();

  TESTCASE_BEGIN("operator-");
  SquareMatrix c = SquareMatrix::fill(5, 1);
  SquareMatrix d = SquareMatrix::identity(5);
  (c - d).print();
  TESTCASE_END();

  TESTCASE_BEGIN("To int");
  std::cout << int(SquareMatrix::identity(5)) << std::endl;
  TESTCASE_END();

  TESTCASE_BEGIN("Out to text file");
  File otf("./assets/out.txt", std::ios_base::out);
  otf << SquareMatrix::identity(5);
  otf.close();
  TESTCASE_END();

  TESTCASE_BEGIN("Out to binary file");
  File obf("./assets/out.b", std::ios_base::binary | std::ios_base::out);
  obf << SquareMatrix::identity(5);
  obf.close();
  TESTCASE_END();

  TESTCASE_BEGIN("In from binary file");
  Matrix mmm;
  File ibf("./assets/in.b", std::ios_base::binary | std::ios_base::in);
  ibf >> mmm;
  ibf.close();
  mmm.print();
  TESTCASE_END();

  TESTCASE_BEGIN("Overload vectors print");
  VectorH vec = Matrix::fill(1, 10, 5);
  vec.print();
  static_cast<Matrix &>(vec).print();
  TESTCASE_END();

  TESTCASE_BEGIN("VectorH to VectorV");
  VectorH vech = Matrix::fill(1, 10, 5);
  vech.print();
  vech.transpose().print();
  TESTCASE_END();

  TESTCASE_BEGIN("CircularDoubleLinkedList");
  CircularQueueOfMatrix cq;
  Matrix *m = new Matrix[5];
  for (std::size_t i = 0; i < 5; ++i) {
    m[i] = Matrix::fill(i + 1, i + 1, i + 1);
    cq.add(m[i]);
  }
  cq.print();
  cq.remove();
  cq.print();
  TESTCASE_END();

  TESTCASE_BEGIN("Exceptions")
  Matrix m = Matrix::fill(5, 5, 5);
  try {
    m(6, 6);
  } catch (Matrix::OutOfRange &e) {
    std::cout << e.what() << std::endl;
  }
  try {
    VectorH vech(m);
  } catch (Matrix::BadSize &e) {
    std::cout << e.what() << std::endl;
  }
  TESTCASE_END();

  return 0;
}
