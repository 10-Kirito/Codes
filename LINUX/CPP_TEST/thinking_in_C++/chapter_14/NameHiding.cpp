#include <iostream>
#include <string>
using namespace std;

class Base {
public:
  int f() const {
    cout << "Base::f()\n";
    return 1;
  }

  int f(string) const { return 1; }
  void g() {}
};

class Derived1 : public Base {
public:
  void g() const {}
};

class Derived2 : public Base {
public:
  // Redefinition
  int f() const {
    cout << "int Derived2::f() const\n";
    return 2;
  }
  int f(string) const {
    cout << "int Derived2::f(string) const\n";
    return 2;
  }

};

class Derived3 : public Base {
public:
  // Change return type:
  void f() const { cout << "void Derived3::f() const\n"; }
};

class Derived4 : public Base {
public:
  // Change return type:
  void f(int) const { cout << "void Derived4::f(int) const\n"; }
};

int main (int argc, char *argv[])
{
  string s("hello");
  cout << "--------------Base---------------" << endl;
  Base base;
  base.f();
  cout << "--------------Derived1---------------" << endl;
  Derived1 derived1;
  derived1.f();

  cout << "--------------Derived2---------------" << endl;
  Derived2 derived2;
  derived2.f();

  cout << "--------------Derived3---------------" << endl;
  Derived3 derived3;
  derived3.f();
  
  cout << "--------------Derived4---------------" << endl;
  Derived4 derived4;
  derived4.f(4);

  return 0;
}
