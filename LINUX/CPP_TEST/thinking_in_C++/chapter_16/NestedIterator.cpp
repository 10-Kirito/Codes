#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <ostream>
#include <string>

using namespace std;

class IntStack {
  enum { ssize = 100 };
  int stack[ssize];
  int top;

public:
  IntStack() : top(0) {}
  void push(int i) {
    if (top >= ssize) {
      cout << "Too mant push()es" << endl;
      exit(0);
    }

    stack[top++] = i;
  }

  int pop() {
    if (top <= 0) {
      cout << "Too many pop()s";
      exit(0);
    }
    return stack[--top];
  }

  class iterator;
  friend class iterator;
  class iterator {
    IntStack &s;
    int index;

  public:
    iterator(IntStack &is) : s(is), index(0) {}
    // To create the end sentinel iterator:
    iterator(IntStack &is, bool) : s(is), index(s.top) {}
    int current() const { return s.stack[index]; }
    int operator++() {
      if (index >= s.top) {
        cout << "iterator moved out of range" << endl;
        exit(0);
      }
      return s.stack[++index];
    }

    int operator++(int) {
      if (index >= s.top) {
        cout << "iterator moved out of range" << endl;
        exit(0);
      }
      return s.stack[index++];
    }

    iterator &operator+=(int amount) {
      if (index + amount >= s.top) {
        cout << "IntStack::iterator::operator+=() \n tried to move out of "
                "bounds \n";
        exit(0);
      }
      index += amount;
      return *this;
    }

    // To see if you're at the end:
    bool operator==(const iterator &rv) const { return index == rv.index; }
    bool operator!=(const iterator &rv) const { return index != rv.index; }

    friend ostream &operator<<(ostream &os, const iterator &it) {
      return os << it.current();
    }
  };

  // access the begin() and the end():
  iterator begin() { return iterator(*this); }

  iterator end() { return iterator(*this, true); }
};

int main(int argc, char *argv[]) {
  IntStack is;
  for (int i = 0; i < 20; i++) {
    is.push(i);
  }

  cout << "Traverse the whole IntStack\n" << flush;
  IntStack::iterator it = is.begin();
  while (it != is.end()) {
    cout << it++ << endl;
  }
  IntStack::iterator start = is.begin(), end = is.begin();

  start += 5, end += 15;
  cout << "start = " << start << endl;
  cout << "end = " << end << endl;
  while (start != end) {
    cout << start++ << endl;
  }

  return 0;
}
