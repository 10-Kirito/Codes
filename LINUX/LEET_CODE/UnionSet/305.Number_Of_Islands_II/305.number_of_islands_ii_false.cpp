#include <iostream>
#include <numeric>
#include <vector>
using namespace std;

/**
 * 该代码的想法是简单的遍历一遍给定的坐标，然后去判断该坐标的
 * 周围是否存在岛屿，如果存在的话，就说明岛屿的数量没有增加;
 * 如果不存在的话，说明该岛屿为新的一块岛屿，岛屿的数量加一;
 * ！！！！！
 * 但是我们忘记了添加一个新的岛屿之后是有可能将两个不相邻的岛屿
 * 连接起来的，就是说我们仅仅考虑了岛屿数量的增加，却没有考虑岛屿
 * 数量的减少!!
 */


class Solution {
public:
  vector<int> numIslands2(int m, int n, vector<vector<int>> &positions) {
    vector<vector<int>> grid(m, vector<int>(n, 0));
    vector<int> result(positions.size());

    // 处理第一个特殊情况:
    vector<int> position = positions[0];
    grid[position[0]][position[1]] = 1;
    result[0] = 1;
    int count = 1;

    for (int i = 1; i < positions.size(); i++) {
      // 获取相应的坐标!
      position = positions[i];
      int row = position[0];
      int col = position[1];
      // 修改grid数组，标记该处为岛屿!
      grid[row][col] = 1;
      // 判断是否和之前的岛屿属于一个岛屿，如果不是的话，就将岛屿的数量加一!
      if (row > 0 && grid[row - 1][col] == 1 ||
          row < m - 1 && grid[row + 1][col] == 1 ||
          col > 0 && grid[row][col - 1] == 1 ||
          col < n - 1 && grid[row][col + 1] == 1) {
        result[i] = count;
      } else {
        count++;
        result[i] = count;
      }
    }

    for (auto elem : result) {
      cout << elem << " ";
    }
    return result;
  }
};

int main (int argc, char *argv[])
{
  vector<vector<int>> test1 = {{0, 0}, {0, 1}, {1, 2}, {2, 1}};

  Solution solution;
  solution.numIslands2(3, 3, test1);
  
  return 0;
}
