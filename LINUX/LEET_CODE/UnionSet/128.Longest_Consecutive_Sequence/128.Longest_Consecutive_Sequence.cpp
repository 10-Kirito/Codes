#include <algorithm>
#include <iostream>
#include <numeric>
#include <unordered_map>
#include <vector>
using std::iota;
using std::unordered_map;
using std::vector;

class UnionSet {
  vector<int> size;
  vector<int> parent;
  int maxsize;

public:
  UnionSet(int size_) : size(size_, 1), parent(size_), maxsize{1} {
    iota(parent.begin(), parent.end(), 0);
  }

  void unite(int x, int y) {
    int left = find(x);
    int right = find(y);
    if (left != right) {
      size[left] += size[right];
      size[right] = size[left];
      parent[left] = right;
      maxsize = std::max(maxsize, size[left]);
    }
  }

  int find(int x) {
    if (parent[x] != x)
      parent[x] = find(parent[x]);
    return parent[x];
  }

  int getMaxSize() { return maxsize; }
};

class Solution {
public:
  int longestConsecutive(vector<int> &nums) {
    if (nums.empty()) {
      return 0;
    }
    unordered_map<int, int> mp;

    UnionSet unionset(nums.size());

    for (int i = 0; i < nums.size(); i++) {
      if (mp.find(nums[i]) != mp.end()) {
        continue;
      }

      if (mp.find(nums[i] - 1) != mp.end()) {
        unionset.unite(i, mp[nums[i] - 1]);
      }

      if (mp.find(nums[i] + 1) != mp.end()) {
        unionset.unite(i, mp[nums[i] + 1]);
      }

      mp[nums[i]] = i;
    }

    int result = unionset.getMaxSize();

    return result;
  }
};

int main(int argc, char *argv[]) {
  Solution solution;

  vector<int> test1 = {100, 4, 200, 1, 3, 2};
  vector<int> test2 = {0, 0};
  vector<int> test3 = {9, 1, 4, 7, 3, -1, 0, 5, 8, -1, 6};

  std::cout << solution.longestConsecutive(test3);

  return 0;
}
