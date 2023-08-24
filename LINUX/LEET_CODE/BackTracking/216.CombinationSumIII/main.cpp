#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::vector;

class Solution {
private:
  // sum of nodes in path
  int path_sum = 0;
  vector<int> path;
  vector<vector<int>> result;
  void backtracking(int k, int sum, int index) {
    bool flag = true;
    if (path_sum == sum && path.size() == k) {
      result.push_back(path);
      return;
    } else if (path_sum > sum || path.size() > k) {
      return;
    }

    for (int i = index; i <= 9; i++) {
      path_sum += i;
      path.push_back(i);
      backtracking(k, sum, i + 1);
      path_sum -= i;
      path.pop_back();
      if ((path_sum + i) > sum) {
        return;
      }
    }
  }

public:
  vector<vector<int>> combinationSum3(int k, int n) {
    path.clear();
    result.clear();
    backtracking(k, n, 1);
    return result;
  }
};

template <typename T> void output(const vector<vector<T>> &sets, int index) {
  cout << "case" << index << ":";
  cout << "[";
  for (int i = 0; i < sets.size(); i++) {
    cout << "[";
    for (int j = 0; j < sets[i].size(); j++) {
      cout << sets[i][j];
      if (j != (sets[i].size() - 1)) {
        cout << ",";
      }
    }
    cout << "]";
    if (i != (sets.size() - 1)) {
      cout << ",";
    }
  }
  cout << "]" << endl;
}
int main(int argc, char *argv[]) {
  Solution solution;
  output(solution.combinationSum3(3, 7), 1);
  output(solution.combinationSum3(9, 45), 2);
  output(solution.combinationSum3(3, 9), 3);

  return 0;
}
