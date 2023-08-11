#include <iostream>
#include <string>
/**
 * 简单的字符串模式匹配算法：
 * 暴力求解算法，就是依次遍历我们的目标字符串，一位一位的去比较！
 */

using namespace std;

/**
 * 模式匹配算法（暴力求解算法）：
 * @param target, 主串；
 * @param pattern, 子串；
 * @return, 如果匹配成功返回子串在主串中的位置（从1开始）；
 *          如果匹配失败的话，返回数字0；
 */
int pattern_match(string target, string pattern) {
  int i = 0, j = 0;
  // int temp = 1;
  while (i < target.length() && j < pattern.length()) {
    if (target[i] == pattern[j]) {
      ++i;
      ++j;
    } else {
      i = i - j + 1;
      // i = temp;
      // ++temp;
      j = 0;
    }
  }
  if (j == pattern.length()) {
    // return temp;
    // 此时i应该在主串相同的位置之后一个位置，所以要回退子串大小的位置
    // 并且切换为从1开始的位置坐标。
    return (i - pattern.length() + 1);
  }
  return 0;
}
int main(int argc, char *argv[]) {
  string target = "world!Hello,world!";
  string pattern = "world!";

  cout << pattern_match(target, pattern) << endl;
  return 0;
}
