#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

typedef struct UnionSet {
  vector<int> parent;
  int count;
} UnionSet;

// 该解法是利用并查集来解决相应的问题:
class Solution {

public:
  bool validTree(int n, vector<vector<int>> &edges) {
    // 初始化并查集:
    UnionSet union_set;
    union_set.parent.resize(n);
    union_set.count = n;
    std::iota(union_set.parent.begin(), union_set.parent.end(), 0);

    // 用来判断是否存在环:
    bool valid = true;

    // 依次遍历所有的边，然后利用并查集进行合并!
    for (auto edge : edges) {
      int from = edge[0];
      int to = edge[1];

      // 如果发现两个顶点已经存在于一个集合当中的话，说明存在环!
      if (find(union_set, from) == find(union_set, to)) {
        valid = false;
      }

      // 合并两个结点:
      unite(union_set, from, to);
    }

    // 如果valid为true且最终并查集中集合只有一个，说明符合题意!
    return valid && (union_set.count == 1);
  }

  // 并查集unite实现:
  void unite(UnionSet &union_set, int i, int j) {
    int left = find(union_set, i);
    int right = find(union_set, j);

    if (left != right) {
      union_set.parent[left] = right;
      union_set.count--;
    }
  }

  // 并查集find实现:
  int find(UnionSet &union_set, int next) {
    if (union_set.parent[next] != next) {
      union_set.parent[next] = find(union_set, union_set.parent[next]);
    }
    return union_set.parent[next];
  }
};

int main(int argc, char *argv[]) {
  vector<vector<int>> edges = {{0, 1}, {1, 2}, {2, 3}, {1, 3}, {1, 4}};
  vector<vector<int>> edges_1 = {{0, 1}, {0, 2}, {0, 3}, {1, 4}};

  Solution solution;

  if (solution.validTree(5, edges_1)) {
    cout << "给定图当中不存在环!" << endl;
  } else {
    cout << "给定图当中存在环!" << endl;
  };

  return 0;
}
