#include <iostream>
#include <vector>
using std::vector;

class Solution {
  vector<vector<int>> result;
  vector<int> path;

  void backtracking(const vector<int> &nums, int index) {
    if (index == nums.size()) {
      result.push_back(path);
      return;
    }

    path.push_back(nums[index]);
    backtracking(nums, index + 1);
    path.pop_back();
    backtracking(nums, index + 1);
  }

public:
  vector<vector<int>> subsets(vector<int> &nums) {
    result.clear();
    path.clear();
    backtracking(nums, 0);
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



// Example 1:

// Input: nums = [1,2,3]
// Output: [[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]
// Example 2:

// Input: nums = [0]
// Output: [[],[0]]
int main(int argc, char *argv[]) {
  vector<int> nums{1, 2, 3};
  Solution solution;

  output(solution.subsets(nums), 1);


  return 0;
}
