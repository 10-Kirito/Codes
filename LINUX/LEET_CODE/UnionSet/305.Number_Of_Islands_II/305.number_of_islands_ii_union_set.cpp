#include <iostream>
#include <numeric>
#include <vector>
using namespace std;

class Solution {
public:
  vector<int> numIslands2(int m, int n, vector<vector<int>> &positions) {
    // 初始化结果数组以及grid数组：
    vector<vector<int>> grid(m, vector<int>(n, 0));
    vector<int> result(positions.size());
    result[0] = 1;
    vector<int> position = positions[0];
    grid[position[0]][position[1]] = 1;
    // 初始化并查集数组:
    vector<int> union_set(m * n);
    std::iota(union_set.begin(), union_set.end(), 0);
    // 初始化岛屿块的数量，之后合并的时候该岛屿数量减去一:
    int count = 1;

    for (int i = 1; i < positions.size(); i++) {
      // 获取相应的坐标!
      position = positions[i];
      int row = position[0];
      int col = position[1];
      // 检查该位置是否已经存在岛屿，如果存在的话就不需要继续执行：
      if (grid[row][col] == 1) {
        result[i] = count;
        continue;
      }
      // 一开始是一块岛屿，这时候加入了一块岛屿，所以数量加一
      count++;

      // 修改grid数组，标记该处为岛屿!
      grid[row][col] = 1;
      // 判断周围是四个方向否存在岛屿, 如果存在岛屿的话就将岛屿的数量减去一;
      // 否则的话，就是新的岛屿，岛屿的数量加上一；
      // 左边:
      if (col > 0 && grid[row][col - 1] == 1) {
        unite(union_set, count, row * n + col, row * n + col - 1);
      }
      // 右边:
      if (col < n - 1 && grid[row][col + 1] == 1) {
        unite(union_set, count, row * n + col, row * n + col + 1);
      }
      // 上边:
      if (row > 0 && grid[row - 1][col] == 1) {
        unite(union_set, count, row * n + col, (row - 1) * n + col);
      }
      // 下边:
      if (row < m - 1 && grid[row + 1][col] == 1) {
        unite(union_set, count, row * n + col, (row + 1) * n + col);
      }

      result[i] = count;
    }

    for (auto elem : result) {
      cout << elem << " ";
    }

    cout << endl;
    return result;
  }

  // unite():
  void unite(vector<int> &union_set, int &count, int i, int j) {
    int left = find(union_set, i);
    int right = find(union_set, j);

    if (left != right) {
      union_set[left] = right;
      count--;
    }
  }

  // find():
  int find(vector<int> &union_set, int index) {
    if (union_set[index] != index) {
      union_set[index] = find(union_set, union_set[index]);
    }
    return union_set[index];
  }
};

int main(int argc, char *argv[]) {
  vector<vector<int>> test1 = {{0, 0}, {0, 1}, {1, 2}, {2, 1}};
  vector<vector<int>> test2 = {{0, 0}, {1, 1}, {0, 1}};
  vector<vector<int>> test3 = {{0, 0}, {0, 1}, {1, 2}, {1, 2}};

  Solution solution;
  solution.numIslands2(3, 3, test1);
  solution.numIslands2(3, 3, test2);
  solution.numIslands2(3, 3, test3);

  return 0;
}
