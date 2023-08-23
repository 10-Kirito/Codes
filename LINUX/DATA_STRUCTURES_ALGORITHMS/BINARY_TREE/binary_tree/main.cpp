#include "binary_tree.h"
#include "tools.h"
#include <iostream>
#include <random>
#include <stack>

template <typename T> void visit(const T &data) { std::cout << data << " "; }

void test1() {
  BinaryTree<int> tree_1;
  tree_1.insert(8, 5, 2, 6, 10, 9, 11);
  Dump(tree_1);
  std::cout << "The binary_tree's height is " << tree_1.height() << std::endl;

  BinaryTree<int> tree_2;
  tree_2.insert(33, 27, 15, 21, 36, 35, 43, 42, 49);
  Dump(tree_2);
  std::cout << "The binary_tree's height is " << tree_2.height() << std::endl;

  BinaryTree<int> tree;
  for (int i = 0; i < 10; ++i) {
    tree.insert(rand() % 50);
  }
  Dump(tree);
  std::cout << "The binary_tree's height is " << tree.height() << std::endl;
  BinaryTree<int> binary_tree;

  binary_tree.insert(50, 49, 53, 54, 23, 24, 60, 10, 12);

  Dump(binary_tree);

  std::cout << "Preorder Traversal:" << std::endl;
  binary_tree.preorderTarversal(&visit);
  std::cout << std::endl;
  binary_tree.preorderTarversal(&visit, true);
  std::cout << std::endl;
  binary_tree.preorderTarversal(&visit, true, true);

  std::cout << std::endl << "Inorder Traversal:" << std::endl;
  binary_tree.inorderTarversal(&visit);
  std::cout << std::endl;
  binary_tree.inorderTarversal(&visit, true);
  std::cout << std::endl;
  binary_tree.inorderTarversal(&visit, true, true);

  std::cout << std::endl << "PostOrder Traversal:" << std::endl;
  binary_tree.postTarversal(&visit);
  std::cout << std::endl;
  binary_tree.postorderTarversal(&visit, true);
  std::cout << std::endl;
  binary_tree.postorderTarversal(&visit, true, true);

  std::cout << std::endl << "LevelOrder Traversal:" << std::endl;
  binary_tree.levelorderTarversal(&visit);
}

int main(int argc, char *argv[]) {
  BinaryTree<int> tree;
  tree.insert(23, 45, 12, 56, 20, 60, 6);
  Dump(tree);
  tree.invertTree();
  Dump(tree);

  // construct the binary tree use a inorder and postorder:
  BinaryTree<int> tree_test_1({9, 3, 15, 20, 7}, {9, 15, 7, 20, 3});
  Dump(tree_test_1);
  // construct the binary tree use a inorder and preorder:
  BinaryTree<int> tree_test_2({9, 3, 15, 20, 7}, {3, 9, 20, 15, 7}, true);
  Dump(tree_test_2);

  return 0;
}
