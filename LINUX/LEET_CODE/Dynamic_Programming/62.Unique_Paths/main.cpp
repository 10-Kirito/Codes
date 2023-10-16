#include <iostream>
#include <vector>

class Solution {
public:
  int uniquePaths(int m, int n) {
    std::vector<std::vector<int>> dp(m, std::vector<int>(n));

    // 初始化DP数组
    for (int i = 0; i < n; ++i) {
      dp[0][i] = 1;
    }
    for (int i = 0; i < m; ++i) {
      dp[i][0] = 1;
    }

    for (int i = 1; i < m; ++i) {
      for (int j = 1; j < n; ++j) {
        dp[i][j] = dp[i][j - 1] + dp[i - 1][j];
      }
    }

    for (const auto &elem : dp) {
      for (const auto &elem1 : elem) {
        std::cout << elem1 << " ";
      }
      std::cout << std::endl;
    }

    return dp[m-1][n-1];
  }
};

int main(int argc, char *argv[]) {
  Solution solution;

  std::cout << solution.uniquePaths(3, 7);

  return 0;
}
