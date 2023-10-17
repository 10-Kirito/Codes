#include <initializer_list>
#include <iostream>
#include <vector>

/*
 * 归并算法实现(注意这里的算法不是归并算法，仅仅是两个算法合并在一起):
 * 我们这里是将两个或者多个升序的数组进行合并而已.
 */
std::vector<int> merge(const std::vector<int> &lh, const std::vector<int> &rh) {
  int n = lh.size();
  int m = rh.size();

  std::vector<int> result(n + m);

  int i{0}, j{0}, k{0};

  while (i < n && j < m) {
    if (lh[i] < rh[j]) {
      result[k++] = lh[i++];
    }
    if (lh[i] >= rh[j]) {
      result[k++] = rh[j++];
    }
  }

  while (i < n) {
    result[k++] = lh[i++];
  }

  while (j < m) {
    result[k++] = rh[j++];
  }
  return result;
}

template <typename... Args>
std::vector<int> merge(const std::vector<int> &lh, const Args &...args) {
  std::vector<int> result = lh;
  (void)std::initializer_list<int>{(result = merge(result, args), 0)...};
  return result;
}

/*
 * 归并排序算法实现:
 */
void merge(std::vector<int> &nums, int low, int mid, int high) {
  std::vector<int> temp(nums.size());

  int i, j, k;

  /*临时存储相应的元素:*/
  for (k = low; k <= high; ++k) {
    temp[k] = nums[k];
  }

  for (i = low, j = mid + 1, k = low; i <= mid && j <= high; ++k) {
    if (temp[i] <= temp[j]) {
      nums[k] = temp[i++];
    } else {
      nums[k] = temp[j++];
    }
  }

  /*如果上面有一个序列已经排好，则在这里将另外的一个序列全部依次放在后面*/

  while (i <= mid) {
    nums[k++] = temp[i++];
  }

  while (j <= mid) {
    nums[k++] = temp[j++];
  }
}
void merge_sort(std::vector<int> &nums, int low, int high) {
  if (low < high) {
    /*从中间进行划分*/
    int mid = (low + high) / 2;

    /*对左边部分进行归并排序*/
    merge_sort(nums, low, mid);
    /*对右边部分进行归并排序*/
    merge_sort(nums, mid + 1, high);
    /*归并*/
    merge(nums, low, mid, high);
  }
}

int main(int argc, char *argv[]) {

  std::vector<int> vector_1{1, 45, 67, 89, 90};
  std::vector<int> vector_2{2, 100, 101, 102, 104};
  std::vector<int> vector_3{1, 23, 60, 70, 99};
  std::vector<int> vector_4{45, 56, 23, 34, 100, 90};

  std::vector<int> result = merge(vector_1, vector_2, vector_3, vector_2);

  for (const auto &elem : result) {
    std::cout << elem << " ";
  }
  std::cout << std::endl;
  merge_sort(vector_4, 0, vector_4.size() - 1);

  for (const auto &elem : vector_4) {
    std::cout << elem << " ";
  }
  std::cout << std::endl;
  return 0;
}
