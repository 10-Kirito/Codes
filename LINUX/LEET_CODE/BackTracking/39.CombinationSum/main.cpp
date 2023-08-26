#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>

using std::vector;

class Solution {
  vector<vector<int>> result;
  vector<int> path;

  int sum_of_vector() {
    int sum = 0;
    for (const auto &elem : path) {
      sum += elem;
    }
    return sum;
  }

  // check out if the path already exist in result:
  bool check() {
    for (auto &elem : result) {
      if (check_exist(elem)) {
        return true;
      }
    }
    return false;
  }

  bool check_exist(vector<int> vector1) {
    vector<int>::iterator iter;
    for (auto &elem : path) {
      if ((iter = std::find(vector1.begin(), vector1.end(), elem)) ==
          vector1.end()) {
        return false;
      }
      vector1.erase(iter);
    }
    return true;
  }

  // BackTracing Algorithm
  // The method is very slow: because we consider too much useless situations
  // Runtime: 1479ms;
  // Memory: 257.6MB;
  void get_combination(vector<int> &candidates, int target) {
    if (sum_of_vector() == target) {
      if (check()) {
        return;
      }
      result.push_back(path);
      return;
    } else if (sum_of_vector() > target) {
      return;
    }

    for (auto iter = candidates.begin(); iter != candidates.end(); iter++) {
      if (sum_of_vector() > target) {
        break;
      }
      path.push_back(*iter);
      get_combination(candidates, target);
      path.pop_back();
    }
  }

  void get_combination(vector<int> &candidates, int target, int startIndex,
                       bool) {
    if (sum_of_vector() > target) {
      return;
    }
    if (sum_of_vector() == target) {
      result.push_back(path);
      return;
    }

    for (int i = startIndex; i < candidates.size(); i++) {
      path.push_back(candidates[i]);
      // it means we can put the same element into path
      get_combination(candidates, target, i, true);
      path.pop_back();
    }
  }

public:
  // BackTracing Algorithm
  // The method is very slow: because we consider too much useless situations
  // Runtime: 1479ms;
  // Memory: 257.6MB;

  vector<vector<int>> combinationSum(vector<int> &candidates, int target) {
    path.clear();
    result.clear();
    get_combination(candidates, target);
    std::cout << "The size of result is " << result.size() << std::endl;
    return result;
  }

  // BackTracing Algorithm
  // Runtime: 9ms;
  // Memory: 10.9MB;

  vector<vector<int>> combinationSum(vector<int> &candidates, int target,
                                     bool) {
    path.clear();
    result.clear();
    get_combination(candidates, target, 0, true);
    return result;
  }
};

template <typename T> void output(const vector<vector<T>> &sets, int index) {
  std::cout << "case" << index << ":";
  std::cout << "[";
  for (int i = 0; i < sets.size(); i++) {
    std::cout << "[";
    for (int j = 0; j < sets[i].size(); j++) {
      std::cout << sets[i][j];
      if (j != (sets[i].size() - 1)) {
        std::cout << ",";
      }
    }
    std::cout << "]";
    if (i != (sets.size() - 1)) {
      std::cout << ",";
    }
  }
  std::cout << "]" << std::endl;
}

int main(int argc, char **argv) {
  Solution solution;

  vector<int> candidates_1{2, 3, 6, 7};
  vector<int> candidates_2{7, 3, 2};
  output(solution.combinationSum(candidates_1, 7, true), 1);
  output(solution.combinationSum(candidates_2, 18, true), 2);

  return 0;
}
