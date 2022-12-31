#include "matrix.hpp"

#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <iomanip>
#include <ios>
#include <iostream>


void Matrix::init(size_t size) {
  this->size = size;
  size_t s = this->size * this->size;
  // if (size > 0)
  this->data = new MATRIX_DATATYPE[s];
}

Matrix::Matrix() {
  this->init(0);
}

Matrix::Matrix(const size_t size) {
  this->init(size);
}

Matrix::Matrix(const Matrix &matrix) {
  size_t size = matrix.getSize();
  this->init(size);
  for (size_t i = 0; i < size * size; ++i) {
    operator()(i / size, i % size) = matrix(i / size, i % size);
  }
}

Matrix::~Matrix() {
  // if (size > 0)
  delete[] this->data;
}

Matrix Matrix::plus(const Matrix &other) const {
  Matrix matrix(this->size);
  for (size_t i = 0; i < this->size; ++i) {
    for (size_t j = 0; j < this->size; ++j) {
      matrix(i, j) = operator()(i, j) + other(i, j);
    }
  }
  return matrix;
}

Matrix Matrix::transpose() const {
  size_t size = getSize();

  Matrix result(size);

  for (size_t i = 0; i < size; ++i) {
    for (size_t j = i; j < size; ++j) {
      MATRIX_DATATYPE tmp = operator()(i, j);
      result(i, j) = operator()(j, i);
      result(j, i) = tmp;
    }
  }


  // for (size_t i = 0; i < this->size; ++i) {
  //   for (size_t j = 0; j < this->size; ++j) {
  //     result.set(i, j, this->get(j, i));
  //   }
  // }
  return result;
}

void Matrix::print() const {
  size_t size = getSize();
  std::cout << "[";
  for (size_t i = 0; i < size; ++i) {
    if (i != 0) {
      std::cout << " ";
    }
    std::cout << "[";
    for (size_t j = 0; j < size; ++j) {
      std::cout << operator()(i, j);
      if (j + 1 < size) {
        std::cout << ", ";
      }
    }
    std::cout << "]";
    if (i + 1 < size) {
      std::cout << ",";
      std::cout << std::endl;
    }
  }
  std::cout << "]" << std::endl;
}

// MATRIX_DATATYPE Matrix::get(size_t x, size_t y) const {
//   return this->data[x * this->size + y];
// }

// void Matrix::set(size_t x, size_t y, MATRIX_DATATYPE v) {
//   this->data[x * this->size + y] = v;
// }

size_t Matrix::getSize() const {
  return this->size;
}

MATRIX_DATATYPE Matrix::max() const {
  int max = operator()(0, 0);
  size_t size = getSize();

  for (size_t i = 1; i < size * size; ++i) {
    int el = operator()(i / size, i % size);
    if (el > max) {
      max = el;
    }
  }
  return max;
}

MATRIX_DATATYPE Matrix::min() const {
  int min = operator()(0, 0);
  size_t size = getSize();

  for (size_t i = 1; i < size * size; ++i) {
    int el = operator()(i / size, i % size);
    if (el < min) {
      min = el;
    }
  }
  return min;
}

Matrix Matrix::fill(size_t size, MATRIX_DATATYPE value) {
  Matrix result(size);
  size_t s = result.getSize();
  for (size_t i = 0; i < s * s; ++i) {
    result(i / s, i % s) = value;
  }
  return result;
}

Matrix Matrix::diagonal(size_t size, MATRIX_DATATYPE value) {
  Matrix result = Matrix::zeros(size);
  for (size_t i = 0; i < result.getSize(); ++i) {
    result(i, i) = value;
  }
  return result;
}

Matrix Matrix::identity(size_t size) {
  return Matrix::diagonal(size, 1);
}

Matrix Matrix::zeros(size_t size) {
  return Matrix::fill(size, 0.0);
}

Matrix Matrix::operator+() const {
  return Matrix(*this);
}

Matrix Matrix::operator+(const Matrix &other) const {
  size_t size = getSize();

  Matrix result(*this);

  for (size_t i = 0; i < size * size; ++i) {
    result(i / size, i % size) += other(i / size, i % size);
  }

  return result;
}

Matrix &Matrix::operator++() {
  size_t size = getSize();
  size_t s = size * size;
  for (size_t i = 0; i < s; ++i) {
    operator()(i / size, i % size) = operator()(i / size, i % size) + 1;
  }
  return *this;
}

Matrix Matrix::operator++(int) {
  Matrix result(*this);
  operator++();
  return result;
}

Matrix &Matrix::operator--() {
  size_t size = getSize();
  size_t s = size * size;
  for (size_t i = 0; i < s; ++i) {
    operator()(i / size, i % size) = operator()(i / size, i % size) + 1;
  }
  return *this;
}

Matrix Matrix::operator--(int) {
  Matrix result(*this);
  operator--();
  return result;
}

Matrix::operator size_t() {
  return getSize();
}

Matrix &Matrix::operator=(const Matrix &other) noexcept {
  if (&other == this) {
    return *this;
  }
  size = other.getSize();
  delete[] data;
  this->data = new MATRIX_DATATYPE[size * size];
  for (size_t i = 0; i < size * size; ++i) {
    operator()(i / size, i % size) = other(i / size, i % size);
  }

  return *this;
}

MATRIX_DATATYPE Matrix::operator()(size_t row, size_t col) const {
  return this->data[row * getSize() + col];
}

MATRIX_DATATYPE &Matrix::operator()(size_t row, size_t col) {
  return this->data[row * getSize() + col];
}

const Matrix operator-(const Matrix &matrix) {
  return -1.0 * matrix;
}

const Matrix operator-(const Matrix &matrix, const Matrix &other) {
  const Matrix o = -other;
  return matrix + o;
}

const Matrix operator*(MATRIX_DATATYPE value, const Matrix &matrix) {
  size_t size = matrix.getSize();
  Matrix result(size);
  for (size_t i = 0; i < size; ++i) {
    for (size_t j = 0; j < size; ++j) {
      result(i, j) = matrix(i, j) * value;
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
    size_t size;
    MATRIX_DATATYPE el;

    fs.read((char *)&size, sizeof(size_t));
    std::cout << size << std::endl;
    matrix = Matrix::zeros(size);

    for (size_t i = 0; i < size * size; ++i) {
      fs.read((char *)&el, sizeof(MATRIX_DATATYPE));
      matrix(i / size, i % size) = el;
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

  size_t size = matrix.getSize();
  std::fstream &fs = file.getFStream();

  if ((file.getMode() & std::ios_base::binary) > 0) {
    fs.write((char *)&size, sizeof(size_t));
    for (size_t i = 0; i < size * size; ++i) {
      MATRIX_DATATYPE el = matrix(i / size, i % size);
      fs.write((char *)&el, sizeof(MATRIX_DATATYPE));
    }
  } else {
    fs << "[";
    for (size_t i = 0; i < size; ++i) {
      if (i != 0) {
        fs << " ";
      }
      fs << "[";
      for (size_t j = 0; j < size; ++j) {
        fs << matrix(i, j);
        if (j + 1 < size) {
          fs << ", ";
        }
      }
      fs << "]";
      if (i + 1 < size) {
        fs << ",\n";
      }
    }
    fs << "]\n";
  }
  return file;
}
