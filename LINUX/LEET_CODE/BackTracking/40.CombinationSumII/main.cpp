#include <algorithm>
#include <iostream>
#include <vector>
using std::vector;

class Solution {
  vector<vector<int>> result;
  vector<int> path;
  int sum = 0;

  void findCombination(const vector<int> &candidates, const int &target,
                       int index) {
    if (sum > target) {
      return;
    }
    if (sum == target) {
      result.push_back(path);
      return;
    }

    // If we write i >= 1, it will become remove duplicates on the same branch
    // else if we write i > index, it will become remove duplicates on the same
    // tree level. One is vertical and the other is horizontal.
    for (int i = index; i < candidates.size(); i++) {
      if ((i > index) && (candidates[i] == candidates[i - 1])) {
        continue;
      }
      path.push_back(candidates[i]);
      sum += candidates[i];
      findCombination(candidates, target, i + 1);
      path.pop_back();
      sum -= candidates[i];
    }
  }

public:
  vector<vector<int>> combinationSum2(vector<int> &candidates, int target) {
    std::sort(candidates.begin(), candidates.end());
    findCombination(candidates, target, 0);
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

// Input: candidates = [10,1,2,7,6,1,5], target = 8
// Output:
// [
// [1,1,6],
// [1,2,5],
// [1,7],
// [2,6]
// ]

int main(int argc, char *argv[]) {
  vector<int> candidates{10, 1, 2, 7, 6, 1, 5};

  Solution solution;
  output(solution.combinationSum2(candidates, 8), 1);

  return 0;
}
