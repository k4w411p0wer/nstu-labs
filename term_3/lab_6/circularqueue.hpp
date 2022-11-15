#pragma once

#include "matrix.hpp"
#include <exception>
#include <ostream>


class CircularQueueOfMatrixNode {
  private:
  CircularQueueOfMatrixNode *_prev;
  CircularQueueOfMatrixNode *_next;
  Matrix &_data;

  public:
  CircularQueueOfMatrixNode(Matrix &);
  ~CircularQueueOfMatrixNode() = default;

  CircularQueueOfMatrixNode *getPrev();
  void setPrev(CircularQueueOfMatrixNode *);
  CircularQueueOfMatrixNode *getNext();
  void setNext(CircularQueueOfMatrixNode *);
  Matrix &getMatrix();
};

class CircularQueueOfMatrix {
  private:
  CircularQueueOfMatrixNode *_head;

  public:
  CircularQueueOfMatrix();
  ~CircularQueueOfMatrix();
  void add(Matrix &);
  Matrix &remove();
  void fprint(std::ostream &);
  void print();

  class NotEnoughOfItems : public std::exception {
public:
    const char *what() const noexcept;
  };
};
