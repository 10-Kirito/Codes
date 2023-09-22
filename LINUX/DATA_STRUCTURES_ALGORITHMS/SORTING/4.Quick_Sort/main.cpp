#include <algorithm>
#include <cstddef>
#include <iostream>
#include <vector>

// 辅助输出函数:
void show_nums(const std::vector<int> &nums) {
  for (const auto &elem : nums) {
    std::cout << elem << " ";
  }

  std::cout << std::endl;
}

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

// 4.冒泡排序:
void Bubble_Sort(std::vector<int> &nums) {
  int temp;
  for (int i = 0; i < nums.size(); ++i) {
    bool flag = true;
    for (int j = 0; j < nums.size() - 1; ++j) {
      if (nums[j] > nums[j + 1]) {
        flag = false;
        temp = nums[j + 1];
        nums[j + 1] = nums[j];
        nums[j] = temp;
      }
    }
    show_nums(nums);
    // 如果该轮冒泡之后，flag变量仍然为true，说明此时的序列已经有序，我们不需要再次进行排序:
    if (flag) {
      return;
    }
  }
}

// 5. 快速排序算法:
int Quick(std::vector<int> &nums, int low, int high);
void Quick_Sort(std::vector<int> &nums, int low, int high);

void Quick_Sort_Algori(std::vector<int> &nums) {
  if (nums.empty()) {
    return;
  }
  Quick_Sort(nums, 0, nums.size() - 1);
}

void Quick_Sort(std::vector<int> &nums, int low, int high) {
  // 注意这里不能写low == high,第一次写该算法的时候就是这里写了== 导致在这里找bug找了半天
  // 如果这里是等于的话，当左边或者右边只有连个元素的时候，下一轮一定是相等的，在调用了Quick_Sort()算法
  // 时候，会导致high比low小，但是不相等，但是由于我们在这里写的是==导致不会停止.
  if (low >= high) {
    return;
  }
  int pivot = Quick(nums, low, high);
  Quick_Sort(nums, low, pivot - 1);
  show_nums(nums);
  Quick_Sort(nums, pivot + 1, high);
  show_nums(nums);
}

// 快速排序算法辅助函数，我们此算法的目的是为了获得当前low指针指向的元素应该在的位置，然后再次分为两组.
int Quick(std::vector<int> &nums, int low, int high) {
  int temp = nums[low];
  while (low < high) {
    for (; low < high && nums[high] >= temp; --high);
    nums[low] = nums[high];
    for (;low < high && nums[low] <= temp; ++low);
    nums[high] = nums[low];
  }

  nums[low] = temp;
  return low;
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
  std::cout << "-----------------------" << std::endl;
  std::vector<int> nums_3{49, 38, 65, 97, 76, 13, 27, 49};
  Bubble_Sort(nums_3);
  std::cout << "冒泡插入排序结果:" << std::endl;
  show_nums(nums_3);

  std::cout << "-----------------------" << std::endl;
  std::vector<int> nums_4{49, 38, 65, 97, 76, 13, 27, 49};
  Quick_Sort_Algori(nums_4);
  std::cout << "快速排序插入排序结果:" << std::endl;
  show_nums(nums_4);

  return 0;
}
