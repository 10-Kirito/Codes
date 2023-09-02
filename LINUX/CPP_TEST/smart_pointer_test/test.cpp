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

int main() {
  std::shared_ptr<Node> node1 = std::make_shared<Node>(1);
  std::shared_ptr<Node> node2 = std::make_shared<Node>(2);

  // 相互引用
  node1->next = node2;
  node2->next = node1;

  std::cout << "node1 " << node1.use_count() << std::endl;
  std::cout << "node2 " << node2.use_count() << std::endl;

  // 输出节点的数据
  // std::cout << "Node 1 data: " << node1->data << std::endl;
  // std::cout << "Node 2 data: " << node2->data << std::endl;

  // save raw pointer
  Node* ptr_node1 = const_cast<Node*>(node1.get());
  Node* ptr_node2 = const_cast<Node*>(node2.get());

  node1 = nullptr;
  std::cout << "node1 " << node1.use_count() << std::endl;
  std::cout << "node2 " << node2.use_count() << std::endl;

  using std::cout;
  using std::endl;
cout << "node1.get(): " << node1.get() << endl;
cout << "node2.get(): " << node2.get() << endl;

  cout << "raw pointer1->data: " << (ptr_node1->data) << endl;
  cout << "raw pointer2->data: " << (ptr_node2->data) << endl;

  return 0;
}
