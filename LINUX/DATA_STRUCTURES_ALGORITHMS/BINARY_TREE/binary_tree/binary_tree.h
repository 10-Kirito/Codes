#ifndef BINARY_TREE_H
#define BINARY_TREE_H
/**
 * Attention:
 *
 * The insertion of this binary tree is implementated based on
 * the binary search tree. Of course, you can alse add other
 * methods of initializing the binary tree.
 *
 */
#include <algorithm>
#include <iostream>
#include <ostream>
#include <queue>
#include <stack>
#include <unordered_map>
#include <vector>
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
  // use inorder and postorder to construct the binary tree:
  BinaryTree(const std::vector<T> &inorder, const std::vector<T> &postorder) {
    root = buildTree(inorder, postorder);
  }
  // use inorder and preorder to construct the binary tree:
  BinaryTree(const std::vector<T> &inorder, const std::vector<T> &preorder,
             bool) {
    root = buildTree(inorder, preorder, true);
  }
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

  // traversal(recursive):
  // 1. preorder tarversal;
  // 2. inorder tarversal;
  // 3. postorder tarversal;

  void preorderTarversal(void (*visit)(const T &)) const {
    _preorderTarversal(root, visit);
  };
  void inorderTarversal(void (*visit)(const T &)) const {
    _inorderTarversal(root, visit);
  };
  void postTarversal(void (*visit)(const T &)) const {
    _postorderTarversal(root, visit);
  };

  // For the following iterative traversal methods, it is recommended to first
  // order traversal memory (visit, true), in-order traversal memory (visit,
  // true, true), and post-order traversal memory (visit, true)

  // tarversal(non-recursive, also known as iterative methods)
  // 1. preorder tarversal(******);
  // 2. inorder tarversal;
  // 3. postorder tarversal(******);

  void preorderTarversal(void (*visit)(const T &), bool) const;
  void inorderTarversal(void (*visit)(const T &), bool) const;
  void postorderTarversal(void (*visit)(const T &), bool) const;

  // Unified style traversal iteration algorithm:
  // (Token marking methods)
  // 1. preorder tarversal;
  // 2. inorder tarversal(******);
  // 3. postorder tarversal;

  void preorderTarversal(void (*visit)(const T &), bool, bool) const;
  void inorderTarversal(void (*visit)(const T &), bool, bool) const;
  void postorderTarversal(void (*visit)(const T &), bool, bool) const;

  // Binary tree level order traversal:
  void levelorderTarversal(void (*visit)(const T &)) const;

  // invertTree(recursive)
  void invertTree(TreeNode<T> *);
  // invertTree(non-recursive)
  void invertTree();
  // determine whether a binary tree is centrally symmetric:
  bool compare() const;

private:
  // helper functions:
  // deep copy the entire binary tree:
  TreeNode<T> *_copy(TreeNode<T> *);

  // clear all the tree nodes:
  void _clear(TreeNode<T> *);
  // insert a node in order of size:
  void _insert(TreeNode<T> *&, const T &);
  void _insert(TreeNode<T> *&, T &&);

  // tarversal:
  // 1. preorder tarversal;
  // 2. inorder tarversal;
  // 3. postorder tarversal;
  //
  void _preorderTarversal(TreeNode<T> *node, void (*visit)(const T &)) const;
  void _inorderTarversal(TreeNode<T> *node, void (*visit)(const T &)) const;
  void _postorderTarversal(TreeNode<T> *node, void (*visit)(const T &)) const;

  // Construct a binary tree using inorder and postorder:
  TreeNode<T> *buildTree(const std::vector<T> &inorder,
                         const std::vector<T> &postorder);
  TreeNode<int> *buildHelper(const std::vector<T> &inorder,
                             const std::vector<T> &postorder, int instart,
                             int inend, int poststart, int postend,
                             std::unordered_map<T, int> &number_map);

  // Construct a binary tree using inorder and preorder:
  TreeNode<T> *buildTree(const std::vector<T> &inorder,
                         const std::vector<T> &preorder, bool);
  TreeNode<int> *buildHelper(const std::vector<T> &inorder,
                             const std::vector<T> &preorder, int instart,
                             int inend, int prestart, int preend,
                             std::unordered_map<T, int> &number_map, bool);

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

template <typename T>
void BinaryTree<T>::printTree() const {/* Dump(*this); */};

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

// Construct a binary tree using inorder and postorder:
template <typename T>
TreeNode<T> *BinaryTree<T>::buildTree(const std::vector<T> &inorder,
                                      const std::vector<T> &postorder) {
  if (inorder.size() == 0 || postorder.size() == 0) {
    return nullptr;
  }
  std::unordered_map<T, int> number_map;
  for (int i = 0; i < inorder.size(); ++i) {
    number_map[inorder[i]] = i;
  }
  return buildHelper(inorder, postorder, 0, inorder.size(), 0, postorder.size(),
                     number_map);
}

