#include <cmath>
#include <iostream>
template <typename... T> void do_something(T... args) {
  auto temp = {args...};
  for (auto &v : temp) {
    std::cout << v << std::endl;
  }
}

template <typename... T> void do_something_else(T... args) {
  auto temp = {
      ([&args] { std::cout << "hello, world!" << std::endl; }(), 1)...};

  auto temp1 = {(args * args)...};
  for (auto &v : temp1) {
    std::cout << v << " ";
  }
  std::cout << std::endl;
  auto temp2 = {(std::sin(args))...};
  for (auto &v : temp2) {
    std::cout << v << " ";
  }
  std::cout << std::endl;
  auto temp3 = {(std::sin(args) + args)...};
  for (auto &v : temp3) {
    std::cout << v << " ";
  }
  std::cout << std::endl;
}
int main(int argc, char *argv[]) {
  do_something_else(1, 2, 3, 4, 5, 6);
  return 0;
}
