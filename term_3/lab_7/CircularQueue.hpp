#include <cstddef>
#include <iostream>

class CircularQueueIsClear : public std::exception {
  public:
  const char *what() const noexcept {
    return "CirqularQueue is clear";
  }
};

template<typename T>
class CircularQueue {
  private:
  size_t _size;
  ptrdiff_t _last;
  ptrdiff_t _first;
  T *_data;

  public:
  CircularQueue() : CircularQueue<T>(0) {}
  CircularQueue(size_t size) : _size(size), _last(-1), _first(-1) {
    if (_size == 0) {
      _data = nullptr;
    } else {
      _data = new T[size];
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
    _first = (_first + 1) % _size;
    return result;
  }
  void add(T element) {
    _last = (_last + 1) % _size;
    if (_first == -1)
      _first = _last;
    _data[_last] = element;
  }
  void print() const {
    std::cout << "[";
    for (size_t i = 0; i < _size; ++i) {
      std::cout << _data[i];
      if (i + 1 < _size) {
        std::cout << ", ";
      }
    }
    std::cout << "]\n";
  }
};
