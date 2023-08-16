#include <future>
#include <iostream>
#include <string>

class test {
  int a;
  int *ptr;

public:
  test() : a{0}, ptr{nullptr} {}
  test(const int &d, int *p = nullptr) : a{d}, ptr{p} {}
  void print() const {
    std::cout << "int :" << a << std::endl;
    std::cout << "int* :" << (ptr ? std::to_string(*ptr) : "nullptr")
              << std::endl;
  }
};

int main(int argc, char *argv[]) {
  int *a = new int(10);

  test b(1, a), c;
  std::swap(b, c);

  b.print();

  return 0;
}
