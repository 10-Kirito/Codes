// overload unary operators
#include <iostream>
#include <iterator>
using namespace std;

class Integer {
  long i;
  Integer *This() { return this; }

public:
  Integer(long ll = 0) : i(ll) {}
  long geti() const { return i; }
  // No side effects takes const& argument:
  friend Integer *operator&(Integer &a);
  friend int operator!(const Integer &a);
  friend const Integer operator~(const Integer &a);
  friend const Integer operator-(const Integer &a);
  friend const Integer &operator++(Integer &a);
  friend const Integer operator++(Integer &a, int);
  friend const Integer &operator--(Integer &a);
  friend const Integer operator--(Integer &a, int);
};

// Global operators:
const Integer &operator+(const Integer &a) {
  cout << "+Integer\n";
  return a;
}

const Integer operator-(const Integer &a) {
  cout << "-Integer\n";
  return Integer(-a.i);
}

const Integer operator~(const Integer &a) {
  cout << "~Integer\n";
  return Integer(~a.i);
}

Integer *operator&(Integer &a) {
  cout << "&Integer\n";
  return a.This();
}

int operator!(const Integer &a) {
  cout << "!Integer\n";
  return !a.i;
}

// Prefix; return incremented value
const Integer &operator++(Integer &a) {
  cout << "++Integer\n";
  a.i++;
  return a;
}

// Postfix: return the value before increment:
const Integer operator++(Integer &a, int) {
  cout << "Integer++\n";
  Integer before(a.i);
  a.i++;
  return before;
}

// Prefix; return incremented value
const Integer &operator--(Integer &a) {
  cout << "--Integer\n";
  a.i--;
  return a;
}

// Postfix: return the value before increment:
const Integer operator--(Integer &a, int) {
  cout << "Integer--\n";
  Integer before(a.i);
  a.i--;
  return before;
}

int main(int argc, char *argv[]) {
  Integer a(10);
  +a;
  -a;
  ~a;
  Integer *ip = &a;
  !a;
  ++a;
  a++;
  --a;
  a--;
  return 0;
}
