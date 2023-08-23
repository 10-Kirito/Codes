#include <iostream>
#include <string>

int main(int argc, char *argv[]) {

  std::string world;
  std::string test(10, 'c');
  std::cout << test << std::endl;

  // while (std::cin >> world) {
  //   std::cout << world << std::endl;
  // }
  while (std::getline(std::cin, world)) {
    std::cout << world << std::endl;
  }
  return 0;
}
