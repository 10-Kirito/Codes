#include "thread_tree.h"
#include <iostream>
#include <string>

template <typename T> void output(const T &t) {
  std::cout << t << " " << std::flush;
}

int main(int argc, char *argv[]) {
  std::string pre = "ABC  DE G  F   ";
  ThreadTree<char> thread_tree(pre);
  ThreadTreeNode<char> *root = thread_tree.get_root();
  std::cout << "The binary tree is(inorder_traversal):";
  thread_tree.inorder_traversal(&output);
  std::cout << std::endl;

  ThreadTree<char> thread_test(pre);
  ThreadTreeNode<char> *temp = nullptr;
  ThreadTreeNode<char> *test_node = thread_test.get_root();
  std::cout << "Thread the binary_tree(inorder_traversal)!" << std::endl;
  to_thread_tree(test_node, temp, INORDER());
  std::cout << "ThreadTree traversal(inorder):";
  thread_test.inorder_thread_tree(&output);

  std::cout << std::endl;
  return 0;
}
