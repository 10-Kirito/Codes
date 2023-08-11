#include <iostream>
using namespace std;

class Byte {
  unsigned char b;

public:
  Byte(unsigned char bb = 0) : b(bb) {}
  const Byte &operator+() const {
    cout << "+Byte\n";
    return *this;
  }

  const Byte operator-() const {
    cout << "-Byte\n";
    return Byte(-b);
  }

  const Byte operator~() const {
    cout << "~Byte\n";
    return Byte(~b);
  }

  Byte operator!() const {
    cout << "!Byte\n";
    return Byte(!b);
  }

  Byte *operator&() { return this; }

  // side effects: non-const member function:
  const Byte &operator++() {
    cout << "++Byte\n";
    b++;
    return *this;
  }

  const Byte operator++(int) {
    cout << "Byte++\n";
    Byte before(b);
    b++;
    return before;
  }

  // side effects: non-const member function:
  const Byte &operator--() {
    cout << "--Byte\n";
    b--;
    return *this;
  }

  const Byte operator--(int) {
    cout << "Byte--\n";
    Byte before(b);
    b--;
    return before;
  }
};
