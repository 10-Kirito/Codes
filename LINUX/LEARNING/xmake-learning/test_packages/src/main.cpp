/* #include <iostream>

using namespace std;

class MyClass {
public:
  void printf(char *) { cout << "This is char!\n"; }
  void printf(int) { cout << "This is char!\n"; }
};

int main(int argc, char **argv) {
  MyClass s;
  // s.printf(NULL);
  s.printf(nullptr);

  return 0;
}
 */

// test cyclic reference:
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