#include <initializer_list>
#include <iostream>
#include <vector>

/*
 * 归并算法实现:
 * 我们这里是将两个或者多个升序的数组进行合并而已.
 */
std::vector<int> merge(const std::vector<int> &lh, const std::vector<int> &rh) {
  int n = lh.size();
  int m = rh.size();

  std::vector<int> result(n + m);

  int i{0}, j{0}, k{0};

  while (i < n || j < m) {
    if (lh[i] < rh[j] && i < n && j < m || i < n && j >= m) {
      result[k] = lh[i];
      ++i;
    }
    if (lh[i] >= rh[j] && i < n && j < m || i >= n && j < m) {
      result[k] = rh[j];
      ++j;
    }
    ++k;
  }

  return result;
}

template <typename... Args>
std::vector<int> merge(const std::vector<int> &lh, const Args &...args) {
  std::vector<int> result = lh;
  (void)std::initializer_list<int>{(result = merge(result, args), 0)...};
  return result;
}

int main(int argc, char *argv[]) {

  std::vector<int> vector_1{1, 45, 67, 89, 90};
  std::vector<int> vector_2{2, 100, 101, 102, 104};
  std::vector<int> vector_3{1, 23, 60, 70, 99};

  std::vector<int> result = merge(vector_1, vector_2);

  for (const auto &elem : result) {
    std::cout << elem << " ";
  }
  std::cout << std::endl;
  return 0;
}
