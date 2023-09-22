#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using std::string;
using std::vector;

class Solution {
  vector<vector<string>> result;
  vector<string> set;

public:
  vector<vector<string>> groupAnagrams(vector<string> &strs) {
    // if strs is NULL, return NULL
    if (strs.empty()) {
      return result;
    }
    // We traverse the array each time, put all the strings that form anagrams
    // with the first string into the result, and delete the corresponding
    // strings from the original array
    while (!strs.empty()) {
      tools(strs);
    }
    return result;
  }

  void tools(vector<string> &strs) {
    set.clear();
    string temp = strs[0];

    // initialization
    set.push_back(temp);
    strs.erase(strs.begin());
    if (strs.empty()) {
      result.push_back(set);
      return;
    }
    for (auto it = strs.begin(); it != strs.end();) {
      if (isAnagram(temp, *it)) {
        set.push_back(*it);
        it = strs.erase(it);
      } else {
        ++it;
      }
    }
    result.push_back(set);
  }

  // Check two strings if is Anagram:
  bool isAnagram(const string &str_1, const string &str_2) {
    int record[26] = {0};
    for (int i = 0; i < str_1.size(); ++i) {
      record[str_1[i] - 'a']++;
    }
    for (int i = 0; i < str_2.size(); ++i) {
      record[str_2[i] - 'a']--;
    }
    for (int i = 0; i < 26; ++i) {
      if (record[i] != 0) {
        return false;
      }
    }
    return true;
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
