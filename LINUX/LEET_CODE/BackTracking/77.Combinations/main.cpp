#include <iostream>
#include <vector>
using namespace std;

class Solution {
private:
  vector<int> path;
  vector<vector<int>> result;
  void backtracking(int n, int k, int index) {
    // if path.size() == k, then it means that we have traversed to the leaf
    // node, that is to say, we have found a qualified subset
    if (path.size() == k) {
      result.push_back(path);
      return;
    }

    for (int i = index; i <= n - (k - path.size()) + 1; i++) {
      path.push_back(i);
      backtracking(n, k, i + 1);
      // backtracking: undo this step!
      path.pop_back();
    }
  }

public:
  vector<vector<int>> combine(int n, int k) {
    path.clear();
    result.clear();
    backtracking(n, k, 1);
    return result;
  }

  vector<vector<int>> returnsets() const { return result; }
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

  solution.combine(4, 2);
  output(solution.returnsets(), 1);

  solution.combine(20, 9);
  output(solution.returnsets(), 2);
  return 0;
}
