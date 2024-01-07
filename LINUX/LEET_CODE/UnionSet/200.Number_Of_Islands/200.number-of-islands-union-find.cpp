/*
 * @lc app=leetcode id=200 lang=cpp
 *
 * [200] Number of Islands
 */

// @lc code=start
#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using std::vector;
class Solution {
public:
  int numIslands(vector<vector<char>> &grid) {
    // m: rows, n: columns
    int m = grid.size();
    int n = grid[0].size();

    // 妈的，第一次写的时候这里的* 写成了+!!!
    // 导致tm找了半天的错误，甚至都开始怀疑自己的脑子是不是存在问题!!!
    vector<int> union_find(m * n, -1);

    int count = 0;

    for (auto elem : grid) {
      for (auto a : elem) {
        if (a == '1') {
          count++;
        }
      }
    }

    std::cout << count << std::endl;

    // attention!!!!!
    // 我们一开始仅仅是建立并查集，而且不同题目下的条件不一样
    // 我们建立并查集的方式可能也不一样，比如说本题的当中存在着一些
    // 根本就是不是我们要合并的元素，就是“海水”。这个时候我们就不能将
    // 他们算进来，所以一开始初始化的时候，我们将其全部初始化为-1,
    // 之后遍历的时候进行判断，如果是“岛屿”的话，我们就将其的值修改为
    // 自己，然后根据具体的条件提供我们要合并的结点，最后我们仍旧需要
    // 统计并查集中不同属性的元素的个数!!!!!
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        if (grid[i][j] == '1') {
          union_find[i * n + j] = i * n + j;
          if (i > 0 && grid[i - 1][j] == '1') {
            unite(union_find, i * n + j, (i - 1) * n + j, count);
          }
          if (j > 0 && grid[i][j - 1] == '1') {
            unite(union_find, i * n + j, i * n + j - 1, count);
          }
        }
      }
    } // for

    /*     // 最后再次进行统计并查集当中不同属性元素的个数，即"岛屿"
        for (int i = 0; i < m; i++) {
          for (int j = 0; j < n; j++) {
            if (union_find[i * n + j] == i * n + j) {
              count++;
            }
          }
        }
     */
    return count;
  }

  // union-find : unite() implement:
  void unite(vector<int> &union_find, int x, int y, int &count) {
    int left = find(union_find, x);
    int right = find(union_find, y);

    if (left != right) {
      union_find[left] = right;
      count--;
    }
  }

  // union-find : find() implement:
  int find(vector<int> &union_find, int index) {
    if (union_find[index] != index) {
      union_find[index] = union_find[find(union_find, union_find[index])];
    }
    return union_find[index];
  } // find
};

int main(int argc, char *argv[]) {

  Solution solution;
  vector<vector<char>> grid = {{'1', '1', '0', '0', '0'},
                               {'1', '1', '0', '0', '0'},
                               {'0', '0', '1', '0', '0'},
                               {'0', '0', '0', '1', '1'}};

  vector<vector<char>> grid1 = {
      {'1', '1', '1'}, {'0', '1', '0'}, {'1', '1', '1'}};

  std::cout << solution.numIslands(grid) << std::endl;
  std::cout << solution.numIslands(grid1) << std::endl;

  return 0;
}
// @lc code=end
