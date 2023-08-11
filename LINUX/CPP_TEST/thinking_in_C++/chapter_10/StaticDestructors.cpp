#include <fstream>
using namespace std;

ofstream out("statdest.out"); //Trace file

class Obj {
  char _c;
  public:
  Obj(char c) :_c(c) {
    out << "Obj::Obj() for " << _c << endl;
  }

  ~Obj() {
    out << "Obj::Obj() for " << _c << endl;
  }
};

Obj a('a');

void f() {
  static Obj b('b');
}

void g() {
  static Obj c('c');
}

int main (int argc, char *argv[])
{
  out << "inside main()" << endl;
  f();
  // g();
  out << "leaving main()" << endl;
  return 0;
}
