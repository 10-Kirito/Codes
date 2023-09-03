#include <iostream>
#include <memory>

class Node {
  int _data;

public:
  std::shared_ptr<Node> ptr;
  Node(const int &data) : _data(data) {}
  ~Node() { std::cout << "delete" << _data << std::endl; }
};

int main(int argc, char *argv[]) {

  std::shared_ptr<Node> ptr1 = std::make_shared<Node>(1);
  std::shared_ptr<Node> ptr2 = std::make_shared<Node>(2);

  ptr1->ptr = ptr2;
  ptr2->ptr = ptr1;

  return 0;
}
