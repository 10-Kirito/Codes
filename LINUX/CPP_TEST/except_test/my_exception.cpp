#include "header.h"
#include <iostream>

using namespace std;

void testfunc() noexcept(false) { throw MyException(); }

int main(int argc, char *argv[]) {

  try {
    testfunc();
  } catch (const exception &e) {
    cerr << "Caught exception: " << e.what() << endl;
  }

  return 0;
}
