#include <algorithm>
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
  return 0;
}
