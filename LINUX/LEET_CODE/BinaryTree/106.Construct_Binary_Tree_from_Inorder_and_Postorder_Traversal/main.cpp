#include "../include/binary_tree.h"
#include "../include/tools.h"
#include <algorithm>
#include <ios>
#include <unordered_map>
#include <vector>

class Solution {
public:
  // Solution 1:
  // Runtime: 27ms;
  // Memory: 73.79MB;
  // The method is very slow and consumes a lot of memory!!
  static TreeNode<int> *buildTree(vector<int> &inorder,
                                  vector<int> &postorder) {
    // Step1:
    if (postorder.size() == 0 || inorder.size() == 0) {
      return nullptr;
    }
    // Step2:
    // Get the last element of post-order traversal and construct the current
    // node:
    int rootValue = postorder[postorder.size() - 1];
    TreeNode<int> *root = new TreeNode<int>(rootValue);

    // leaf node:
    if (postorder.size() == 1) {
      return root;
    }

    // Step3:
    // Find the cut point:
    int delimiterIndex;
    for (delimiterIndex = 0; delimiterIndex < inorder.size();
         delimiterIndex++) {
      if (inorder[delimiterIndex] == rootValue) {
        break;
      }
    }

    // Step4:
    // Split the inorder array into two other inorder array:
    // [0, delemiterIndex)
    vector<int> leftInorder(inorder.begin(), inorder.begin() + delimiterIndex);
    vector<int> rightInorder(inorder.begin() + delimiterIndex + 1,
                             inorder.end());

    // Step5:
    // Split the postorder array into two other postorder array:
    postorder.resize(postorder.size() - 1);
    // [0, 0 + leftInorder.size());
    vector<int> leftPostorder(postorder.begin(),
                              postorder.begin() + leftInorder.size());
    vector<int> rightPostorder(postorder.begin() + leftInorder.size(),
                               postorder.end());

    // Step6:
    root->lchild = buildTree(leftInorder, leftPostorder);
    root->rchild = buildTree(rightInorder, rightPostorder);

    return root;
  }

  // Solution2:
  // if don't use hash-table:
  // Runtime: 22ms;
  // Memory: 26.1MB;
  //
  // after use hash-table:
  // Runtime: 4ms;
  // Memory: 26.42MB;
  static TreeNode<int> *buildTree(vector<int> &inorder, vector<int> &postorder,
                                  bool) {
    if (inorder.size() == 0 || postorder.size() == 0) {
      return nullptr;
    }

    unordered_map<int, int> number_map;

    for (int i = 0; i < inorder.size(); ++i) {
      number_map[inorder[i]] = i;
    }

    return buildHelper(inorder, postorder, 0, inorder.size(), 0,
                       postorder.size(), number_map);
  }

private:
  static TreeNode<int> *buildHelper(vector<int> &inorder,
                                    vector<int> &postorder, int instart,
                                    int inend, int poststart, int postend, unordered_map<int, int>& number_map) {
    // nullptr node:
    if (poststart == postend) {
      return nullptr;
    }

    int rootValue = postorder[postend - 1];
    TreeNode<int> *root = new TreeNode<int>(rootValue);
    // leaf node:
    if (instart == (inend - 1) && poststart == (postend - 1)) {
      return root;
    }

    // find the cut point in the inorder:
    int delemiterIndex = number_map[rootValue];
    // for (delemiterIndex = instart; delemiterIndex < inend; delemiterIndex++) {
    //   if (inorder[delemiterIndex] == rootValue) {
    //     break;
    //   }
    // }


    // construct the left children:
    // inorder:
    int left_inorder_begin = instart;
    int left_inorder_end = delemiterIndex;

    int right_inorder_begin = delemiterIndex + 1;
    int right_inorder_end = inend;

    // postorder:
    int left_post_begin = poststart;
    int left_post_end = poststart + delemiterIndex - instart;

    int right_post_begin = poststart + delemiterIndex - instart;
    int right_post_end = postend - 1;

    root->lchild =
        buildHelper(inorder, postorder, left_inorder_begin, left_inorder_end,
                    left_post_begin, left_post_end, number_map);

    // construct the right children:
    root->rchild =
        buildHelper(inorder, postorder, right_inorder_begin, right_inorder_end,
                    right_post_begin, right_post_end, number_map);

    return root;
  }
};

int main(int argc, char *argv[]) {
  vector<int> inorder{9, 3, 15, 20, 7};
  vector<int> postorder{9, 15, 7, 20, 3};
  BinaryTree<int> tree = Solution::buildTree(inorder, postorder, true);
  Dump(tree);

  vector<int> inorder1{9,3,15,20,7};
  vector<int> postorder1{9,15,7,20,3};

  BinaryTree<int> tree1 = Solution::buildTree(inorder1, postorder1, true);

  Dump(tree1);

  return 0;
}
