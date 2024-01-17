#include <iostream>
#include <vector>

class Solution {
public:
  // 第一种方法，使用递归进行实现，该种方法的时间复杂度为2^n，即指数型增长
  // 会导致时间超时.
  int fib(int n) {
    if (n == 0 || n == 1)
      return n;
    return fib(n - 1) + fib(n - 2);
  }

  // 第二种方法，使用动态规划数组来做:
  int fib(int n, bool) {
    if (n == 1 || n == 0) {
      return n;
    }
    std::vector<int> dp(n + 1);
    dp[0] = 0;
    dp[1] = 1;

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
