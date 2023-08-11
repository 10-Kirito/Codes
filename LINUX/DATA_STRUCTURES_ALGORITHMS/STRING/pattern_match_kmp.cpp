#include <cstddef>
#include <iostream>
#include <string>
using namespace std;

int *kmp_table(string pattern) {
  size_t size = pattern.length();
  int *next = new int[size];
  next[0] = 0;

  for (int i = 1; i < size; ++i) {
    int k = next[i - 1];
    // 下面的while循环是为了寻找子对称，就是在前面看看有没有已经对称的前缀和后缀，我们看看可以不可以进行继承之前的对称性：
    //     1.首先判断k是否为0，如果为0的话，说明前面就不存在子对称，如果多加了一个字符（也就是我们i指向的那个字符），要对称的话
    //       那也是最多是和pattern的第一个字符对称，那我们需要判断是否和pattern的第一个字符相等：
    //         如果相等的话，那么后缀和前缀匹配的最大长度为1；
    //         否则的话，后缀和前缀匹配的最大长度为0；
    //     2.接下来如果k不为0的话，说明前面是存在子对称的，我们需要判断前面的对称性我们是否可以继承！
    //       这里判断pattern[i] != pattern[k],
    //       如果不相等的话，说明前面的对称性不能被继承，我们需要递归查看这个失败匹配的子对称的
    //       子对称，就是嵌套，查看里面的子对称我们是否可以继承，如果出现pattern[i]
    //       == pattern[k]的情况的话，说明是可以继承的，退出循环
    //
    while (k != 0 && pattern[i] != pattern[k]) {
      k = next[k - 1];
    }

    // 如果前面的对称性是可以继承的话，或者说我们需要和第一个字符比较其是否相等（这里也可以变相的理解为继承第一个元素的对称性）
    if (pattern[i] == pattern[k]) {
      next[i] = k + 1;
    } else {
      // 如果不相等的话，说明是不可以继承或者也不等于pattern的第一个字符，这种情况就设置为0即可
      next[i] = 0;
    }
  }
  return next;
}

/**
 * 该版本的算法进行了改进，因为在实际的操作过程中，next数组的最后一位，我们是一定用不到的
 * 所以说我们可以将next数组的值整体往右边移动一位，这样的话我们哪一个元素匹配失败的，就可以
 * 直接查看自己的部分匹配值就可以了，因为存储的是前一位的部分匹配值!
 *
 * 这样的话子串指针变化公式j = next[j]即可。
 *
 */
int *kmp_table_v1(string pattern){


  return nullptr;
}

/**
 * KMP算法的实现：
 * 最主要的就是： 移动位数 = 已经匹配的字符数 - 对应的字符的部分匹配值
 * （部分匹配值也就是上面我们求得的next数组，在这里对应的字符指的是已经匹配的字符集的最后一个字符，如果该字符的
 *   部分匹配值不为0的话，说明已经匹配的字符串是存在子对称的前缀和后缀的，这个时候我们只需要过滤掉那些肯定不匹
 *   配的字符即可，所以是已经匹配的字符数 -
 * 匹配的字符集的最后一位字符的部分匹配值）
 * @param target, 主串；
 * @param pattern, 模式串；
 * @return, 如果匹配成功返回相应的位置（下标从1开始），反之返回-1；
 *
 */
int kmp(string target, string pattern) {
  // 初始化模式串的部分匹配值
  int *next = new int[pattern.length()];
  next = kmp_table(pattern);

  int i = 0, j = 0;

  // 注意： KMP算法最精妙的地方在于主串遍历的过程中不需要回退，我只需要一直比较即可，只要我们
  //        及时的修改遍历模式串的位置j即可，向右移动的位数 = 已经匹配的字符数 - 对应的部分匹配值
  while (i < target.length() && j < pattern.length()) {
    if (target[i] == pattern[j]) {
      ++i;
      ++j;
    }else if (j == 0) {
      // 如果比较的时候，第一位字符就不相等的话，母串比较下一位
      ++i;
    }else {
      // 如果不匹配的话，查看前面的已匹配字符最后一位字符的部分匹配值
      j = next[j - 1];
    }
  }
  if (j >= pattern.length()) {
    return (i - pattern.length() + 1);
  }
  return -1;
}

int main(int argc, char *argv[]) {
  string temp = "agctagcagctagctg";
  string pattern = "agctag";
  string test = "HcsacscsacasHello";
  string pattern_1 = "Hello";

  int result = kmp(temp, pattern);
  if (result != -1) {
    std::cout << "匹配成功! 位置为：" << result << std::endl;
  } else {
    std::cout << "匹配失败！" << std::endl;
  }

  return 0;
}
