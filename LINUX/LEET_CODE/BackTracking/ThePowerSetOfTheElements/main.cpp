#include <iostream>
#include <vector>

class Solution {
private:
  std::vector<std::vector<int>> result{};
  std::vector<int> path{};

  void get_powerset(const std::vector<int> &elements, int height) {
    if (height == elements.size()) {
      result.push_back(path);
      return;
    }

    path.push_back(elements[height]);
    get_powerset(elements, height + 1);

    path.pop_back();
    get_powerset(elements, height + 1);
  }

public:
  std::vector<std::vector<int>>
  get_the_powerset(const std::vector<int> &elements) {
    get_powerset(elements, 0);
    return result;
  }
};

template <typename T> void output(const std::vector<std::vector<T>> &sets, int index) {
  std::cout << "case" << index << ":";
  std::cout << "{";
  for (int i = 0; i < sets.size(); i++) {
    std::cout << "{";
    for (int j = 0; j < sets[i].size(); j++) {
      std::cout << sets[i][j];
      if (j != (sets[i].size() - 1)) {
        std::cout << ",";
      }
    }
    std::cout << "}";
    if (i != (sets.size() - 1)) {
      std::cout << ",";
    }
  }
  std::cout << "}" << std::endl;
}

int main(int argc, char *argv[]) {
  std::vector<int> elements{1, 2, 3, 4, 5, 6, 7, 8, 9};
  Solution solution;
  output(solution.get_the_powerset(elements), 1);
  return 0;
}
