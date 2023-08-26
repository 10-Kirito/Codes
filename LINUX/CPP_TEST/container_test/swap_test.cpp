#include <forward_list>
#include <ios>
#include <iostream>
#include <vector>

int main(int argc, char *argv[]) {
  std::vector<int> vector_1{1, 2, 3, 4, 5, 6, 7};
  std::cout << "vector_1.size(): " << vector_1.size() << std::endl;

  std::cout << "vector_1.max_size(): " << vector_1.max_size() << std::endl;
  std::cout << "vector_1.empty(): " << std::boolalpha << vector_1.empty()
            << std::endl;

  std::forward_list<int> forward_list{1, 2, 3, 4, 5, 6, 7};
  // std::cout << "forward_list.size(): " << forward_list.size() << std::endl;
  std::cout << "forward_list.max_size(): " << forward_list.max_size()
            << std::endl;
  std::cout << "forward_list.empty(): " << forward_list.empty() << std::endl;

  return 0;
}
