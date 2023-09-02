#include <iostream>
#include <memory>
#include <string>
#include <vector>

int main(int argc, char *argv[]) {
  std::shared_ptr<std::string> pNico(new std::string("nico"),
                                     [](std::string *p) {
                                       std::cout << "delete " << *p << std::endl;
                                       delete p;
                                     });
  std::shared_ptr<std::string> pJutta(new std::string("jutta"));

  // capitalize person names
  (*pNico)[0] = 'N';
  pJutta->replace(0, 1, "J");

  std::vector<std::shared_ptr<std::string>> whoMadeCoffee;

  whoMadeCoffee.push_back(pJutta);
  whoMadeCoffee.push_back(pJutta);
  whoMadeCoffee.push_back(pJutta);
  whoMadeCoffee.push_back(pNico);
  whoMadeCoffee.push_back(pNico);
  whoMadeCoffee.push_back(pJutta);
  whoMadeCoffee.push_back(pJutta);
  whoMadeCoffee.push_back(pJutta);

  // print all:
  for (auto ptr : whoMadeCoffee) {
    std::cout << *ptr << " ";
  }
  std::cout << std::endl;

  // change one share object:
  *pNico = "Nicolai";

  // print again:
  for (auto ptr : whoMadeCoffee) {
    std::cout << *ptr << " ";
  }
  std::cout << std::endl;

  std::cout << "pJutta use_count:" << whoMadeCoffee[0].use_count() << std::endl;

  std::cout << "--Test deleter:" << std::endl;
  pJutta = nullptr;
  std::cout << "pJutta use_count:" << whoMadeCoffee[0].use_count() << std::endl;

  std::cout << "--Test container.resize:" << std::endl;
  whoMadeCoffee.resize(3);
  std::cout << "pJutta use_count:" << whoMadeCoffee[0].use_count() << std::endl;
  return 0;
}
