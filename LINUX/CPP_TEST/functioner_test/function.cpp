#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

int add(int i, int j) { return i + j; }

int (*addptr)(int i, int j) = add;

auto mod = [](int i, int j) { return i % j; };

class divide {
public:
  int operator()(int i, int j) { return i / j; }
};

int main(int argc, char *argv[]) {
  std::vector<std::string> vec{"111", "222", "333", "555"};

  std::sort(vec.begin(), vec.end(), std::greater<std::string>());

  std::for_each(vec.begin(), vec.end(),
                [](const std::string &s) { std::cout << s << " "; });

  std::function<int(int, int)> f1 = add;
  std::function<int(int, int)> f2 = [](int i, int j) { return i % j; };
  std::function<int(int, int)> f3 = addptr;
  std::function<int(int, int)> f4 = divide();

  return 0;
}
