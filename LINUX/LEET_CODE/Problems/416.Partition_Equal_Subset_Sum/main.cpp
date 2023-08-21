#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <utility>
#include <vector>
using namespace std;

// Given an integer array nums, return true if you can partition the array into
// two subsets such that the sum of the elements in both subsets is equal or
// false otherwise.

class Solution {
public:
  static bool canPartition(vector<int> &nums) {
    int sum = 0;
    for (auto &e : nums) {
      sum += e;
    }
    // if the sum of nums is odd number, then it means that the sitution
    // described in the title must not exist.
    if (sum % 2 != 0) {
      return false;
    }

    // the (sum / 2) is the sum of subset.
    sum = sum / 2;
    // now, the question is reduced to find a subset whose sum is sum.
    // we sort the numbers in order from smallest to largest:
    sort(nums.begin(), nums.end());

    // if sorted numbers' largest one is larger than sum, then it means that
    // the sitution described in the title must not exist.
    if (nums.back() > sum) {
      return false;
    }

    bool flag = true;
    int temp = nums.back();
    if (temp == sum) {
      return true;
    }
    vector<int>::iterator itera = nums.begin();
    vector<int>::iterator itera_temp = nums.begin();

    while (flag && (itera_temp != nums.end())) {
      if ((temp + *itera_temp) < sum) {
        temp += *itera_temp;
        itera_temp++;
      } else if ((temp + *itera_temp) == sum) {
        // if temp + *itera == sum, it means we get it!
        flag = false;
      } else {
        temp = nums.back();
        itera_temp = ++itera;
      }
    }
    return !flag;
  }

  static bool canPartition_1(vector<int> &nums) {
    int sum = 0;
    for (auto &e : nums) {
      sum += e;
    }
    // if the sum of nums is odd number, then it means that the sitution
    // described in the title must not exist.
    if (sum % 2 != 0) {
      return false;
    }

    // the (sum / 2) is the sum of subset.
    sum = sum / 2;
    // now, the question is reduced to find a subset whose sum is sum.
    // we sort the numbers in order from smallest to largest:
    sort(nums.begin(), nums.end());

    // if sorted numbers' largest one is larger than sum, then it means that
    // the sitution described in the title must not exist.
    if (nums.back() > sum) {
      return false;
    }

    unordered_map<int, int> nummap;
    for (int i = 0; i < nums.size(); ++i) {
      nummap.insert(make_pair(nums[i], i));
    }

    auto it = nummap.find(sum);
    if (it != nummap.end()) {
      return true;
    }

    bool flag = true;
    while (flag) {
      it = nummap.find(sum - nums.back());
      if (it != nummap.end()) {
        return true;
      } else {

      }
    }

    vector<int>::iterator itera = nums.begin();
    vector<int>::iterator itera_temp = nums.begin();

    return !flag;
  }
};



void print(int id, const std::vector<int> &container, bool flag) {
  std::cout << id << ". ";
  for (const int x : container)
    std::cout << x << ' ';
  std::cout << std::boolalpha;
  std::cout << flag << std::endl;
}
int main(int argc, char *argv[]) {
  vector<int> test1 = {3, 3, 3, 4, 5};
  print(1, test1, Solution::canPartition(test1));

  vector<int> test2 = {14, 9, 8, 4, 3, 2};
  print(2, test2, Solution::canPartition(test2));



  return 0;
}
