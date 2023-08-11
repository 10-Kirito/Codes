#include <iostream>
#include <string>
#include "thread_tree.h"

template<typename T>
void output(const T & t){
  std::cout << t << " " << std::flush;
}

int main (int argc, char *argv[])
{
  std::string pre = "ABC  DE G  F   ";
  ThreadTree<char> thread_tree(pre);
  ThreadTreeNode<char> *root = thread_tree.get_root();
  thread_tree.inorder_traversal(&output);
  std::cout << std::endl;
  thread_tree.preorder_traversal(&output);
  std::cout << std::endl;

  ThreadTree<char> thread_test(pre);
  ThreadTreeNode<char> * temp = nullptr;
  ThreadTreeNode<char> * test_node = thread_test.get_root();
  to_thread_tree(test_node, temp);
  thread_test.inorder_thread_tree(&output);
  
  std::cout << std::endl;
  return 0;
}



