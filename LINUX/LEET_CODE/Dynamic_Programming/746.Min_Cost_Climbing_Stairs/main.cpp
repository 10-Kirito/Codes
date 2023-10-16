#include <iostream>
#include <vector>
using std::vector;

class Solution {
public:
  int minCostClimbingStairs(vector<int> &cost) {
    vector<int> dp(cost.size() + 1);

    dp[0] = dp[1] = 0;

    for (int i = 2; i <= cost.size(); ++i) {
      if (dp[i - 2] + cost[i - 2] <= dp[i - 1] + cost[i - 1]) {
        dp[i] = dp[i - 2] + cost[i - 2];
      } else {
        dp[i] = dp[i - 1] + cost[i - 1];
      }
    }

    for (const auto & elem : dp) {
      std::cout << elem << " ";
    }
    std::cout << std::endl;

    return dp[cost.size()];
  }
};

int main(int argc, char *argv[]) {
  Solution solution;

  vector<int> cost{1,100,1,1,1,100,1,1,100,1};

  std::cout << solution.minCostClimbingStairs(cost);

  return 0;
}
