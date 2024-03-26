#include <iostream>

enum class test {
  ONE = 1,
  TWO = 2,
};

int main() {
  test a = test::ONE;
  std::cout << static_cast<int>(a) << std::endl;
  return 0;
}