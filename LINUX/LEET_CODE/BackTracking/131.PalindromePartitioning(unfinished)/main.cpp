#include <iostream>
#include <string>
#include <vector>
using std::cout;
using std::endl;
using std::string;
using std::vector;

class Solution {
  vector<vector<string>> result;
  vector<string> path;

  bool isPalindrome(const string &s, int start, int end) {
    for (int i = start, j = end; i < j; i++, j--) {
      if (s[i] != s[j]) {
        return false;
      }
    }
    return true;
  }

  void subpartition(const string &s, int startindex) {

    if (startindex >= s.size()) {
      result.push_back(path);

      return;
    }

    for (int i = startindex; i < s.size(); i++) {
      if (isPalindrome(s, startindex, i)) {
        string str = s.substr(startindex, i - startindex + 1);
        path.push_back(str);
      } else {
        continue;
      }

      subpartition(s, i + 1);

      path.pop_back();
    }
  }

public:
  vector<vector<string>> partition(string s) {
    result.clear();
    path.clear();

    subpartition(s, 0);

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

// Example 1:

// Input: s = "aab"
// Output: [["a","a","b"],["aa","b"]]
// Example 2:

// Input: s = "a"
// Output: [["a"]]

int main(int argc, char *argv[]) {
  string s = "aab";

  Solution solution;

  output(solution.partition(s), 1);

  return 0;
}
