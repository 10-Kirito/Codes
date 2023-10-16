#include <iostream>

/*
 *简单的测试一下如何获取参数包的个数
 */

template <typename... T> void f(T... args) {
  std::cout << sizeof...(args) << std::endl;
}

int main(int argc, char *argv[]) {
  f(0);
  f(0, 1, 1, 1, 1, 1);

  return 0;
}
