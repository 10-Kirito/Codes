#include <iostream>
#include <memory>

class Node {
public:
  int data;
  Node(int value) : data(value) {}
  ~Node() { std::cout << "deconstruction" << std::endl; }

  // 使用 shared_ptr 来相互引用
  std::shared_ptr<Node> next;
};

Node* ptr1 = nullptr, *ptr2 = nullptr;

void test() {
  using ptype = std::shared_ptr<Node>;

  ptype node1 = std::make_shared<Node>(1);
  ptype node2 = std::make_shared<Node>(2);

  node1->next = node2;
  node2->next = node1;

  ptr1 = const_cast<Node*>(node1.get());
  ptr2 = const_cast<Node*>(node2.get());
}

int main() {
  using std::cout;
  using std::endl;

  test();

  cout << (ptr1->data) << endl;
  cout << (ptr2->data) << endl;

  delete ptr1;
  delete ptr2;
}
