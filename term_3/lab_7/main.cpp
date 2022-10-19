#include "CircularQueue.hpp"


int main() {
  CircularQueue<int> cqueue(5);

  cqueue.print();
  try {
    cqueue.remove();
  } catch (CircularQueueIsClear &e) {
    std::cout << e.what() << std::endl;
  }

  cqueue.add(1);
  cqueue.print();
  int a = cqueue.remove();
  cqueue.print();
  cqueue.add(1);
  cqueue.print();
  cqueue.add(2);
  cqueue.print();
  cqueue.add(3);
  cqueue.print();
  cqueue.add(4);
  cqueue.print();
  cqueue.add(5);
  cqueue.print();
  cqueue.add(6);
  cqueue.print();


  return 0;
}
