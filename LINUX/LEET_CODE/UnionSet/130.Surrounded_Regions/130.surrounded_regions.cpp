#include <numeric>
#include <iostream>
#include <vector>

using std::vector;

// 使用并查集这里第一次没有做出来，是查看的别人的题解才会的！！
// 并查集的概念本来是很简单的，但是我们如何将其与实际问题联系起来是十分困难的！！
// 比如说本题当中我们知道：如果O处于边界之上的话，或者O和边界上的O是处于连通状态
// 那么我们就可以将其进行合并，合并为一个集合，该集合我们一开始就声明出来（意思是初始状态下我们会多出一个结点用来表示这个是位于边界之上的！！）
// 到最后所有的O结点就会被分为一个特殊集合和若干个小集合.

class Solution {
public:
  void solve(vector<vector<char>> &board) {
    int row = board.size();
    int col = board[0].size();

    // 设置并查集:
    // 这里的并查集比较特殊，我们需要预先设置一个特殊集合.
    vector<int> union_sets(row * col + 1, -1);
    int special = row * col;

    // 初始化:
    std::iota(union_sets.begin(), union_sets.end(), 0);

    for (int i = 0; i < row; i++) {
      for (int j = 0; j < col; j++) {
        if (board[i][j] == 'O') {
          // 判断结点是否存在于边界之上，如果是就和special结点进行合并
          if (i == 0 || i == (row - 1) || j == 0 || j == (col - 1))
            unite(union_sets, i * col + j, special);

          // 判断左上两个方向是否也是相同的结点'O'
          if (i > 0 && board[i - 1][j] == 'O') {
            unite(union_sets, i * col + j, (i - 1) * col + j);
          }
          if (j > 0 && board[i][j - 1] == 'O') {
            unite(union_sets, i * col + j, i * col + j - 1);
          }
        }
      }
    }

    // 判断对应的结点是否和special处于相同的集合当中:
    for (int i = 0; i < row; i++) {
      for (int j = 0; j < col; j++) {
        if (board[i][j] == 'O' &&
            find(union_sets, i * col + j) != find(union_sets, special)) {
          board[i][j] = 'X';
        }
      }
    }
  }

  // 并查集unite实现:
  // 这里没有什么特殊的要求就是普通的合并和查找即可.
  void unite(vector<int> &union_set, int i, int j) {
    int left = find(union_set, i);
    int right = find(union_set, j);

    if (left != right) {
      union_set[left] = right;
    }
  }

  // 并查集find实现:
  int find(vector<int> &union_set, int i) {
    if (union_set[i] != i) {
      union_set[i] = find(union_set, union_set[i]);
    }
    return union_set[i];
  }
};

int main(int argc, char *argv[]) {
  vector<vector<char>> data = {{'X', 'X', 'X', 'X'},
                               {'X', 'O', 'O', 'X'},
                               {'X', 'X', 'O', 'X'},
                               {'X', 'O', 'X', 'X'}};

  Solution solution;

  solution.solve(data);

  return 0;
}
