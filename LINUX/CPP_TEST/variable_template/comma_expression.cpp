#include <iostream>
#include <string>
#include <vector>

using std::string;

void hello_world(const string &name) {
  std::cout << "Hello, " << name << std::endl;
}

template <typename... T> void hello_world(const string &name, T... args) {
  std::vector<int> arr = {(hello_world(args), 0)...};
}

template <typename... T> void test(T... args) {
  /*左折叠*/
  (std::cout << ... << args);
  std::cout << std::endl;
  /*右折叠*/
  ((std::cout << args), ...);
}

int main(int argc, char *argv[]) {

  /* hello_world(string("Kirito"), string("Kirito_1"), string("Kirito_2"),
              string("Kirito_3")); */

  test(string("Kirito"), string("Kirito_1"), string("Kirito_2"),
       string("Kirito_3"));

  return 0;
}
