#include "matrix.hpp"

#include <cassert>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <iomanip>
#include <ios>
#include <iostream>


#define _ASSERT_INDEXES(SELF, OTHER)                                           \
  assert((SELF).getRows() == (OTHER).getRows()                                 \
         && (SELF).getCols() == (OTHER).getCols());


void Matrix::_init(const std::size_t rows, const std::size_t cols) {
  _rows = rows;
  _cols = cols;
  size_t size = _rows * _cols;
  if (size > 0)
    _data = new MATRIX_DATATYPE[size];
}

void Matrix::_assert_indexes(const Matrix &other) {
  assert(_rows == other.getRows() && _cols == other.getCols());
}

Matrix::Matrix() : Matrix(0, 0) {}

Matrix::Matrix(const std::size_t rows, const std::size_t cols) {
  _init(rows, cols);
}

Matrix::Matrix(const Matrix &matrix) {
  std::size_t rows = matrix._rows;
  std::size_t cols = matrix._cols;
  std::size_t size = rows * cols;

  _init(rows, cols);

  for (std::size_t row = 0; row < rows; ++row) {
    for (std::size_t col = 0; col < cols; ++col) {
      operator()(row, col) = matrix(row, col);
    }
  }
}

Matrix::~Matrix() {
  if (_rows * _cols > 0)
    delete[] _data;
}

Matrix Matrix::plus(const Matrix &other) const {
  _ASSERT_INDEXES(*this, other);

  Matrix result(_rows, _cols);

  for (std::size_t row = 0; row < _rows; ++row) {
    for (std::size_t col = 0; col < _cols; ++col) {
      result(row, col) = operator()(row, col) + other(row, col);
    }
  }

  return result;
}

Matrix Matrix::transpose() const {
  Matrix result(_cols, _rows);

  for (std::size_t row = 0; row < _cols; ++row) {
    for (std::size_t col = 0; col < _rows; ++col) {
      result(row, col) = operator()(col, row);
    }
  }
  return result;
}

void Matrix::fprint(std::ostream &stream) const {
  stream << "[";
  for (std::size_t row = 0; row < _rows; ++row) {
    if (row != 0)
      stream << " ";
    stream << "[";
    for (std::size_t col = 0; col < _cols; ++col) {
      stream << operator()(row, col);
      if (col + 1 < _cols)
        stream << ", ";
    }
    stream << "]";
    if (row + 1 < _rows)
      stream << "," << std::endl;
  }
  stream << "]" << std::endl;
}

void Matrix::print() const {
  fprint(std::cout);
}

std::size_t Matrix::getRows() const {
  return _rows;
}

std::size_t Matrix::getCols() const {
  return _cols;
}

Matrix Matrix::fill(std::size_t rows, std::size_t cols, MATRIX_DATATYPE value) {
  Matrix result(rows, cols);

  for (std::size_t row = 0; row < rows; ++row) {
    for (std::size_t col = 0; col < cols; ++col) {
      result(row, col) = value;
    }
  }
  return result;
}

// Matrix Matrix::diagonal(size_t size, MATRIX_DATATYPE value) {
//   Matrix result = Matrix::zeros(size);
//   for (size_t i = 0; i < result.getSize(); ++i) {
//     result(i, i) = value;
//   }
//   return result;
// }

// Matrix Matrix::identity(size_t size) {
//   return Matrix::diagonal(size, 1);
// }

Matrix Matrix::zeros(std::size_t rows, std::size_t cols) {
  return Matrix::fill(rows, cols, 0.0);
}

Matrix Matrix::operator+() const {
  return Matrix(*this);
}

Matrix Matrix::operator+(const Matrix &other) const {
  _ASSERT_INDEXES(*this, other);
  Matrix result(*this);

  for (std::size_t row = 0; row < _rows; ++row) {
    for (std::size_t col = 0; col < _cols; ++col) {
      result(row, col) += other(row, col);
    }
  }

  return result;
}

Matrix &Matrix::operator++() {
  for (std::size_t row = 0; row < _rows; ++row) {
    for (std::size_t col = 0; col < _cols; ++col) {
      operator()(row, col) = operator()(row, col) + 1;
    }
  }
  return *this;
}

Matrix Matrix::operator++(int) {
  Matrix result(*this);
  operator++();
  return result;
}

Matrix &Matrix::operator--() {
  for (std::size_t row = 0; row < _rows; ++row) {
    for (std::size_t col = 0; col < _cols; ++col) {
      operator()(row, col) = operator()(row, col) - 1;
    }
  }
  return *this;
}

Matrix Matrix::operator--(int) {
  Matrix result(*this);
  operator--();
  return result;
}

Matrix::operator int() {
  return _rows * _cols;
}

Matrix &Matrix::operator=(const Matrix &other) noexcept {
  if (&other == this)
    return *this;

  if (_rows * _cols > 0)
    delete[] _data;

  _rows = other.getRows();
  _cols = other.getCols();
  _data = new MATRIX_DATATYPE[_rows * _cols];

  for (std::size_t row = 0; row < _rows; ++row) {
    for (std::size_t col = 0; col < _cols; ++col) {
      operator()(row, col) = other(row, col);
    }
  }

  return *this;
}

