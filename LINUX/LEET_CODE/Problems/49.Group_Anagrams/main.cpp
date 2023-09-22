#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
using std::string;
using std::vector;

class Solution {
public:
  vector<vector<string>> groupAnagrams(vector<string> &strs) {
    std::unordered_map<string, vector<string>> map;

    for (string elem: strs) {
      string t = elem;
      std::sort(t.begin(), t.end());
      map[t].push_back(elem);
    }

    vector<vector<string>> anagrams;

    for (auto elem : map) {
      anagrams.push_back(elem.second);
    }
    return anagrams;
  }
};

/* Example 1:

Input: strs = ["eat","tea","tan","ate","nat","bat"]
Output: [["bat"],["nat","tan"],["ate","eat","tea"]]
Example 2:

Input: strs = [""]
Output: [[""]]
Example 3:

Input: strs = ["a"]
Output: [["a"]]
 */

void showResult(const vector<vector<string>> &result) {
  for (const auto &set : result) {
    for (const auto &elem : set) {
      std::cout << elem << " ";
    }
    std::cout << std::endl;
  }
}

int main(int argc, char *argv[]) {
  string str_1{"abcd"};
  string str_2{"dcba"};

  vector<string> strs = {"eat", "tea", "tan", "ate", "nat", "bat"};

  Solution solutioin;

  showResult(solutioin.groupAnagrams(strs));

  return 0;
}
