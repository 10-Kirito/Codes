#include "Useful.h"
#include <iostream>

using namespace std;

class Y : public X {
  int i;

public:
  Y() { i = 0; }
  int change() {
    i = permute();
    return i;
  }

  void set(int ii) {
    i = ii;
    X::set(13);
  }

  void print() {
    cout << "the value of i is " << i << endl;
    cout << "the value of x_i is " << read() << endl;
  }
};

int main(int argc, char *argv[]) {
  cout << "sizeof(X) = " << sizeof(X) << endl;
  cout << "sizeif(Y) = " << sizeof(Y) << endl;
  Y D;
  D.change();

  D.read();
  D.permute();

  D.set(12);
  D.print();
  return 0;
}
