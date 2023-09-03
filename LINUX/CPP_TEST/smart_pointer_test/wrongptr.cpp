#include <iostream>
#include <memory>

int main(int argc, char *argv[]) {
  int *a = new int;

  std::shared_ptr<int> p1(a);
  std::shared_ptr<int> p2(a);

  std::cout << "p1,use_count: " << p1.use_count() << std::endl;
  std::cout << "p2.use_count: " << p2.use_count() << std::endl;

  return 0;
}
