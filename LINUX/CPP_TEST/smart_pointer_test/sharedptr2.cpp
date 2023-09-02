// Test Array shared_ptr's usage:
//
#include <iostream>
#include <memory>

int main(int argc, char *argv[]) {
  // the following operation is wrong although compiles and run
  // std::shared_ptr<int> p(new int[10]);
  // we need to define our own deleter:
  std::shared_ptr<int> p(new int[10], [](int *p) { delete[] p; });
  // another solution:
  std::shared_ptr<int> q(new int[10], std::default_delete<int[]>());

  std::cout << "Hello, World!" << std::endl;

  std::shared_ptr<int []> s(new int [10]);

  return 0;
}
