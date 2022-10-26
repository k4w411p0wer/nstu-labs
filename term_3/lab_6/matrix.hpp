#pragma once

#include <cstddef>
#include <cstdio>
#include <cstring>
#include <exception>
#include <fstream>
#include <limits>
#include <ostream>

#include "file.hpp"


#define MATRIX_DATATYPE double


class Matrix {
  private:
  std::size_t _rows;
  std::size_t _cols;
  MATRIX_DATATYPE *_data;

  void _init(const std::size_t, const std::size_t);

  public:
  Matrix();
  Matrix(const std::size_t, const std::size_t);
  // Matrix(std::size_t, std::size_t, MATRIX_DATATYPE *);
  // Matrix(std::size_t, std::size_t, MATRIX_DATATYPE **);
  Matrix(const Matrix &);
  ~Matrix();


  Matrix plus(const Matrix &) const;
  virtual void fprint(std::ostream &) const;
  void print() const;
  Matrix transpose() const;
  std::size_t getRows() const;
  std::size_t getCols() const;

  static Matrix fill(std::size_t, std::size_t, MATRIX_DATATYPE);
  static Matrix zeros(std::size_t, std::size_t);

  Matrix operator+() const;
  Matrix operator+(const Matrix &) const;
  MATRIX_DATATYPE operator()(std::size_t, std::size_t) const;
  MATRIX_DATATYPE &operator()(std::size_t, std::size_t);
  Matrix &operator++();
  Matrix operator++(int);
  Matrix &operator--();
  Matrix operator--(int);

  operator int();

  Matrix &operator=(const Matrix &other) noexcept;

  friend const Matrix operator-(const Matrix &);
  friend const Matrix operator-(const Matrix &, const Matrix &);
  friend const Matrix operator*(MATRIX_DATATYPE, const Matrix &);
  friend const Matrix operator*(const Matrix &, MATRIX_DATATYPE);
  friend const Matrix operator*(const Matrix &, const Matrix &);

  friend File &operator>>(File &, Matrix &);
  friend File &operator<<(File &, const Matrix &);
  class OutOfRange : public std::exception {
private:
    std::size_t _row, _col;
    char *_message;

public:
    OutOfRange();
    OutOfRange(std::size_t row, std::size_t col);
    ~OutOfRange();
    const char *what() const noexcept;
  };
  class BadSize : public std::exception {
public:
    const char *what() const noexcept;
  };
};

class SquareMatrix : public Matrix {
  public:
  SquareMatrix() : SquareMatrix(0){};
  SquareMatrix(std::size_t size) : Matrix(size, size){};
  SquareMatrix(const Matrix &);
  SquareMatrix(const SquareMatrix &matrix)
      : Matrix(dynamic_cast<const Matrix &>(matrix)){};
  ~SquareMatrix() = default;

  static SquareMatrix fill(std::size_t, MATRIX_DATATYPE);
  static SquareMatrix zeros(std::size_t);
  static SquareMatrix diagonal(std::size_t, MATRIX_DATATYPE);
  static SquareMatrix identity(std::size_t);

  SquareMatrix operator=(const SquareMatrix &) noexcept;

  SquareMatrix transpose() const;
};

class VectorH;
class VectorV;

class VectorH : public Matrix {
  public:
  VectorH() : VectorH(0){};
  VectorH(std::size_t size) : Matrix(1, size){};
  VectorH(const Matrix &);
  VectorH(const VectorH &matrix)
      : Matrix(dynamic_cast<const Matrix &>(matrix)){};
  ~VectorH() = default;


  VectorV transpose() const;

  void fprint(std::ostream &) const override;
};

class VectorV : public Matrix {
  public:
  VectorV() : VectorV(0){};
  VectorV(std::size_t size) : Matrix(size, 1){};
  VectorV(const Matrix &);
  VectorV(const VectorH &matrix)
      : Matrix(dynamic_cast<const Matrix &>(matrix)){};
  ~VectorV() = default;

  VectorH transpose() const;

  void fprint(std::ostream &) const override;
};
