#include <cstddef>
#include <iostream>
#include <ostream>

template <typename T, size_t static_initial_size = 0> class CircularQueue {
private:
  size_t _size;
  ptrdiff_t _last;
  ptrdiff_t _first;
  T *_data;

public:
  // CircularQueue() : CircularQueue<T,
  // static_initial_size>(static_initial_size) {}
  CircularQueue(size_t size = -1) : _last(-1), _first(-1) {
    if (size == -1)
      _size = static_initial_size;
    else
      _size = size;

    if (_size == 0) {
      _data = nullptr;
    } else {
      _data = new T[_size];
    }
  }
  ~CircularQueue() {
    if (_size != 0) {
      delete[] _data;
    }
  }

  T remove() {
    if (_first == -1)
      throw CircularQueueIsClear();
    T result = _data[_first];
    if (_first == _last) {
      _data[_last] = 0;
      _first = -1;
      _last = -1;
    }
    return result;
  }
  void add(T element) {
    _last = (_last + 1) % _size;
    if (_first == -1)
      _first = _last;
    _data[_last] = element;
  }
  void print() const {
    std::cout << "( size_t size = " << _size << ") -> ";
    std::cout << "[";
    for (size_t i = 0; i < _size; ++i) {
      std::cout << _data[i];
      if (i + 1 < _size) {
        std::cout << ", ";
      }
    }
    std::cout << "]\n";
  }
  class CircularQueueIsClear : public std::exception {
  public:
    const char *what() const noexcept { return "CirqularQueue is clear"; }
  };
};
