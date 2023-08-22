#include <iostream>

namespace A {
struct X {};
struct Y {};

void f(int i) { std::cout << "A::f(int i) is called!" << std::endl; }

void g(X x) { std::cout << "A::g(X x) is called!" << std::endl; }

} // namespace A

namespace B {
  void f(int i) {
    std::cout << "B::f(int i) is called!" << std::endl;
    f(i);
  }

  void g(A::X x) {
    std::cout << "B::g(X x) is called!" << std::endl;
    g(x);
  }

  void h(A::Y y) {
    h(y);
  }
}

int main (int argc, char *argv[])
{
  using B::f;
  f(1);
  
  return 0;
}
