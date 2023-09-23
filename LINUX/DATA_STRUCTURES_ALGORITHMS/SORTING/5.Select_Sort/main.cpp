#include <iostream>
#include <vector>

// 辅助输出函数:
void show_nums(const std::vector<int> &nums) {
  for (const auto &elem : nums) {
    std::cout << elem << " ";
  }

  std::cout << std::endl;
}

void select_sort(std::vector<int> &nums) {
  // 首先需要进行n-1趟排序:
  for (int i = 0; i < (nums.size() - 1); ++i) {
    // 每一次排序从区间[j,n-1]中选择出最小的元素，将其和元素j进行交换:
    // 我们是记录位置:
    int min = i;
    for (int j = i + 1; j < nums.size(); ++j) {
      if (nums[j] < nums[min]) {
        min = j;
      }
    }
    // 找出最小的元素之后，将其余位置i上的元素进行交换:
    std::swap(nums[i], nums[min]);
    /* int temp = nums[i];
    nums[i] = nums[min];
    nums[min] = temp; */
    show_nums(nums);
  }
}

int main(int argc, char *argv[]) {
  std::vector<int> nums{49, 38, 65, 97, 76, 13, 27, 49};
  show_nums(nums);
  select_sort(nums);
  std::cout << "简单选择排序:" << std::endl;
  show_nums(nums);
  return 0;
}
