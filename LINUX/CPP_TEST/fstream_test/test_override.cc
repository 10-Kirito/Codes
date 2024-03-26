

#include <iostream>
class Base {
public:
  virtual void f() const { std::cout << "I'm Base object" << std::endl; }
};

class Derived : public Base {
public:
  void f() const override { std::cout << "I'm Derived object" << std::endl; }
};

void test(Base *base) { base->f(); }

int main() {
  test(new Derived());
  return 0;
}