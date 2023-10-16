#include <iostream>
#include <vector>
using std::vector;

class Solution {
public:
  int uniquePathsWithObstacles(vector<vector<int>> &obstacleGrid) {
    // 如果输入的数组的长度为0的话，就直接推出，并返回错误码-1
    if (obstacleGrid.size() == 0) {
      return -1;
    }

    int m = obstacleGrid.size();
    int n = obstacleGrid[0].size();

    vector<vector<int>> dp(m, vector<int>(n, 0));

    // 如果在开始的位置上放置一个障碍物的话，那没办法过不去的.
    if (obstacleGrid[0][0] == 1) {
      return 0;
    } else {
      dp[0][0] = 1;
    }
    // 1. 初始化第一列:
    for (int i = 1; i < m; ++i) {
      if (obstacleGrid[i][0] == 1) {
        dp[i][0] = 0;
      } else {
        dp[i][0] += dp[i - 1][0];
      }
    }

    for (int i = 1; i < n; ++i) {
      if (obstacleGrid[0][i] == 1) {
        dp[0][i] = 0;
      } else {
        dp[0][i] += dp[0][i - 1];
      }
    }

    for (int i = 1; i < m; ++i) {
      for (int j = 1; j < n; ++j) {
        if (obstacleGrid[i][j] != 1) {
          dp[i][j] = dp[i][j - 1] + dp[i - 1][j];
        }
      }
    }

    for (const auto &elem : dp) {
      for (const auto &e : elem) {
        std::cout << e << " ";
      }
      std::cout << std::endl;
    }

    return dp[m - 1][n - 1];
  }
};

int main(int argc, char *argv[]) {
  Solution solution;

  vector<vector<int>> data{
      {0, 0, 1, 0, 0}, {0, 0, 0, 0, 0}, {1, 0, 0, 0, 1}, {0, 0, 0, 1, 0}};
  std::cout << solution.uniquePathsWithObstacles(data);
  return 0;
}
