#include "../include/binary_tree.h"
#include "../include/tools.h"
#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left),
 * right(right) {}
 * };
 */
class Solution {
public:
  // Solution1: in this case, we use recursive to handle with this questioin:
  static vector<int> inorderTraversal(TreeNode<int> *root) {
    vector<int> result;
    if (root) {
      vector<int> left = inorderTraversal(root->lchild);
      result.insert(result.end(), left.begin(), left.end());
      result.push_back(root->data);
      vector<int> right = inorderTraversal(root->rchild);
      result.insert(result.end(), right.begin(), right.end());
    }
    return result;
  }

  // Solution2: in this case, we use non-recursive to handle with this question:
  static vector<int> inorderTraversal(TreeNode<int> *root, bool) {
    vector<int> result;
    stack<TreeNode<int> *> _stack;

    if (root) {
      _stack.push(root);
    }

    while (!_stack.empty()) {
      TreeNode<int> *node = _stack.top();
      if (node) {
        _stack.pop();

        if (node->rchild) {
          _stack.push(node->rchild);
        }

        _stack.push(node);
        _stack.push(nullptr);

        if (node->lchild) {
          _stack.push(node->lchild);
        }
      } else {
        _stack.pop();
        node = _stack.top();
        result.push_back(node->data);
        _stack.pop();
      }
    }
    return result;
  }
};

int main(int argc, char *argv[]) {
  BinaryTree<int> tree;

  tree.insert(1, 2, 3);
  Dump(tree);

  vector<int> result = Solution::inorderTraversal(tree.getRoot(), true);
  for (auto &e : result) {
    std::cout << e << " ";
  }
  return 0;
}
