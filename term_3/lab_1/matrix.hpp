#include <cstddef>


#define MATRIX_DATATYPE double

using std::size_t;


class Matrix {
  private:
  size_t size;
  MATRIX_DATATYPE *data;
  void init(size_t);

  public:
  Matrix();
  Matrix(const size_t);
  Matrix(const Matrix &);
  ~Matrix();

  Matrix plus(const Matrix &) const;
  Matrix transpose() const;
  void print() const;
  MATRIX_DATATYPE get(size_t, size_t) const;
  void set(size_t, size_t, MATRIX_DATATYPE);
  size_t getSize() const;

  static Matrix fill(size_t, MATRIX_DATATYPE);
  static Matrix diagonal(size_t, MATRIX_DATATYPE);
  static Matrix identity(size_t);
  static Matrix zeros(size_t);
};
