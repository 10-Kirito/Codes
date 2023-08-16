#include "tools.h"
#include "binary_tree.h"
#include <random>
#include <iostream>

int main (int argc, char *argv[])
{
  BinaryTree<int> tree_1;
  tree_1.insert(8,5,2,6,10,9,11);
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

    return 0;
}
