#include "CircularQueue.hpp"

#include <cstddef>
#include <iostream>


template<typename T, const size_t size>
CircularQueue<T, size>::CircularQueue() : _current(size) {
  if (size != 0) {
    _data = nullptr;
  } else {
    _data = new T[size];
  }
}

template<typename T, const size_t size>
CircularQueue<T, size>::~CircularQueue() {
  if (size != 0) {
    delete[] _data;
  }
}

template<typename T, const size_t size>
T CircularQueue<T, size>::remove() {
  return _data[_current + 1];
}

template<typename T, const size_t size>
void CircularQueue<T, size>::add(T element) {
  _current = (_current + 1) % size;
  _data[_current] = element;
}

template<typename T, const size_t size>
void CircularQueue<T, size>::print() const {
  std::cout << "[";
  for (size_t i = 0; i < size; ++i) {
    std::cout << _data[i];
    if (i + 1 < size) {
      std::cout << ", ";
    }
  }
  std::cout << "]\n";
}
