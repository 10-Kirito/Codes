/*
 * @lc app=leetcode id=200 lang=cpp
 *
 * [200] Number of Islands
 */

// @lc code=start
#include <iostream>
#include <vector>

using std::vector;
class Solution {
public:
  int numIslands(vector<vector<char>> &grid) {
    // m为行数，n为列数
    int m = grid.size();
    int n = grid[0].size();
    // 将访问数组全部设置为false
    std::vector<std::vector<bool>> visit(m, std::vector<bool>(n, false));

    int count = 0;

    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        // 如果发现当前岛屿块没有被访问过，说明是新的岛屿
        if (grid[i][j] == '1' && !visit[i][j]) {
          count++;
          dfs(grid, visit, i, j);
        }
      }
    }

    return count;
  }

  // “dfs遍历”
  void dfs(std::vector<std::vector<char>> &grid,
           std::vector<std::vector<bool>> &visit, int i, int j) {
    int m = grid.size();
    int n = grid[0].size();

    // 注意，如果我们访问过了之后就立即返回，否则的话就会陷入无限死循环
    if (i >= m || i < 0 || j >= n || j < 0 || grid[i][j] == '0' ||
        visit[i][j]) {
      return;
    }

    // 如果当前区域为小岛的一部分的话，将visit设置为true
    visit[i][j] = true;
    dfs(grid, visit, i, j + 1);
    dfs(grid, visit, i + 1, j);
    dfs(grid, visit, i, j - 1);
    dfs(grid, visit, i - 1, j);
    return;
  }
};

int main(int argc, char *argv[]) {

  Solution solution;
  vector<vector<char>> grid = {{'1', '1', '0', '0', '0'},
                               {'1', '1', '0', '0', '0'},
                               {'0', '0', '1', '0', '0'},
                               {'0', '0', '0', '1', '1'}};

  std::cout << solution.numIslands(grid);

  return 0;
}
// @lc code=end
