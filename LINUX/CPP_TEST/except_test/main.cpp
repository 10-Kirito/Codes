// Test what will happen if we throw except in a noexcept function
#include <iostream>
#include <stdexcept>
using namespace std;

void func() noexcept { throw runtime_error("An exception occured!"); }

int main(int argc, char *argv[]) {
  try {
    func();
  } catch (const exception &e) {
    cerr << "Caught exception: " << e.what() << endl;
  }
  return 0;
}
