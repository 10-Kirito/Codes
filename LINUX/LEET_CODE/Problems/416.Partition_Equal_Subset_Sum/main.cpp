#include <algorithm>
#include <iostream>
#include <set>
#include <unordered_map>
#include <utility>
#include <vector>
using namespace std;

// Given an integer array nums, return true if you can partition the array into
// two subsets such that the sum of the elements in both subsets is equal or
// false otherwise.

class Solution {
public:

  // WRONG!!!
  // don't consider all case!!!
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

  // Brute Force:
  // The crux of the problem lies in how we find a subset from a given set of
  // numbers so that its sum is equal to half of the sum of all numbers. Then we
  // can consider listing all the subsets. For each number in the subset, he can
  // choose to exist or not. If there are n numbers in total, then there will be
  // 2^n solutions. We can first initialize an array with an initial value of 0,
  // because there may be all numbers that do not exist in the subset.
  // WRONG!!!!
  // vector<int> test3 = {
  //     100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100,
  //     100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100,
  //     100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100,
  //     100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100,
  //     100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100,
  //     100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100,
  //     100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100,
  //     100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100,
  //     100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100,
  //     100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100,
  //     100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100,
  //     100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100,
  //     100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100,
  //     100, 100, 100, 99,  97};
  // in this case, the test3 will cause the memory limit exceeded!!!

  static bool canPartition(vector<int> &nums, bool) {
    vector<int> subsets{0};

    int sum = 0;

    for (const auto &e : nums) {
      sum += e;
    }

    if (sum % 2) {
      return false;
    }

    sum = sum / 2;
    for (auto e = nums.begin(); e != nums.end(); ++e) {
      vector<int> newItem;
      for (auto it = subsets.begin(); it != subsets.end(); ++it) {
        if ((*e + *it) <= sum) {
          newItem.push_back(*e + *it);
        }
      }
      subsets.insert(subsets.begin(), newItem.begin(), newItem.end());
      sort(subsets.begin(), subsets.end());
    }

    for (auto &e : subsets) {
      cout << e << " ";
    }
    cout << endl;

    if (find(subsets.begin(), subsets.end(), sum) == subsets.end()) {
      return false;
    };
    return true;
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
  print(2, test2, Solution::canPartition(test2, true));

  vector<int> test3 = {
      100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100,
      100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100,
      100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100,
      100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100,
      100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100,
      100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100,
      100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100,
      100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100,
      100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100,
      100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100,
      100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100,
      100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100,
      100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100,
      100, 100, 100, 99,  97};
  print(3, test3, Solution::canPartition(test3, true));
  return 0;
}
