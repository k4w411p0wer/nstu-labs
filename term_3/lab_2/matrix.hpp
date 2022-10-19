#include <cstddef>


#define MATRIX_DATATYPE double

using std::size_t;


class Matrix {
  private:
  size_t size;
  MATRIX_DATATYPE *data;
  void init(size_t);

  MATRIX_DATATYPE max() const;
  MATRIX_DATATYPE min() const;

  bool validateIndexes(size_t, size_t) const;

  public:
  Matrix();
  Matrix(const size_t);
  Matrix(const Matrix &);
  ~Matrix();

  Matrix plus(const Matrix &) const;
  Matrix transpose() const;
  void print() const;
  // MATRIX_DATATYPE get(size_t, size_t) const;
  // void set(size_t, size_t, MATRIX_DATATYPE);
  size_t getSize() const;

  static Matrix fill(size_t, MATRIX_DATATYPE);
  static Matrix diagonal(size_t, MATRIX_DATATYPE);
  static Matrix identity(size_t);
  static Matrix zeros(size_t);

  Matrix operator+() const;
  Matrix operator+(const Matrix &) const;
  double operator()(size_t, size_t) const;
  MATRIX_DATATYPE &operator()(size_t, size_t);
  Matrix &operator++();
  Matrix operator++(int);
  Matrix &operator--();
  Matrix operator--(int);

  operator size_t();

  Matrix &operator=(const Matrix &other) noexcept;
};

const Matrix operator-(const Matrix &);
const Matrix operator-(const Matrix &, const Matrix &);
const Matrix operator*(MATRIX_DATATYPE, const Matrix &);
const Matrix operator*(const Matrix &, MATRIX_DATATYPE);
const Matrix operator*(const Matrix &, const Matrix &);
