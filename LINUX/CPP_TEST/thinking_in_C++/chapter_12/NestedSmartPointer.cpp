#include "../required.h"
#include <iostream>
#include <vector>
using namespace std;

class Obj {
  static int i, j;

public:
  void f() { cout << i++ << endl; }
  void g() { cout << j++ << endl; }
};

int Obj::i = 47;
int Obj::j = 11;

// Container
class ObjContainer {
  vector<Obj *> a;

public:
  void add(Obj *obj) { a.push_back(obj); }
  class SmartPointer;
  friend SmartPointer;
  // Nested SmartPointer
  class SmartPointer {
    ObjContainer &oc;
    unsigned int index;

  public:
    SmartPointer(ObjContainer &objc) : oc(objc) { index = 0; }
    // Prefix
    bool operator++() {
      // if the size is overflow, return false
      if (index >= oc.a.size())
        return false;
      // if the next Obj Pointer is nullptr, return false
      if (oc.a[++index] == 0)
        return false;
      // everything is OK, return true, the SmartPointer++,
      // point to the next Object
      return true;
    }

    // Postfix
    // what we want to do is just move the iterator forward one unit.
    // So we needn't consider about the other thing, such as return
    // the before iterator.
    bool operator++(int) { return operator++(); }

    Obj *operator->() const {
      require(oc.a[index] != 0, "Zero value"
                                "returned by SmartPointer::operator->()");
      return oc.a[index];
    }
  };
  // Function to produce a smart pointer that points to the beginning of the
  // ObjContainer:
  SmartPointer begin() { return SmartPointer(*this); }
};

int main(int argc, char *argv[]) {
  const int sz = 10;
  Obj o[sz];
  ObjContainer oc;
  for (int i = 0; i < sz; i++) {
    oc.add(&o[i]);
  }

  ObjContainer::SmartPointer sp = oc.begin();
  do {
    sp->f();
    sp->g();
  } while (++sp);
  return 0;
}
