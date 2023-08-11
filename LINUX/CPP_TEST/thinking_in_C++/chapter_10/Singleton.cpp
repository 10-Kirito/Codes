// Static member of same type, ensures that 
// only one object of this type exists.
// Also referred to as the "singleton" pattern.

#include <iostream>
using namespace std;

class Egg {
  static Egg e;
  int i;
  Egg(int ii) : i(ii) {}
  Egg(const Egg &); // Prevent copy-construction
                    // Egg e = *Egg::instance();
                    // Egg e2(*Egg::instance());

public:
  static Egg *instance() { return &e; }
  int val() const { return i; }
};

Egg Egg::e(47);

int main (int argc, char *argv[])
{
  // Egg x(1);
  cout << Egg::instance()->val() << endl;
  return 0;
}
