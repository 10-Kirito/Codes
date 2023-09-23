#include <algorithm>
#include <cstddef>
#include <iostream>
#include <vector>

// 1. 直接插入排序：
void Insert_Sort(std::vector<int> &nums) {
  int n = nums.size();
  int temp, j;
  // 从第二个元素开始，和前面的元素进行比较:
  // 如果是大于前面的一个元素的话,就说明已经是有序的；
  // 如果说小于前面的元素的话，就说明是无序的，此时我们需要将该元素移动到前面的元素的合适位置；
  for (int i = 1; i < n; ++i) {
    // 如果小于前面的元素的话：
    if (nums[i] < nums[i - 1]) {
      temp = nums[i];

      for (j = i - 1; j >= 0 && nums[j] > temp; --j) {
        nums[j + 1] = nums[j];
      }

      nums[j + 1] = temp;
    }
  }
}

// 2. 折半插入排序:
void Insert_Sort(std::vector<int> &nums, bool) {
  int n = nums.size();
  int temp;

  for (int i = 1; i < n; ++i) {
    if (nums[i] < nums[i - 1]) {
      int begin = 0;
      int end = i;
      // 这里的折半查找采取左闭右开的查找方式：[)
      int mid = (begin + end) / 2;
      int temp = nums[i];
      while (begin < end) {
        // 为了保持该排序算法的稳定性，所以当找到中间的那个值等于待插入的元素的时候
        // 需要继续往后面进行寻找，这样才能保证算法的稳定性;
        if (nums[mid] == temp) {
          begin = mid + 1;
        } else if (nums[mid] > temp) {
          end = mid;
        } else {
          begin = mid + 1;
        }
        mid = (begin + end) / 2;
      }
      // 将begin指向的元素依次往后进行移动:
      for (int j = i; j > begin; --j) {
        nums[j] = nums[j - 1];
      }
      nums[begin] = temp;
    }
  }
}

// 3. 希尔排序:
void Hill_Sort(std::vector<int> &nums) {
  std::size_t n = nums.size();
  int dk;

  // 分为不同的步长，从总长度的一半开始，依次每一次除以2:
  for (dk = n / 2; dk >= 1; dk = dk / 2) {
    // 遍历各个分好的小组:
    // (注意，这里的循环遍历每一次是进行加一的操作，每一轮进行直接插入排序是不位于一个
    // 组的，是在不同的小组之间进行切换的.)
    for (int i = dk; i < n; ++i) {
      // 如果当前分组的当前元素小于前面的元素的话，进行直接插入排序:
      if (nums[i] < nums[i - dk]) {
        int temp = nums[i];
        int j;
        for (j = i - dk; j >= 0 && nums[j] >= temp; j = j - dk) {
          nums[j + dk] = nums[j];
        }
        nums[j + dk] = temp;
      }
    }
  }
}

void show_nums(const std::vector<int> &nums) {
  for (const auto &elem : nums) {
    std::cout << elem << " ";
  }

  std::cout << std::endl;
}

int main(int argc, char *argv[]) {
  std::vector<int> nums{49, 38, 65, 97, 76, 13, 27, 49};
  show_nums(nums);
  Insert_Sort(nums);
  std::cout << "直接插入排序:" << std::endl;
  show_nums(nums);
  std::vector<int> nums_1{49, 38, 65, 97, 76, 13, 27, 49};
  Insert_Sort(nums_1, true);
  std::cout << "折半插入排序:" << std::endl;
  show_nums(nums_1);
  std::vector<int> nums_2{49, 38, 65, 97, 76, 13, 27, 49};
  Hill_Sort(nums_2);
  std::cout << "希尔插入排序:" << std::endl;
  show_nums(nums_2);
  return 0;
}
