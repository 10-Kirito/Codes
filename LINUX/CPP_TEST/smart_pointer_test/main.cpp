#include <memory>

int main(int argc, char *argv[]) {
  int *i = new int;

  std::shared_ptr<int> sp1(i);

  std::shared_ptr<int> sp2(sp1);

  return 0;
}
