#include "circularqueue.hpp"
#include <iostream>


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
  if (_head == nullptr)
    throw NotEnoughOfItems();
  Matrix &result = _head->getPrev()->getMatrix();
  CircularQueueOfMatrixNode *prev = _head->getPrev();
  if (_head == prev)
    _head = nullptr;
  else {
    prev->getPrev()->setNext(_head);
    _head->setPrev(prev->getPrev());
  }
  delete prev;
  return result;
}

void CircularQueueOfMatrix::fprint(std::ostream &os) {
  int num = 0;
  CircularQueueOfMatrixNode *iterator = _head;
  do {
    if (!iterator) {
      os << "No items" << std::endl;
      return;
    }
    os << "(" << num++ << "): " << std::endl;
    iterator->getMatrix().fprint(os);
    iterator = iterator->getNext();
  } while (iterator != _head);
}
void CircularQueueOfMatrix::print() {
  fprint(std::cout);
}

const char *CircularQueueOfMatrix::NotEnoughOfItems::what() const noexcept {
  return "Not enough elements in matrix";
}
