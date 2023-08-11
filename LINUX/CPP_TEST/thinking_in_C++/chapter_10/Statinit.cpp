#include <iostream>
using namespace std;

int x = 100;
class WithStatic {
  static int x;
  static int y;

public:
  // WithStatic() : x(1), y(2) {}
  void print() const {
    cout << "WithStatic::x = " << x << endl;
    cout << "WithStatic::y = " << y << endl;
  }
};

int WithStatic::x = 1;
int WithStatic::y = 2;

int main (int argc, char *argv[])
{
  WithStatic ws;
  ws.print();
  return 0;
}
