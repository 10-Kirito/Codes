#include <array>
#include <iostream>
#include <vector>

int main(int argc, char *argv[]) {
  std::vector<int> vector_1{1, 2, 3, 4, 5};
  std::vector<int> vector_2{6, 7, 8, 9, 10};
  auto iter = vector_1.begin();
  std::cout << "------vector test------" << std::endl;
  std::cout << "Before exchange: " << *iter << std::endl;
  swap(vector_1, vector_2);
  std::cout << "After exchange: " << *iter << std::endl;

  std::cout << "-------array test------" << std::endl;
  std::array<int, 10> array_1{1, 2, 3, 4};
  std::array<int, 10> array_2{5, 6, 7, 8, 9};
  auto iter_array = array_1.begin();
  std::cout << "Before exchange: " << *iter_array << std::endl;
  swap(array_1, array_2);
  std::cout << "After exchange: " << *iter_array << std::endl;

  return 0;
}
