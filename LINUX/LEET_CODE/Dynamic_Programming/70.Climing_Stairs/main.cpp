#include <iostream>
#include <vector>

class Solution {
public:
  int climbStairs(int n) {
    std::vector<int> dp(n + 1);
    dp[1] = 1;
    dp[0] = 1;

    for (int i = 2; i <= n; ++i) {
      dp[i] = dp[i - 1] + dp[i - 2];
    }

    for (const auto& elem : dp) {
      std::cout << elem << " ";
    }
    std::cout << std::endl;

    return dp[n];
  }
};

int main(int argc, char *argv[]) {
  Solution solution;

  std::cout << solution.climbStairs(10) << std::endl;

  return 0;
}
