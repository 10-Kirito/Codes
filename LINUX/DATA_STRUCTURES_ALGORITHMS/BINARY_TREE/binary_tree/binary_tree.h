#ifndef BINARY_TREE_H
#define BINARY_TREE_H
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <ostream>
// the binary tree node:
template <typename T> struct TreeNode {
  T data;
  TreeNode *lchild;
  TreeNode *rchild;

  // default constructor:
  TreeNode() : lchild{nullptr}, rchild{nullptr} {};

  TreeNode(const T &d = T(), TreeNode *leftchild = nullptr,
           TreeNode *rightchild = nullptr)
      : data{d}, lchild{leftchild}, rchild{rightchild} {};

  TreeNode(T &&d, TreeNode *leftchild = nullptr, TreeNode *rightchild = nullptr)
      : data{std::move(d)}, lchild(leftchild), rchild(rightchild){};

  int height() const {
    const int left_height = lchild ? lchild->height() : 0;
    const int right_child = rchild ? rchild->height() : 0;
    return ((left_height > right_child) ? left_height : right_child) + 1;
  }
};

// the binary tree class:
template <typename T> class BinaryTree {
private:
  // the binary tree struct:
public:
  // default constructor:
  BinaryTree();
  BinaryTree(const BinaryTree &rhs);
  BinaryTree(BinaryTree &&rhs);
  BinaryTree &operator=(const BinaryTree &rhs);
  BinaryTree &operator=(BinaryTree &&rhs);
  ~BinaryTree();

  // functions:
  bool empty() const { return root == nullptr; };
  void clear();
  int height() const;
  void printTree() const;
  void insert(const T &);
  void insert(T &&);
  template <typename... Args> void insert(const T &value, Args... more) {
    insert(value);
    insert(more...);
  }
  TreeNode<T> *getRoot() const { return root; }

private:
  // helper functions:
  // deep copy the entire binary tree:
  TreeNode<T> *_copy(TreeNode<T> *);

  // clear all the tree nodes:
  void _clear(TreeNode<T> *);
  // insert a node in order of size:
  void _insert(TreeNode<T> *&, const T &);
  void _insert(TreeNode<T> *&, T &&);

  TreeNode<T> *root;
};

// default constructor:
template <typename T> BinaryTree<T>::BinaryTree() : root{nullptr} {}

// copy constructor:
template <typename T>
BinaryTree<T>::BinaryTree(const BinaryTree &rhs) : root{nullptr} {
  root = _copy(rhs.root);
}

// assignment operator:
template <typename T>
BinaryTree<T> &BinaryTree<T>::operator=(const BinaryTree<T> &rhs) {
  // use the copy constructor to create a copy tree
  BinaryTree<T> copy = rhs;

  std::swap(*this, copy);

  return *this;
}

// move assignment:
template <typename T>
BinaryTree<T> &BinaryTree<T>::operator=(BinaryTree<T> &&rhs) {
  std::swap(root, rhs.root);
  return *this;
}

// destructor:
template <typename T> BinaryTree<T>::~BinaryTree<T>() { _clear(root); }

// functions:
//
// clear the tree:
template <typename T> void BinaryTree<T>::clear() { _clear(root); }

// insert the element into tree:
template <typename T> void BinaryTree<T>::insert(const T &value) {
  _insert(root, value);
}

template <typename T> void BinaryTree<T>::insert(T &&value) {
  _insert(root, std::move(value));
}

template <typename T> void BinaryTree<T>::printTree() const { /* Dump(*this); */ };

// return the height of binary tree:
template <typename T> int BinaryTree<T>::height() const {
  return root ? root->height() : 0;
}

// helper functions:
// deep copy the entire binary tree:
template <typename T> TreeNode<T> *BinaryTree<T>::_copy(TreeNode<T> *node) {
  if (node == nullptr) {
    return nullptr;
  }

  // create a new node to achieve deep copy
  TreeNode<T> *newNode = new TreeNode(node->data);
  newNode->lchild = _copy(node->lchild);
  newNode->rchild = _copy(node->rchild);
  return newNode;
}

// clear all the tree nodes:
template <typename T> void BinaryTree<T>::_clear(TreeNode<T> *node) {
  if (node != nullptr) {
    _clear(node->lchild);
    _clear(node->rchild);
    delete node;
  }
}

// insert a node in order of size:
// recursive implementation:
template <typename T>
void BinaryTree<T>::_insert(TreeNode<T> *&node, const T &value) {
  if (node == nullptr) {
    node = new TreeNode(value);
  } else if (value < node->data) {
    _insert(node->lchild, value);
  } else if (value > node->data) {
    _insert(node->rchild, value);
  } else {
    // ignore case of duplicate
  }
}

// non-recursive implementation:
template <typename T>
void BinaryTree<T>::_insert(TreeNode<T> *&node, T &&value) {
  if (node == nullptr) {
    node = new TreeNode(std::move(value));
    return;
  }

  TreeNode<T> *current = node;

  bool flag = true;

  while (flag) {
    if (value < current->data) {
      if (current->lchild == nullptr) {
        current->lchild = new TreeNode<T>(std::move(value));
        flag = false;
      } else {
        current = current->lchild;
      }
    } else if (value > current->data) {
      if (current->rchild == nullptr) {
        current->rchild = new TreeNode<T>(std::move(value));
        flag = false;
      } else {
        current = current->rchild;
      }
    } else {
      flag = false;
      // ignore if value and node->data is same
    }
  }
}

#endif // !BINARY_TREE_H
