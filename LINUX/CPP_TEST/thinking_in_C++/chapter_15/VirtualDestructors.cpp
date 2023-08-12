// Behavior of virtual vs . non-virtual destructor
#include <iostream>
using namespace std;

class Base1 {
public:
  ~Base1() { cout << "~Base1()\n"; }
};

class Derived1 : public Base1 {
public:
  ~Derived1() { cout << "~Derived1()\n"; }
};

class Base2 {
public:
  virtual ~Base2() { cout << "~Base2()\n"; }
};

class Derived2 : public Base2 {
public:
  ~Derived2() { cout << "~Derived2()\n"; }
};

int main (int argc, char *argv[])
{
  Base1* bp = new Derived1;
  delete bp;

  cout << "--------------------------" << endl;
  Base2* bp2 = new Derived2;
  delete bp2;
  return 0;
}
