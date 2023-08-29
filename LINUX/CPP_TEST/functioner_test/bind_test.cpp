#include <functional>
#include <iostream>
using namespace std::placeholders;

void fun(int n1, int n2, int n3) {
  std::cout << n1 << " " << n2 << " " << n3 << std::endl;
}

void ref_test(int & test) {
  test = 100;
}

int main (int argc, char *argv[])
{
  
  auto f1 = std::bind(fun, 11, 22, _1);
  f1(33);

  auto f2 = std::bind(fun, _2, _1, 33);
  f2(22, 11);

  int test = 10;
  auto f3 = std::bind(ref_test, std::ref(test));
  f3();
  std::cout << "After f3, the value of test is " << test << std::endl;
  return 0;
}
