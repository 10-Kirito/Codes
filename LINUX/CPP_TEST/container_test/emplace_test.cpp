#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

struct A {
  std::string s;
  A(const std::string &str) : s(std::move(str)) {
    std::cout << " constructed\n";
  }
  A(const A &o) : s(o.s) { std::cout << " copy constructed\n"; }
  A(A &&o) : s(std::move(o.s)) { std::cout << " move constructed\n"; }
  A &operator=(const A &other) {
    s = other.s;
    std::cout << " copy assigned\n";
    return *this;
  }
  A &operator=(A &&other) {
    s = std::move(other.s);
    std::cout << "move assigned\n";
    return *this;
  }
};

int main(int argc, char *argv[]) {
  std::vector<A> container;
  std::cout << "container.capacity(): " << container.capacity() << std::endl;
  container.reserve(10);
  std::cout << "container.capacity(): " << container.capacity() << std::endl;
  std::cout << "construct 2 times A:\n";
  A two{"two"};
  A three{"three"};

  std::cout << "emplace:\n";
  container.emplace(container.end(), "one");

  std::cout << "emplace with A&:\n";
  container.emplace(container.end(), two);

  std::cout << "emplace with A&&:\n";
  container.emplace(container.end(), std::move(two));

  std::cout << "content:\n";

  for (const auto &elem : container) {
    std::cout << elem.s << " ";
  }
  std::cout << "\n";

  return 0;
}
