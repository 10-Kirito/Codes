#ifndef DISJOINT_SET
#define DISJOINT_SET

#include <algorithm>
#include <cstddef>
#include <numeric>
#include <vector>
class DisJointSet {
  // 统计并查集当中不同属性的元素的个数;
  // int count;
  // attention
  // 我们如果想要统计不同属性元素的个数的时候，我们必须重新遍历一遍
  // 如果其父亲就是自己的话，个数加一!!!
  //
  // 存储给定元素的父亲结点（代表元素）;
  std::vector<std::size_t> parent;

public:
  explicit DisJointSet(std::size_t size) : parent(size)/* , count(size) */ {
    std::iota(parent.begin(), parent.end(), 0);
  }

  // 寻找到给定元素的代表元素:
  // 注意：这里是进行过优化的，我们在寻找相应结点的过程中的修改原来并查集的值，
  // 下面的修改方案是每一棵树的根结点的都是相同的，那么我们可以不可以直接将除了
  // 根结点的所有的结点的父亲结点修改为根结点!!!
  inline std::size_t find(std::size_t  x) {
    if(parent[x] != x)
      parent[x] = find(parent[x]);
    return parent[x];
  }

  // 合并两个结点:
  inline void unite(std::size_t x, std::size_t y) {
    // 如果两个结点已经在同一个集合当中的话，就直接返回
    if (find(x) == find(y)) {
      return;
    }
    // 否则的话，就将x的根结点设置为y的根结点;
    parent[find(x)] = find(y);
    // count--;
  }

  // 判断两个结点是否已经连接:
  bool connected(std::size_t p, std::size_t q) {
    return find(p) == find(q);
  }
};

#endif
