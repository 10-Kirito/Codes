#include <iostream>
#include <vector>

class Solution {
public:
  // 第二种方法，使用动态规划数组来做:
  int fib(int n, bool) {
    if (n == 1 || n == 0) {
      return n;
    }
    // 注意，这里我们需要额外的一个空间，因为我们需要去访问dp[n], 所以
    // 我们需要额外申请一个空间!
    std::vector<int> dp(n + 1);
    dp[0] = 0; dp[1] = 1;

    for (int i = 2; i <= n; ++i) {
      dp[i] = dp[i - 1] + dp[i - 2];
    }
    return dp[n];
  }
};

int main(int argc, char *argv[]) {
  Solution solution;

  std::cout << solution.fib(10, true) << std::endl;
  return 0;
}
