#include <iostream>
#include <string>

using std::string;

void hello_world(const string &name) {
  std::cout << "Hello, " << name << std::endl;
}

template <typename... T> void hello_world(const string &name, T... args) {
  hello_world(name);
  hello_world(args...);
}

int main(int argc, char *argv[]) {

  hello_world(string("Kirito"), string("Kirito_1"), string("Kirito_2"),
              string("Kirito_3"));

  return 0;
}
