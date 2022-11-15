#include "circularqueue.hpp"
#include <cassert>
#include <iostream>
#include <ostream>


CircularQueueOfMatrixNode::CircularQueueOfMatrixNode(Matrix &_matrix)
    : _data(_matrix), _next(nullptr), _prev(nullptr) {}

CircularQueueOfMatrixNode *CircularQueueOfMatrixNode::getPrev() {
  return _prev;
}

void CircularQueueOfMatrixNode::setPrev(CircularQueueOfMatrixNode *prev) {
  _prev = prev;
}

CircularQueueOfMatrixNode *CircularQueueOfMatrixNode::getNext() {
  return _next;
}

void CircularQueueOfMatrixNode::setNext(CircularQueueOfMatrixNode *next) {
  _next = next;
}

Matrix &CircularQueueOfMatrixNode::getMatrix() {
  return _data;
}

CircularQueueOfMatrix::CircularQueueOfMatrix() : _head(nullptr) {}

CircularQueueOfMatrix::~CircularQueueOfMatrix() {
  CircularQueueOfMatrixNode *iterator = _head, *next;
  do {
    if (!iterator)
      break;
    next = iterator->getNext();
    delete iterator;
    iterator = next;
  } while (iterator != _head);
}

void CircularQueueOfMatrix::add(Matrix &m) {
  CircularQueueOfMatrixNode *node = new CircularQueueOfMatrixNode(m);
  if (_head) {
    node->setNext(_head);
    node->setPrev(_head->getPrev());
    _head->getPrev()->setNext(node);
    _head->setPrev(node);
  } else {
    node->setNext(node);
    node->setPrev(node);
    _head = node;
  }
}

Matrix &CircularQueueOfMatrix::remove() {
  assert(_head != nullptr);  // can be replaced with exceptions
  Matrix &result = _head->getMatrix();
  CircularQueueOfMatrixNode *next = _head->getNext(), *prev = _head->getPrev();
  if (_head == next) {
    delete _head;
    _head = nullptr;
    return result;
  }
  prev->setNext(next);
  next->setPrev(prev);

  delete _head;
  _head = next;
  return result;
}

void CircularQueueOfMatrix::fprint(std::ostream &os) {
  int num = 0;
  CircularQueueOfMatrixNode *iterator = _head;
  do {
    if (!iterator) {
      os << "Queue is clear" << std::endl;
      break;
    }
    os << "(" << num++ << "): " << std::endl;
    static_cast<Matrix>(iterator->getMatrix()).fprint(os);
    // iterator->getMatrix().fprint(os);
    // std::cout << iterator<< " " << iterator->getNext() << " " << _head <<
    // std::endl;
    iterator = iterator->getNext();
  } while (iterator != _head);
}

void CircularQueueOfMatrix::print() {
  fprint(std::cout);
}
