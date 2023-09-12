#include <iostream>
#include <vector>
using std::vector;


int lower_bound(vector<int> &nums, int low, int high, int target) {
  while (low < high) {
    int mid = (low + high) / 2;
    if (nums[mid] < target) {
      low = mid + 1;
    }else {
      high = mid - 1;
    }
  }
  return low;
}


int main(int argc, char *argv[]) {
  vector<int> nums{5, 7, 7, 8, 8, 10};

  std::cout << lower_bound(nums, 0, nums.size() - 1, 8);
  std::cout << lower_bound(nums, 0, nums.size() - 1, 9);

  return 0;
}
