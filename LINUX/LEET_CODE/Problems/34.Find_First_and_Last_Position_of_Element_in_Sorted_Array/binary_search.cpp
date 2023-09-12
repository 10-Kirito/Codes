#include <iostream>
#include <vector>

// []
int binary_search(std::vector<int> &nums, int target) {
  int begin = 0;
  int end = nums.size() - 1;

  while (begin <= end) {
    int mid = (begin + end) / 2;
    if (nums[mid] == target) {
      return mid;
    } else if (nums[mid] > target) {
      end = mid - 1;
    } else {
      begin = mid + 1;
    }
  }
  return -1;
}

// [)
int binary_search(std::vector<int> &nums, int target, bool) {
  int begin = 0;
  int end = nums.size();

  while (begin < end) {
    int mid = (begin + end) / 2;
    if (nums[mid] == target) {
      return mid;
    } else if (nums[mid] > target) {
      end = mid;
    } else {
      begin = mid + 1;
    }
  }
  return -1;
}

int main(int argc, char *argv[]) {
  std::vector<int> nums_0{1, 2, 3, 4, 5, 8, 9};
  std::vector<int> nums_1{1};

  std::cout << binary_search(nums_0, 5, true) << std::endl;
  std::cout << binary_search(nums_1, 1, true) << std::endl;
  return 0;
}
