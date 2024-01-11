#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
using namespace std;

class Solution {
public:
  int countComponents(int n, vector<vector<int>> &edges) {
    // 初始化并查集
    vector<int> union_set(n);
    iota(union_set.begin(), union_set.end(), 0);
    int count = n;

    for (auto edge : edges) {
      unite(union_set, count, edge[0], edge[1]);
    }
    return count;
  }

  // unite:
  void unite(vector<int> &union_set, int &count, int i, int j) {
    int left = find(union_set, i);
    int right = find(union_set, j);

    if (left != right) {
      union_set[left] = right;
      count--;
    }
  }

  // find:
  int find(vector<int> &union_set, int index) {
    if (union_set[index] != index) {
      union_set[index] = find(union_set, union_set[index]);
    }
    return union_set[index];
  }
};
