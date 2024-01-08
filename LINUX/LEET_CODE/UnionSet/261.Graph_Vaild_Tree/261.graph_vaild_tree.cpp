#include <iostream>
#include <vector>

using namespace std;

class Solution {
  bool valid = true;

public:
  bool validTree(int n, vector<vector<int>> &edges) {
    vector<vector<int>> graph(n);

    // 遍历给定边建立图:
    for (vector<int> edge : edges) {
      int from = edge[0];
      int to = edge[1];
      graph[from].push_back(to);
      graph[to].push_back(from);
    }

    return checkVaild(graph);
  }

  bool checkVaild(vector<vector<int>> graph) {
    vector<bool> on_path(graph.size(), false);
    vector<bool> visited(graph.size(), false);
    int count = 0;
    for (int i = 0; i < graph.size(); i++) {
      if (!visited[i]) {
        DFS(graph, on_path, visited, 0, -1);
        count++;
      }
    }

    // 这里设置一个计数器来统计图的连图分量有多少个，如果不是一个的话
    // 那么也不符合这个题目的要求，因为该题目的要求是一棵树!!!
    return valid && (count == 1);
  }

  void DFS(vector<vector<int>> &graph, vector<bool> &on_path,
           vector<bool> &visited, int next, int parent) {
    // 如果访问的当前结点已经位于路径之上，说明存在环:
    if (on_path[next]) {
      valid = false;
    }
    // 如果该结点已经访问过:
    if (visited[next] || !valid) {
      return;
    }
    // 设置该结点已经访问:
    visited[next] = true;
    // 标记该结点位于访问路径之上
    on_path[next] = true;
    // 深度递归遍历给定结点的邻接结点:
    for (auto neighbor : graph[next]) {
      // 因为无向图当中如果两个结点之间存在路径，那么如果不判断邻居结点是否是
      // 刚才的父母结点的话，就会导致”有环“，所以这里需要进行判断!!!
      // 这里也是有向图和无向图判断是否有环的区别所在!!!
      if (neighbor != parent) {
        DFS(graph, on_path, visited, neighbor, next);
      }
    }
    // 取消标记该结点位于访问路径之上:
    on_path[next] = false;
  }
};

int main(int argc, char *argv[]) {
  vector<vector<int>> edges = {{0, 1}, {1, 2}, {2, 3}, {1, 3}, {1, 4}};
  vector<vector<int>> edges_1 = {{0, 1}, {0, 2}, {0, 3}, {1, 4}};

  Solution solution;

  if (solution.validTree(5, edges)) {
    cout << "给定图当中不存在环!" << endl;
  } else {
    cout << "给定图当中存在环!" << endl;
  };

  return 0;
}
