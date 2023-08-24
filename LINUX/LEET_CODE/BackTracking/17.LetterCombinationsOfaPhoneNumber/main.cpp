#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::unordered_map;
using std::vector;

class Solution {
private:
  vector<string> result;
  string path;
  unordered_map<char, string> map{{'2', "abc"}, {'3', "def"}, {'4', "ghi"},
                                  {'5', "jkl"}, {'6', "mno"}, {'7', "pqrs"},
                                  {'8', "tuv"}, {'9', "wxyz"}};

  void backtracking(string digits, int index) {
    if (index == digits.size()) {
      result.push_back(path);
      return;
    }

    for (int i = 0; i < map[digits[index]].size(); i++) {
      path += map[digits[index]][i];
      backtracking(digits, index + 1);
      path = path.substr(0, path.size() - 1);
    }
  }

public:
  vector<string> letterCombinations(string digits) {
    if (digits.size() == 0) {
      return vector<string>();
    
    }
    result.clear();
    path = "";
    backtracking(digits, 0);
    return result;
  }
};

void output(const vector<string> &sets, int index) {
  cout << "case" << index << ":";
  cout << "[";
  for (auto i = sets.begin(); i != sets.end(); i++) {
    cout << "\""<< *i << "\"";
    if (i != (sets.end() - 1)) {
      cout << ",";
    }
  }
  cout << "]" << endl;
}

int main(int argc, char *argv[]) {
  string s1 = "23";
  string s2 = "";
  string s3 = "2";

  Solution solution;
  output(solution.letterCombinations(s1), 1);
  output(solution.letterCombinations(s2), 2);
  output(solution.letterCombinations(s3), 3);
  return 0;
}