template <typename T>
TreeNode<int> *
BinaryTree<T>::buildHelper(const std::vector<T> &inorder,
                           const std::vector<T> &postorder, int instart,
                           int inend, int poststart, int postend,
                           std::unordered_map<T, int> &number_map) {
  // nullptr node:
  if (poststart == postend) {
    return nullptr;
  }

  int rootValue = postorder[postend - 1];
  TreeNode<T> *root = new TreeNode<T>(rootValue);
  // leaf node:
  if (instart == (inend - 1) && poststart == (postend - 1)) {
    return root;
  }

  // find the cut point in the inorder:
  int delemiterIndex = number_map[rootValue];
  // for (delemiterIndex = instart; delemiterIndex < inend; delemiterIndex++)
  // {
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

// Construct a binary tree using inorder and preorder:
template <typename T>
TreeNode<T> *BinaryTree<T>::buildTree(const std::vector<T> &inorder,
                                      const std::vector<T> &preorder, bool) {
  if (inorder.size() == 0 || preorder.size() == 0) {
    return nullptr;
  }

  std::unordered_map<int, int> number_map;

  for (int i = 0; i < inorder.size(); ++i) {
    number_map[inorder[i]] = i;
  }

  return buildHelper(inorder, preorder, 0, inorder.size(), 0, preorder.size(),
                     number_map, true);
};
template <typename T>
TreeNode<int> *
BinaryTree<T>::buildHelper(const std::vector<T> &inorder,
                           const std::vector<T> &preorder, int instart,
                           int inend, int prestart, int preend,
                           std::unordered_map<T, int> &number_map, bool) {
  if (prestart == preend) {
    return nullptr;
  }

  int rootValue = preorder[prestart];
  TreeNode<T> *root = new TreeNode<T>(rootValue);
  // leaf node:
  if ((prestart - preend) == 1) {
    return root;
  }

  int splitIndex = number_map[rootValue];

  int left_inorder_begin = instart;
  int left_inorder_end = splitIndex;

  int right_inorder_begin = splitIndex + 1;
  int right_inorder_end = inend;

  int left_preorder_begin = prestart + 1;
  int left_preorder_end = left_preorder_begin + splitIndex - instart;

  int right_preorder_begin = left_preorder_end;
  int right_preorder_end = preend;

  root->lchild =
      buildHelper(inorder, preorder, left_inorder_begin, left_inorder_end,
                   left_preorder_begin, left_preorder_end, number_map, true);
  root->rchild =
      buildHelper(inorder, preorder, right_inorder_begin, right_inorder_end,
                   right_preorder_begin, right_preorder_end, number_map, true);

  return root;
};

// tarversal:
// 1. preorder tarversal;
// 2. inorder tarversal;
// 3. postorder tarversal;
//
template <typename T>
void BinaryTree<T>::_preorderTarversal(TreeNode<T> *node,
                                       void (*visit)(const T &)) const {
  if (!node)
    return;
  visit(node->data);
  _preorderTarversal(node->lchild, visit);
  _preorderTarversal(node->rchild, visit);
}

template <typename T>
void BinaryTree<T>::_inorderTarversal(TreeNode<T> *node,
                                      void (*visit)(const T &)) const {
  if (!node)
    return;
  _inorderTarversal(node->lchild, visit);
  visit(node->data);
  _inorderTarversal(node->rchild, visit);
}

template <typename T>
void BinaryTree<T>::_postorderTarversal(TreeNode<T> *node,
                                        void (*visit)(const T &)) const {
  if (!node)
    return;
  _postorderTarversal(node->lchild, visit);
  _postorderTarversal(node->rchild, visit);
  visit(node->data);
}

// tarversal(non-recursive, also known as iterative methods)
// 1. preorder tarversal;
// 2. inorder tarversal;
// 3. postorder tarversal;
//
template <typename T>
void BinaryTree<T>::preorderTarversal(void (*visit)(const T &), bool) const {
  std::stack<TreeNode<T> *> _stack;

  if (empty()) {
    return;
  }

  _stack.push(root);

  while (!_stack.empty()) {
    TreeNode<T> *node = _stack.top();
    _stack.pop();

    visit(node->data);

    // attention the order of instack
    if (node->rchild)
      _stack.push(node->rchild);
    if (node->lchild)
      _stack.push(node->lchild);
  }
}

// important!!!
template <typename T>
void BinaryTree<T>::inorderTarversal(void (*visit)(const T &), bool) const {
  std::stack<TreeNode<T> *> _stack;
  TreeNode<T> *node = root;

  while (node || !_stack.empty()) {
    if (node) {
      _stack.push(node);
      node = node->lchild;
    } else {
      node = _stack.top();
      _stack.pop();
      visit(node->data);
      node = node->rchild;
    }
  }
}

// Important:
// preorder: mid -> left -> right
// We exchange the instack order of (node->lchild) and (node->rchild),
// there will be mid -> right -> left
// and we reverse the order,
// there will be left -> right -> mid.
// Thus we get the result.
template <typename T>
void BinaryTree<T>::postorderTarversal(void (*visit)(const T &), bool) const {
  std::stack<TreeNode<T> *> _stack;
  TreeNode<T> *node = root;
  std::vector<T> result;
  if (empty()) {
    return;
  }

  _stack.push(node);

  while (!_stack.empty()) {
    node = _stack.top();
    _stack.pop();
    result.push_back(node->data);

    if (node->lchild)
      _stack.push(node->lchild);
    if (node->rchild)
      _stack.push(node->rchild);
  }

  // we reserse the order, then we will get the result.
  std::reverse(result.begin(), result.end());
  for (const T &element : result) {
    visit(element);
  }
}

// Unified style traversal iteration algorithm:

template <typename T>
void BinaryTree<T>::preorderTarversal(void (*visit)(const T &), bool,
                                      bool) const {
  std::stack<TreeNode<T> *> _stack;

  if (!empty()) {
    _stack.push(root);
  }

  // begin:  rightnode ->  leftnode -> mid node
  // later:  mid node -> leftnode -> rightnode

  while (!_stack.empty()) {
    TreeNode<T> *node = _stack.top();

    if (node) {
      _stack.pop();
      // add the right node if not nullptr:
      if (node->rchild)
        _stack.push(node->rchild);

      if (node->lchild) {
        _stack.push(node->lchild);
      }
      _stack.push(node);
      // the key of this methods, we add a flag to the end of the visited node
      _stack.push(nullptr);

    } else {
      // if the top node of stack is nullptr, we are about to visit the
      // corresponding node
      _stack.pop();
      node = _stack.top();
      _stack.pop();
      visit(node->data);
    }
  }
};

template <typename T>
void BinaryTree<T>::inorderTarversal(void (*visit)(const T &), bool,
                                     bool) const {
  std::stack<TreeNode<T> *> _stack;

  if (!empty()) {
    _stack.push(root);
  }

  // begin: rightnode -> midnode -> leftnode
  // later: leftnode ->midnode -> rightnode

  while (!_stack.empty()) {
    TreeNode<T> *node = _stack.top();

    if (node) {
      _stack.pop();
      // add the right node if not nullptr:
      if (node->rchild)
        _stack.push(node->rchild);

      _stack.push(node);
      // the key of this methods, we add a flag to the end of the visited node
      _stack.push(nullptr);

      if (node->lchild) {
        _stack.push(node->lchild);
      }
    } else {
      // if the top node of stack is nullptr, we are about to visit the
      // corresponding node
      _stack.pop();
      node = _stack.top();
      _stack.pop();
      visit(node->data);
    }
  }
};

template <typename T>
void BinaryTree<T>::postorderTarversal(void (*visit)(const T &), bool,
                                       bool) const {
  std::stack<TreeNode<T> *> _stack;

  if (!empty()) {
    _stack.push(root);
  }

  // begin: midnode -> rightnode -> leftnode
  // later: leftnode ->rightnode -> midnode

  while (!_stack.empty()) {
    TreeNode<T> *node = _stack.top();

    if (node) {
      _stack.pop();

      _stack.push(node);
      // the key of this methods, we add a flag to the end of the visited node
      _stack.push(nullptr);

      // add the right node if not nullptr:
      if (node->rchild)
        _stack.push(node->rchild);

      if (node->lchild) {
        _stack.push(node->lchild);
      }
    } else {
      // if the top node of stack is nullptr, we are about to visit the
      // corresponding node
      _stack.pop();
      node = _stack.top();
      _stack.pop();
      visit(node->data);
    }
  }
};

template <typename T>
void BinaryTree<T>::levelorderTarversal(void (*visit)(const T &)) const {
  std::queue<TreeNode<T> *> _queue;

  if (!empty()) {
    _queue.push(root);
  }

  while (!_queue.empty()) {
    TreeNode<T> *node = _queue.front();

    // push the children of the front node:
    if (node->lchild) {
      _queue.push(node->lchild);
    }
    if (node->rchild) {
      _queue.push(node->rchild);
    }

    visit(node->data);
    _queue.pop();
  }
}

// use preorder tarversal to invert every node's children:
template <typename T> void BinaryTree<T>::invertTree(TreeNode<T> *node) {
  if (node == nullptr) {
    return;
  }
  TreeNode<T> *temp = node->lchild;
  node->lchild = node->rchild;
  node->rchild = temp;
  invertTree(node->lchild);
  invertTree(node->rchild);
}

// invertTree(non-recursive)
template <typename T> void BinaryTree<T>::invertTree() {
  std::stack<TreeNode<T> *> _stack;

  if (!empty()) {
    _stack.push(root);
  }

  while (!_stack.empty()) {
    TreeNode<T> *node = _stack.top();
    if (node) {
      _stack.pop();

      _stack.push(node);
      _stack.push(nullptr);

      if (node->lchild) {
        _stack.push(node->lchild);
      }
      if (node->rchild) {
        _stack.push(node->rchild);
      }
    } else {
      _stack.pop();
      node = _stack.top();
      TreeNode<T> *temp = node->lchild;
      node->lchild = node->rchild;
      node->rchild = temp;
      _stack.pop();
    }
  }
}

// determine whether a binary tree is centrally symmetric:
template <typename T> bool BinaryTree<T>::compare() const { return true; }

#endif // !BINARY_TREE_H
