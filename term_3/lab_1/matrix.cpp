#include "matrix.hpp"

#include <cmath>
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <limits>
#include <ostream>

void Matrix::init(size_t size) {
  this->size = size;
  size_t s = this->size * this->size;
  if (size > 0)
    this->data = new MATRIX_DATATYPE[s];
}

Matrix::Matrix() { this->init(0); }

Matrix::Matrix(const size_t size) { this->init(size); }

Matrix::Matrix(const Matrix &matrix) {
  size_t size = matrix.getSize();
  this->init(size);
  for (size_t i = 0; i < size * size; ++i) {
    set(i / size, i % size, matrix.get(i / size, i % size));
  }
}

Matrix::~Matrix() {
  if (size > 0)
    delete[] this->data;
}

Matrix Matrix::plus(const Matrix &other) const {
  Matrix matrix(this->size);
  for (size_t i = 0; i < this->size; ++i) {
    for (size_t j = 0; j < this->size; ++j) {
      matrix.set(i, j, this->get(i, j) + other.get(i, j));
    }
  }
  return matrix;
}

Matrix Matrix::transpose() const { // TODO: rewrite
  Matrix result(this->size);

  for (size_t i = 0; i < result.getSize(); ++i) {
    for (size_t j = i; j < result.getSize(); ++j) {
      MATRIX_DATATYPE tmp = this->get(i, j);
      result.set(i, j, this->get(j, i));
      result.set(j, i, tmp);
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
  std::cout << "[";
  for (size_t i = 0; i < this->size; ++i) {
    if (i != 0) {
      std::cout << " ";
    }
    std::cout << "[";
    for (size_t j = 0; j < this->size; ++j) {
      std::cout << this->get(i, j);
      if (j + 1 < this->size) {
        std::cout << ", ";
      }
    }
    std::cout << "]";
    if (i + 1 < this->size) {
      std::cout << ",";
      std::cout << std::endl;
    }
  }
  std::cout << "]" << std::endl;
}

MATRIX_DATATYPE Matrix::get(size_t x, size_t y) const {
  return this->data[x * this->size + y];
}

void Matrix::set(size_t x, size_t y, MATRIX_DATATYPE v) {
  this->data[x * this->size + y] = v;
}

size_t Matrix::getSize() const { return this->size; }

Matrix Matrix::fill(size_t size, MATRIX_DATATYPE value) {
  Matrix result(size);
  size_t s = result.getSize();
  for (size_t i = 0; i < s * s; ++i) {
    result.set(i / s, i % s, value);
  }
  return result;
}

Matrix Matrix::diagonal(size_t size, MATRIX_DATATYPE value) {
  Matrix result = Matrix::zeros(size);
  for (size_t i = 0; i < result.getSize(); ++i) {
    result.set(i, i, value);
  }
  return result;
}

Matrix Matrix::identity(size_t size) { return Matrix::diagonal(size, 1); }

Matrix Matrix::zeros(size_t size) { return Matrix::fill(size, 0.0); }
