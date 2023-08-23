#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char *argv[]) {
  vector<string> vec{"H", "e", "l", "l", "o"};
  // vector<string> v2("a", "v", "c");  !!!wrong
  for (auto e : vec) {
    cout << e;
  }

  cout << "vec: size: " << vec.size() << endl;
  cout << "vec: capacity:" << vec.capacity() << endl;
  vec.push_back("!");
  cout << "vec: size: " << vec.size() << endl;
  cout << "vec: capacity:" << vec.capacity() << endl;
  vec.reserve(50);
  cout << "vec: size: " << vec.size() << endl;
  cout << "vec: capacity:" << vec.capacity() << endl;
  vec.shrink_to_fit();
  cout << "vec: size: " << vec.size() << endl;
  cout << "vec: capacity:" << vec.capacity() << endl;


  return 0;
}
