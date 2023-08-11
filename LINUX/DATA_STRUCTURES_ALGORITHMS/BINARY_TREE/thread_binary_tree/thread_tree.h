#ifndef THREAD_TREE_H
#define THREAD_TREE_H

#include <string>
// Link == 0, pointer, Thread == 1, thread;
enum Tag { Link, Thread };

template <typename T> struct ThreadTreeNode {
  T data;
  ThreadTreeNode *lchild, *rchild;
  Tag ltag, rtag;
  ThreadTreeNode() : lchild(nullptr), rchild(nullptr), ltag(Link), rtag(Link) {}
};

template <typename T> class ThreadTree {
private:
  ThreadTreeNode<T> *_root;

  void inorder_traversal_tool(ThreadTreeNode<T> *, void (*)(const T &));
  void preorder_traversal_tool(ThreadTreeNode<T> *, void (*)(const T &));

public:
  ThreadTree() : _root(nullptr) {}
  // create binary tree according to the sequence of precedence
  ThreadTree(std::string);

  ThreadTreeNode<T> *&get_root() { return _root; }
  void inorder_traversal(void (*)(const T &));
  void preorder_traversal(void (*)(const T &));
  void inorder_thread_tree(void (*)(const T &));
};
template <typename T>
void create_binary_tree_pre(std::string &str, ThreadTreeNode<T> *&root);


template<typename T>
void to_thread_tree(ThreadTreeNode<T> *&root, ThreadTreeNode<T> *&pre) {
    
  // Attention!!
  //-------O----
  //------/-\---
  //-----O--O---
  // we can think from the easist one!


  if(root == nullptr)
    return;

  // 1. process the left child tree
  to_thread_tree(root->lchild, pre);

  // 2. process the current node
  if(root->lchild == nullptr) {
    root->lchild = pre;
    root->ltag = Thread;
  }

  // process the previous node's next node
  if (pre != nullptr && pre->rchild == nullptr) {
    pre->rchild = root;
    pre->rtag = Thread;
  }
  // move to the next node and save the previous node
  pre = root;

  // 3. process the right child tree
  to_thread_tree(root->rchild, pre);
}

template <typename T> ThreadTree<T>::ThreadTree(std::string str) {
  _root = new ThreadTreeNode<T>;
  create_binary_tree_pre<T>(str, _root);
}

template <typename T>
void ThreadTree<T>::inorder_traversal(void (*visit)(const T &)) {
  inorder_traversal_tool(_root, visit);
}

template <typename T>
void ThreadTree<T>::preorder_traversal(void (*visit)(const T &)) {
  preorder_traversal_tool(_root, visit);
}

template <typename T>
void ThreadTree<T>::inorder_traversal_tool(ThreadTreeNode<T> *p,
                                          void (*visit)(const T &)) {
  if (p != nullptr) {
    inorder_traversal_tool(p->lchild, visit);
    (*visit)(p->data);
    inorder_traversal_tool(p->rchild, visit);
  }
}

template <typename T>
void ThreadTree<T>::preorder_traversal_tool(ThreadTreeNode<T> *p,
                                           void (*visit)(const T &)) {
  if (p != nullptr) {
    (*visit)(p->data);
    preorder_traversal_tool(p->lchild, visit);
    preorder_traversal_tool(p->rchild, visit);
  }
}

template<typename T>
void ThreadTree<T>::inorder_thread_tree(void (*visit)(const T &)){
  ThreadTreeNode<T> *p = _root;
  while (p != nullptr) {
    while (p->ltag == 0) {
      p = p->lchild;
    }
    (*visit)(p->data);

    while (p->rtag == Thread) {
      p = p->rchild;
      (*visit)(p->data);
    }
    p = p->rchild;
  }
}

template <typename T>
void create_binary_tree_pre(std::string &str, ThreadTreeNode<T> *&root) {
  char ch;
  if (!str.empty()) {
    ch = str[0];
    str = str.substr(1);
  }

  if (ch == ' ') {
    root = nullptr;
  } else {
    root->data = ch;
    root->lchild = new ThreadTreeNode<T>;
    root->rchild = new ThreadTreeNode<T>;
    create_binary_tree_pre(str, root->lchild);
    create_binary_tree_pre(str, root->rchild);
  }
}

#endif // !THREAD_TREE_H
