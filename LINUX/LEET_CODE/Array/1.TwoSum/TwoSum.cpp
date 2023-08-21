// Resource:
// https://leetcode.com/problems/two-sum/

#include <ios>
#include <map>
#include <unordered_map>
#include <vector>
using namespace std;
class Solution {
public:
  // 1. Brute Force
  // Runtime: 291ms;
  // Memory: 10.2MB;
  vector<int> twoSum(vector<int> &nums, int target) {
    vector<int> result;
    for (int i = 0; i < nums.size() - 1; ++i) {
      for (int j = i + 1; j < nums.size(); ++j) {
        if ((nums[i] + nums[j]) == target) {
          return (result = {i, j});
        }
      }
    }
    return result;
  }

  // Use One-pass Hash Table:
  // Runtime: 12ms;
  // Memory: 12.1mb;
  vector<int> twoSum_v1(vector<int> &nums, int target) {
    unordered_map<int, int> numMap;
    int n = nums.size();

    // Build the hash table
    for (int i = 0; i < n; i++) {
      numMap[nums[i]] = i;
    }

    // Find the complement
    for (int i = 0; i < n; i++) {
      int complement = target - nums[i];
      // if the complement belongs to hash table and it's index != i
      if (numMap.count(complement) && numMap[complement] != i) {
        return {i, numMap[complement]};
      }
    }
    return {};
  }

  // Use map to compare with unordered_map:
  // Runtime: 18ms;
  // Memory: 12.5ms
  vector<int> twoSum_v2(vector<int> &nums, int target) {
    map<int, int> numMap;
    int n = nums.size();

    // Build the hash table
    for (int i = 0; i < n; i++) {
      numMap[nums[i]] = i;
    }

    // Find the complement
    for (int i = 0; i < n; i++) {
      int complement = target - nums[i];
      // if the complement belongs to hash table and it's index != i
      if (numMap.count(complement) && numMap[complement] != i) {
        return {i, numMap[complement]};
      }
    }
    return {};
  }

  // One-pass Hash Table:
  // Runtime: 7ms;
  // Memory: 10.9mb;
  vector<int> twoSum_v3(vector<int> &nums, int target) {
    unordered_map<int, int> num_map;
    int n = nums.size();

    // The key of this method is to search while inserting!
    for (int i = 0; i < n; i++) {
      int complement = target - nums[i];
      if (num_map.count(complement)) {
        return {num_map[complement], i};
      }
      num_map[nums[i]] = i;
    }
    return {};
  }
};
