#include <iostream>
#include <vector>

// 辅助输出函数:
void show_nums(const std::vector<int> &nums) {
  for (const auto &elem : nums) {
    std::cout << elem << " ";
  }

  std::cout << std::endl;
}

void heap_adjust(std::vector<int> &nums, int end);

// 堆排序算法:
void heap_sort(std::vector<int> &nums) {
  int temp;
  for (int i = nums.size() - 1; i > 0; --i) {
    heap_adjust(nums, i);
    temp = nums[i];
    nums[i] = nums[0];
    nums[0] = temp;
    show_nums(nums);
  }
}

// 建立大根堆算法:
// 将nums数组的[0,end]区间的元素建立大根堆.
void heap_adjust(std::vector<int> &nums, int end) { 
  for (int i = (end - 1) / 2; i >= 0; --i) { // 由于我们的数组是从[0,n]开始的，所以说最后一个非终端结点为(end -1) / 2.
    int next = i;
    int temp = nums[i];
    for (int k = (next * 2 + 1); k <= end;) {
      int max = k;                           // 这里的k < end是为了防止只有一个孩子结点，此时就会出现越界的情况:
      if (k < end && nums[k] < nums[k + 1])  // 如果左孩子更大一点:
        max = k + 1;
      if (nums[next] < nums[max]) {  // 比较父母结点与左右孩子结点中的最大值，如果父母本来就比两个孩子大的话
        nums[next] = nums[max];      // 就什么也不用做，如果父母没有两个孩子大，就将父母和两个孩子交换位置:
        nums[max] = temp;
        next = max;
      }
      k = (k * 2 + 1);
    }
  }
}

int main(int argc, char *argv[]) {
  std::vector<int> nums{49, 38, 65, 97, 76, 13, 27, 49};
  show_nums(nums);
  heap_sort(nums);
  std::cout << "堆排序:" << std::endl;
  show_nums(nums);
  std::cout << "---------------------" << std::endl;
  std::vector<int> nums_1{87, 45, 78, 32, 17, 65, 53, 9};
  show_nums(nums_1);
  heap_sort(nums_1);
  std::cout << "堆排序:" << std::endl;
  show_nums(nums_1);

  return 0;
}
