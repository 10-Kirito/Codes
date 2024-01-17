#include <cstring>
#include <iostream>
#include <vector>

class Solution {
public:
  // 带备忘录的递归解法:
  int fib(int n) {
    // 备忘录全部初始化为0
    int mem[n+1];
    memset(mem, 0, sizeof(mem));
    return recursion(mem, n);
  }

  // 递归:
  int recursion(int mem[], int n) {
    if (n == 0 || n == 1)
      return n;
    if (mem[n] != 0)
      return mem[n];
    mem[n] = recursion(mem, n - 1) + recursion(mem, n - 2);
    return mem[n];
  }
 };

int main(int argc, char *argv[]) {
  Solution solution;

  std::cout << solution.fib(10) << std::endl;
  return 0;
}