MATRIX_DATATYPE Matrix::operator()(size_t row, size_t col) const {
  assert(row < _rows && col < _cols);
  return _data[row * _cols + col];
}

MATRIX_DATATYPE &Matrix::operator()(size_t row, size_t col) {
  assert(row < _rows && col < _cols);
  return _data[row * _cols + col];
}

const Matrix operator-(const Matrix &matrix) {
  return -1.0 * matrix;
}

const Matrix operator-(const Matrix &matrix, const Matrix &other) {
  _ASSERT_INDEXES(matrix, other);
  const Matrix o = -other;
  return matrix + o;
}

const Matrix operator*(MATRIX_DATATYPE value, const Matrix &matrix) {
  Matrix result(matrix);
  for (std::size_t row = 0; row < matrix._rows; ++row) {
    for (std::size_t col = 0; col < matrix._cols; ++col) {
      result(row, col) = matrix(row, col) * value;
    }
  }
  return result;
}

const Matrix operator*(const Matrix &matrix, MATRIX_DATATYPE value) {
  return value * matrix;
}

const Matrix operator*(const Matrix &matrix, const Matrix &other) {
  // TODO:
  return matrix;
}

File &operator>>(File &file, Matrix &matrix) {
  if ((file.getMode() & std::ios_base::in) <= 0) {
    return file;
  }
  std::fstream &fs = file.getFStream();
  if ((file.getMode() & std::ios_base::binary) > 0) {
    std::size_t rows, cols;
    MATRIX_DATATYPE el;

    fs.read((char *)&rows, sizeof(size_t));
    fs.read((char *)&cols, sizeof(size_t));
    matrix = Matrix(rows, cols);

    for (std::size_t row = 0; row < rows; ++row) {
      for (std::size_t col = 0; col < cols; ++col) {
        fs.read((char *)&el, sizeof(MATRIX_DATATYPE));
        matrix(row, col) = el;
      }
    }
  } else {
    // TODO
  }
  return file;
}

File &operator<<(File &file, const Matrix &matrix) {
  if ((file.getMode() & std::ios_base::out) <= 0) {
    return file;
  }

  std::fstream &fs = file.getFStream();

  if ((file.getMode() & std::ios_base::binary) > 0) {
    fs.write((char *)&matrix._rows, sizeof(size_t));
    fs.write((char *)&matrix._cols, sizeof(size_t));
    for (std::size_t row = 0; row < matrix._rows; ++row) {
      for (std::size_t col = 0; col < matrix._cols; ++col) {
        MATRIX_DATATYPE el = matrix(row, col);
        fs.write((char *)&el, sizeof(MATRIX_DATATYPE));
      }
    }
  } else {
    matrix.fprint(fs);
  }
  return file;
}

SquareMatrix::SquareMatrix(const Matrix &matrix)
    : Matrix(dynamic_cast<const Matrix &>(matrix)) {
  assert(matrix.getRows() == matrix.getCols());
}

SquareMatrix SquareMatrix::fill(std::size_t size, MATRIX_DATATYPE value) {
  return SquareMatrix(Matrix::fill(size, size, value));
}

SquareMatrix SquareMatrix::zeros(std::size_t size) {
  return SquareMatrix::fill(size, 0);
}

SquareMatrix SquareMatrix::diagonal(std::size_t size, MATRIX_DATATYPE value) {
  SquareMatrix result = SquareMatrix::zeros(size);
  for (std::size_t i = 0; i < size; ++i) {
    result(i, i) = value;
  }
  return result;
}

SquareMatrix SquareMatrix::identity(std::size_t size) {
  return SquareMatrix::diagonal(size, 1);
}

SquareMatrix SquareMatrix::transpose() const {
  return SquareMatrix(Matrix::transpose());
}
SquareMatrix SquareMatrix::operator=(const SquareMatrix &other) noexcept {
  Matrix::operator=(other);
  return *this;
}

VectorH::VectorH(const Matrix &matrix)
    : Matrix(dynamic_cast<const Matrix &>(matrix)) {
  assert(matrix.getRows() == 1);
}

void VectorH::fprint(std::ostream &stream) const {
  std::cout << "[";
  std::size_t size = getCols();
  for (std::size_t i = 0; i < size; ++i) {
    std::cout << operator()(0, i);
    if (i + 1 < size)
      std::cout << ", ";
  }
  std::cout << "]" << std::endl;
}

VectorV::VectorV(const Matrix &matrix)
    : Matrix(dynamic_cast<const Matrix &>(matrix)) {
  assert(matrix.getCols() == 1);
}
void VectorV::fprint(std::ostream &stream) const {
  std::cout << "[";
  std::size_t size = getRows();
  for (std::size_t i = 0; i < size; ++i) {
    if (i != 0)
      stream << " ";
    std::cout << operator()(i, 0);
    if (i + 1 < size)
      std::cout << "," << std::endl;
  }
  std::cout << "]" << std::endl;
}

VectorV VectorH::transpose() const {
  return VectorV(Matrix::transpose());
}
VectorH VectorV::transpose() const {
  return VectorH(Matrix::transpose());
}
