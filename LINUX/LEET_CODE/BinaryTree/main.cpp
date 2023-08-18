#include "./include//binary_tree.h"
#include "./include/tools.h"
#include <iostream>

template <typename T> void visit(const T &data) { std::cout << data << " "; }

int main(int argc, char *argv[]) {

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

  return 0;
}
