#include <iostream>
#include <string>
#include <vector>
using std::string;
using std::vector;

class Solution {
  vector<string> result;

  string IP;

  bool ifbig(const string &s) {
    if (atoi(s.c_str()) > 255) {
      return true;
    }
    return false;
  }

  void backtracking(const string &s, int startIndex) {
    if (startIndex > s.size()) {
      result.push_back(IP);
      return;
    }

    for (int i = startIndex; i < startIndex; i++) {
      string subs = s.substr(startIndex, i);
      if (ifbig(subs)) {
        return;
      }

      IP += subs;
      IP += ".";
      backtracking(s, i + 1);
      IP = IP.substr(0, IP.size() - subs.size() + 1);
    }
  }

public:
  vector<string> restoreIpAddresses(const string &s) {
    result.clear();
    IP.clear();

    backtracking(s, 0);
    return result;
  }
};

void print(const vector<string> &result, int index) {
  for (const auto &elem : result) {
    std::cout << elem << " ";
  }
}

int main(int argc, char *argv[]) {
  Solution solution;

  print(solution.restoreIpAddresses("25525511135"), 1);

  return 0;
}
