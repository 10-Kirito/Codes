#ifndef __BINNARY_TREE_H__
#define __BINNARY_TREE_H__

#include "BinTreeNode.h" // 二叉树结点类
#include "LinkQueue.h"   // 链队列
#include "LinkStack.h"   //链式栈
#include <string>
// 二叉树类
template <class ElemType> class BinaryTree {
protected:
  //  二叉树的数据成员:
  BinTreeNode<ElemType> *root;

  //	辅助函数:
  BinTreeNode<ElemType> *CopyTree(BinTreeNode<ElemType> *t); // 复制二叉树

  void Destroy(BinTreeNode<ElemType> *&r); // 删除以r为根二叉树

  void PreOrder(BinTreeNode<ElemType> *r,
           void (*Visit)(const ElemType &)) const; // 先序遍历以r为根的二叉树

  void InOrder(BinTreeNode<ElemType> *r,
          void (*Visit)(const ElemType &)) const; // 中序遍历以r为根的二叉树

  void PostOrder(BinTreeNode<ElemType> *r,
            void (*Visit)(const ElemType &)) const; // 后序遍历以r为根的二叉树

  int Height(const BinTreeNode<ElemType> *r) const; // 求以r为根的二叉树的高

  int NodeCount(
      const BinTreeNode<ElemType> *r) const; // 求以r为根的二叉树的结点个数

  BinTreeNode<ElemType> *
  Parent(BinTreeNode<ElemType> *r,
         const BinTreeNode<ElemType> *p) const; // 在以r为根的二叉树中求p的双亲

public:
  //  二叉树方法声明及重载编译系统默认方法声明:
  BinaryTree();                           // 无参数的构造函数
  BinaryTree(const ElemType &e);          // 构造以e为根的二叉树
  virtual ~BinaryTree();                  // 析构函数
  BinTreeNode<ElemType> *GetRoot() const; // 返回二叉树的根
  bool IsEmpty() const;                   // 判断二叉树是否为空
  Status GetElem(BinTreeNode<ElemType> *p, ElemType &e) const;
  // 用e返回结点p元素值
  Status SetElem(BinTreeNode<ElemType> *p, const ElemType &e);
  // 将结点p的值置为e

  void InOrder(void (*Visit)(const ElemType &)) const; // 二叉树的中序遍历
  void InOrderwithStack(
      void (*Visit)(const ElemType &)) const; // 二叉树的非递归中序遍历
  void PreOrder(void (*Visit)(const ElemType &)) const; // 二叉树的先序遍历
  void PostOrder(void (*Visit)(const ElemType &)) const; // 二叉树的后序遍历
  void LevelOrder(void (*Visit)(const ElemType &)) const; // 二叉树的层次遍历
  int TransLevel(BinTreeNode<ElemType> *temp,
                 int level) const; // 遍历二叉树某一层
  int LeafCount() const;           // 求二叉树的叶子结点数

  void Revolute() const; // 将该二叉树所有的结点的左右子树交换

  bool IsCompleteBinaryTree(); // 判断该二叉树是否为完全二叉树
  int NodeCount() const;       // 求二叉树的结点个数
  BinTreeNode<ElemType> *LeftChild(const BinTreeNode<ElemType> *p) const;
  //  求结点p的左孩子
  BinTreeNode<ElemType> *RightChild(const BinTreeNode<ElemType> *p) const;
  // 求结点p的右孩子
  BinTreeNode<ElemType> *LeftSibling(const BinTreeNode<ElemType> *p) const;
  // 求结点p的左兄弟
  BinTreeNode<ElemType> *RightSibling(const BinTreeNode<ElemType> *p) const;
  // 求结点p的右兄弟
  BinTreeNode<ElemType> *Parent(const BinTreeNode<ElemType> *p) const;
  // 求结点p的双亲
  BinTreeNode<ElemType> *Find(const ElemType &e) const;
  // 查找元素e，查找成功返回结点指针，否则返回nullptr
  void InsertLeftChild(BinTreeNode<ElemType> *p, const ElemType &e);
  // 插入一个结点e作为p的左孩子
  void InsertRightChild(BinTreeNode<ElemType> *p, const ElemType &e);
  // 插入一个结点e作为p的右孩子
  void DeleteLeftChild(BinTreeNode<ElemType> *p);  // 删除p的左子树
  void DeleteRightChild(BinTreeNode<ElemType> *p); // 删除p的右子树
  int Height() const;                              // 求二叉树的高
  BinaryTree(const BinaryTree<ElemType> &t);       // 复制构造函数
  BinaryTree(BinTreeNode<ElemType> *r); // 建立以r为根的二叉树
  BinaryTree<ElemType> &operator=(const BinaryTree<ElemType> &t);
  // 赋值运算符重载
};

template <class ElemType>
void DisplayBTWithTreeShape(BinTreeNode<ElemType> *r, int level);
//	按树状形式显示以r为根的二叉树，level为层次数，可设根结点的层次数为1

template <class ElemType> void DisplayBTWithTreeShape(BinaryTree<ElemType> &bt);
//	树状形式显示二叉树

template <class ElemType>
void CreateBinaryTree(BinTreeNode<ElemType> *&r, ElemType pre[], ElemType in[],
                      int preLeft, int preRight, int inLeft, int inRight);
// 已知二叉树的先序序列pre[preLeft..preRight]和中序序列in[inLeft..inRight]构造以r为根的
// 二叉树

template<typename T>
void CreateBinaryTreePre(std::string &, BinTreeNode<T> *&);
// 已知二叉树的先序序列，根据该序列构造二叉树，并且返回根 
// 注意这里的先序序列是有处理的，即如果结点的左孩子或者右孩子为空的话，就会置为‘ ’
// 

template <class ElemType>
BinaryTree<ElemType> &CreateBinaryTree(ElemType pre[], ElemType in[], int n);
// 已知先序和中序序列构造二叉树

// 二叉树类的实现部分
template <class ElemType>
BinaryTree<ElemType>::BinaryTree()
// 操作结果：构造一个空二叉树
{
  root = nullptr;
}

template <class ElemType>
BinaryTree<ElemType>::~BinaryTree()
// 操作结果：删除二叉树--析造函数
{
  Destroy(root);
}

template <class ElemType>
BinTreeNode<ElemType> *BinaryTree<ElemType>::GetRoot() const
// 操作结果：返回二叉树的根
{
  return root;
}

template <class ElemType>
bool BinaryTree<ElemType>::IsEmpty() const
// 操作结果：判断二叉树是否为空
{
  return root == nullptr;
}

template <class ElemType>
Status BinaryTree<ElemType>::GetElem(BinTreeNode<ElemType> *p,
                                     ElemType &e) const
// 操作结果：用e返回结点p元素值,如果不存在结点p,函数返回NOT_PRESENT,否则返回ENTRY_FOUND
{
  if (p == nullptr)        // 不存在结点p
    return NOT_PRESENT; // 返回NOT_PRESENT
  else {                // 存在结点p
    e = p->data;        // 用e返回元素值
    return ENTRY_FOUND; // 返回ENTRY_FOUND
  }
}

template <class ElemType>
Status BinaryTree<ElemType>::SetElem(BinTreeNode<ElemType> *p,
                                     const ElemType &e)
// 操作结果：如果不存在结点p,则返回FAIL,否则返回SUCCESS,并将结点p的值设置为e
{
  if (p == nullptr)    // 不存在结点p
    return FAIL;    // 返回FAIL
  else {            // 存在结点p
    p->data = e;    // 将结点p的值设置为e
    return SUCCESS; // 返回SUCCESS
  }
}

template <class ElemType>
void BinaryTree<ElemType>::PreOrder(BinTreeNode<ElemType> *r,
                                    void (*Visit)(const ElemType &)) const
// 操作结果：先序遍历以r为根的二叉树
{
  if (r != nullptr) {
    (*Visit)(r->data);              // 首先访问根结点r
    PreOrder(r->leftChild, Visit);  // 再遍历r的左子树
    PreOrder(r->rightChild, Visit); // 最后遍历r的右子树
  }
}

template <class ElemType>
void BinaryTree<ElemType>::PreOrder(void (*Visit)(const ElemType &)) const
// 操作结果：先序遍历二叉树
{
  PreOrder(root, Visit);
}

template <class ElemType>
void BinaryTree<ElemType>::InOrder(BinTreeNode<ElemType> *r,
                                   void (*Visit)(const ElemType &)) const
// 操作结果：中序遍历以r为根的二叉树
{
  if (r != nullptr) {
    InOrder(r->leftChild, Visit);  // 首先遍历r的左子树
    (*Visit)(r->data);             // 再访问根结点r
    InOrder(r->rightChild, Visit); // 最后遍历r的右子树
  }
}

template <class ElemType>
void BinaryTree<ElemType>::InOrder(void (*Visit)(const ElemType &)) const
// 操作结果：中序遍历二叉树
{
  InOrder(root, Visit);
}

template <class ElemType>
void BinaryTree<ElemType>::InOrderwithStack(
    void (*Visit)(const ElemType &)) const
// 操作结果：非递归中序遍历二叉树
{
  LinkStack<BinTreeNode<ElemType> *> q; // 链式栈
  BinTreeNode<ElemType> *p = root;
  // BinTreeNode<ElemType>* e;
  while (p != nullptr || !q.IsEmpty()) {
    while (p != nullptr) {
      q.Push(p);
      p = p->leftChild;
    }
    if (!q.IsEmpty()) {
      q.Top(p);
      (*Visit)(p->data);
      q.Pop(p);
      p = p->rightChild;
    }
  }
}

template <class ElemType>
void BinaryTree<ElemType>::PostOrder(BinTreeNode<ElemType> *r,
                                     void (*Visit)(const ElemType &)) const
// 操作结果：后序遍历以r为根的二叉树
{
  if (r != nullptr) {
    PostOrder(r->leftChild, Visit);  // 首先遍历r的左子树
    PostOrder(r->rightChild, Visit); // 再遍历r的右子树
    (*Visit)(r->data);               // 最后访问根结点r
  }
}

template <class ElemType>
void BinaryTree<ElemType>::PostOrder(void (*Visit)(const ElemType &)) const
// 操作结果：后序遍历二叉树
{
  PostOrder(root, Visit);
}

template <class ElemType>
void BinaryTree<ElemType>::LevelOrder(void (*Visit)(const ElemType &)) const
// 操作结果：层次遍历二叉树
{
  LinkQueue<BinTreeNode<ElemType> *> q; // 定义队列q
  BinTreeNode<ElemType> *p;

  if (root != nullptr)
    q.EnQueue(root);     // 如果根非空,则入队
  while (!q.IsEmpty()) { // q非空,说明还有结点未访问
    q.DelQueue(p);       // 队头元素出队，并访问之
    (*Visit)(p->data);
    if (p->leftChild != nullptr)   // 队头元素左孩子非空
      q.EnQueue(p->leftChild);  // 左孩子入队
    if (p->rightChild != nullptr)  // 队头元素右孩子非空
      q.EnQueue(p->rightChild); // 右孩子入队
  }
}

template <class ElemType>
int BinaryTree<ElemType>::TransLevel(BinTreeNode<ElemType> *temp,
                                     int level) const
// 操作结果：遍历二叉树的某一层
{
  if (temp == nullptr || level <= 0)
    return 0;
  if (level == 1) {
    cout << temp->data << " ";
    return 1;
  }
  return TransLevel(temp->leftChild, level - 1) +
         TransLevel(temp->rightChild, level - 1);
}

template <class ElemType> int BinaryTree<ElemType>::LeafCount() const {
  // 利用层次遍历所有的的结点，如果出现没有孩子的结点说明该结点就是叶子结点，count加一；
  LinkQueue<BinTreeNode<ElemType> *> q;    // 定义队列q
  LinkQueue<BinTreeNode<ElemType> *> temp; // 定义队列temp存储叶子结点
  BinTreeNode<ElemType> *p;
  int count = 0;
  if (root != nullptr)
    q.EnQueue(root);     // 如果根非空,则入队
  while (!q.IsEmpty()) { // q非空,说明还有结点未访问
    q.DelQueue(p);       // 队头元素出队，并访问之
    if (p->leftChild == nullptr && p->rightChild == NULL)
      count++;
    if (p->leftChild != nullptr)   // 队头元素左孩子非空
      q.EnQueue(p->leftChild);  // 左孩子入队
    if (p->rightChild != nullptr)  // 队头元素右孩子非空
      q.EnQueue(p->rightChild); // 右孩子入队
  }
  return count;
}

template <class ElemType> void BinaryTree<ElemType>::Revolute() const {
  // 利用层次遍历所有的的结点，交换左右结点
  LinkQueue<BinTreeNode<ElemType> *> q; // 定义队列q
  BinTreeNode<ElemType> *p;
  BinTreeNode<ElemType> *temp;
  int count = 0;
  if (root != nullptr)
    q.EnQueue(root);     // 如果根非空,则入队
  while (!q.IsEmpty()) { // q非空,说明还有结点未访问
    q.DelQueue(p);       // 队头元素出队，并访问之
    temp = p->rightChild;
    p->rightChild = p->leftChild;
    p->leftChild = temp;
    if (p->leftChild != nullptr)   // 队头元素左孩子非空
      q.EnQueue(p->leftChild);  // 左孩子入队
    if (p->rightChild != nullptr)  // 队头元素右孩子非空
      q.EnQueue(p->rightChild); // 右孩子入队
  }
}

template <class ElemType> bool BinaryTree<ElemType>::IsCompleteBinaryTree() {
  // 判断二叉树是否为完全二叉树
  LinkQueue<BinTreeNode<ElemType> *> q; // 定义队列q
  BinTreeNode<ElemType> *p;
  BinTreeNode<ElemType> *temp;
  bool leaf = false;
  if (root != nullptr)
    q.EnQueue(root);     // 如果根非空,则入队
  while (!q.IsEmpty()) { // q非空,说明还有结点未访问
    q.DelQueue(p);       // 队头元素出队，并访问之
    // temp = p->rightChild;
    if ((leaf && (p->leftChild != nullptr || p->rightChild != NULL)) ||
        (p->leftChild == nullptr && p->rightChild != NULL))
      return false;
    if (p->leftChild != nullptr)   // 队头元素左孩子非空
      q.EnQueue(p->leftChild);  // 左孩子入队
    if (p->rightChild != nullptr)  // 队头元素右孩子非空
      q.EnQueue(p->rightChild); // 右孩子入队
    if ((p->leftChild != nullptr && p->rightChild == NULL) ||
        (p->leftChild == nullptr && p->rightChild == NULL))
      leaf = true;
  }
  return true;
}

template <class ElemType>
int BinaryTree<ElemType>::Height(const BinTreeNode<ElemType> *r) const
// 操作结果：返回以r为根的二叉树的高
{
  if (r == nullptr) // 空二叉树高为0
    return 0;
  else { // 非空二叉树高为左右子树的高的最大值再加1
    int lHeight, rHeight;
    lHeight = Height(r->leftChild);  // 左子树的高
    rHeight = Height(r->rightChild); // 右子树的高
    return (lHeight > rHeight ? lHeight : rHeight) + 1;
    // 非空二叉树高为左右子树的高的最大值再加1
  }
}

template <class ElemType>
int BinaryTree<ElemType>::Height() const
// 操作结果：返回二叉树的高
{
  return Height(root);
}

template <class ElemType>
BinaryTree<ElemType>::BinaryTree(const ElemType &e)
// 操作结果：建立以e为根的二叉树
{
  root = new BinTreeNode<ElemType>(e);
}

template <class ElemType>
int BinaryTree<ElemType>::NodeCount(const BinTreeNode<ElemType> *r) const
// 操作结果：返回以r为根的二叉树的结点个数
{
  if (r == nullptr)
    return 0; // 空二叉树结点个数为0
  else
    return NodeCount(r->leftChild) + NodeCount(r->rightChild) + 1;
  // 非空二叉树结点个为左右子树的结点个数之和再加1
}

template <class ElemType>
int BinaryTree<ElemType>::NodeCount() const
// 操作结果：返回二叉树的结点个数
{
  return NodeCount(root);
}

template <class ElemType>
BinTreeNode<ElemType> *
BinaryTree<ElemType>::LeftChild(const BinTreeNode<ElemType> *p) const
// 操作结果：返回二叉树结点p的左孩子
{
  return p->leftChild;
}

template <class ElemType>
BinTreeNode<ElemType> *
BinaryTree<ElemType>::RightChild(const BinTreeNode<ElemType> *p) const
// 操作结果：返回二叉树结点p的右孩子
{
  return p->rightChild;
}

template <class ElemType>
BinTreeNode<ElemType> *
BinaryTree<ElemType>::LeftSibling(const BinTreeNode<ElemType> *p) const
// 操作结果：返回二叉树结点p的左兄弟
{
  BinTreeNode<ElemType> *r = Parent(root, p);
  if (r == nullptr)
    return nullptr;
  else if (r->rightChild == p)
    return r->leftChild;
  else
    return nullptr;
}

template <class ElemType>
BinTreeNode<ElemType> *
BinaryTree<ElemType>::RightSibling(const BinTreeNode<ElemType> *p) const
// 操作结果：返回二叉树结点p的左兄弟
{
  BinTreeNode<ElemType> *r = Parent(root, p);
  if (r == nullptr)
    return nullptr;
  else if (r->leftChild == p)
    return r->rightChild;
  else
    return nullptr;
}

template <class ElemType>
BinTreeNode<ElemType> *
BinaryTree<ElemType>::Parent(BinTreeNode<ElemType> *r,
                             const BinTreeNode<ElemType> *p) const
// 操作结果：返回以r为根的二叉树, 结点p的双亲
{
  if (r == nullptr)
    return nullptr; // 空二叉树
  else if (r->leftChild == p || r->rightChild == p)
    return r; // r为p的双亲
  else {      // 在子树上求双亲
    BinTreeNode<ElemType> *tmp;
    tmp = Parent(r->leftChild, p); // 在左子树上求p的双亲
    if (tmp != nullptr)
      return tmp; // 双亲在左子树上

    tmp = Parent(r->rightChild, p); // 在右子树上求p的双亲
    if (tmp != nullptr)
      return tmp; // 双亲在右子树上
    else
      return nullptr; // 表示p无双亲
  }
}

template <class ElemType>
BinTreeNode<ElemType> *
BinaryTree<ElemType>::Parent(const BinTreeNode<ElemType> *p) const
// 操作结果：返回二叉树结点p的双亲
{
  return Parent(root, p);
}

template <class ElemType>
void BinaryTree<ElemType>::InsertLeftChild(BinTreeNode<ElemType> *p,
                                           const ElemType &e)
// 初始条件：p非空，
// 操作结果：插入元素值为e的结点为p的左孩子，如果p的左孩子非空，则p原有左子树成为e的左子树
{
  if (p == nullptr) // p空，返回
    return;
  else { // 插入左孩子
    BinTreeNode<ElemType> *child =
        new BinTreeNode<ElemType>(e);  // 元素值为e结点
    if (p->leftChild != nullptr)          // p的左孩子非空
      child->leftChild = p->leftChild; // p原有左子树成为e的左子树
    p->leftChild = child;              // e成为p的左孩子
    return;
  }
}

template <class ElemType>
void BinaryTree<ElemType>::InsertRightChild(BinTreeNode<ElemType> *p,
                                            const ElemType &e)
// 初始条件：p非空
// 操作结果：插入元素值为e的结点为p的右孩子，如果p的右孩子非空，则p原有右子树成为e的右子树
{
  if (p == nullptr) // p为空，返回
    return;
  else { // 插入右孩子
    BinTreeNode<ElemType> *child =
        new BinTreeNode<ElemType>(e);    // 元素值为e结点
    if (p->rightChild != nullptr)           // p的右孩子非空
      child->rightChild = p->rightChild; // p原有右子树成为e的右子树
    p->rightChild = child;               // e成为p的右孩子
    return;
  }
}

template <class ElemType>
void BinaryTree<ElemType>::DeleteLeftChild(BinTreeNode<ElemType> *p)
// 初始条件：p非空
// 操作结果：删除p左子树
{
  if (p == nullptr) // p为空
    return;
  else                     // p非空
    Destroy(p->leftChild); // 删除p左子树
}

template <class ElemType>
void BinaryTree<ElemType>::DeleteRightChild(BinTreeNode<ElemType> *p)
// 初始条件：p非空
// 操作结果：删除p右子树
{
  if (p == nullptr) // p为空
    return;
  else                      // p非空
    Destroy(p->rightChild); // 删除p右子树
}

template <class ElemType>
BinTreeNode<ElemType> *BinaryTree<ElemType>::Find(const ElemType &e) const
// 操作结果：返回二叉树结点p的双亲
{
  LinkQueue<BinTreeNode<ElemType> *> q; // 定义队列q
  BinTreeNode<ElemType> *p;

  if (root != nullptr)
    q.EnQueue(root);     // 如果根非空,则入队
  while (!q.IsEmpty()) { // q非空,说明还有结点未访问
    q.DelQueue(p);       // 队头元素出队，并访问之
    if (p->data == e)
      return p;
    if (p->leftChild != nullptr)   // 队头元素左孩子非空
      q.EnQueue(p->leftChild);  // 左孩子入队
    if (p->rightChild != nullptr)  // 队头元素右孩子非空
      q.EnQueue(p->rightChild); // 右孩子入队
  }
  return nullptr;
}

template <class ElemType>
void BinaryTree<ElemType>::Destroy(BinTreeNode<ElemType> *&r)
// 操作结果：删除以r的二叉树
{
  if (r != nullptr) {          // r非空,实施删除
    Destroy(r->leftChild);  // 删除左子树
    Destroy(r->rightChild); // 删除右子树
    delete r;               // 删除根结点
    r = nullptr;
  }
}

template <class ElemType>
BinTreeNode<ElemType> *BinaryTree<ElemType>::CopyTree(BinTreeNode<ElemType> *t)
// 操作结果：将以t为根的二叉树复制成新的二叉树,返回新二叉树的根
{
  if (t == nullptr) // 复制空二叉树
    return nullptr; // 空二叉树根为空
  else {         // 复制非空二叉树
    BinTreeNode<ElemType> *lChild = CopyTree(t->leftChild);  // 复制左子树
    BinTreeNode<ElemType> *rChild = CopyTree(t->rightChild); // 复制右子树
    BinTreeNode<ElemType> *r =
        new BinTreeNode<ElemType>(t->data, lChild, rChild);
    // 复制根结点
    return r;
  }
}

template <class ElemType>
BinaryTree<ElemType>::BinaryTree(const BinaryTree<ElemType> &t)
// 操作结果：由已知二叉树构造新二叉树——复制构造函数
{
  root = CopyTree(t.root); // 复制二叉树
}

template <class ElemType>
BinaryTree<ElemType>::BinaryTree(BinTreeNode<ElemType> *r)
// 操作结果：建立以r为根的二叉树
{
  root = r; // 复制二叉树
}

template <class ElemType>
BinaryTree<ElemType> &
BinaryTree<ElemType>::operator=(const BinaryTree<ElemType> &t)
// 操作结果：由已知二叉树t复制到当前二叉树--赋值运算符重载
{
  if (&t != this) {
    Destroy(root);           // 释放原二叉树所占用空间
    root = CopyTree(t.root); // 复制二叉树
  }
  return *this;
}

template <class ElemType>
void DisplayBTWithTreeShape(BinTreeNode<ElemType> *r, int level)
// 操作结果：按树状形式显示以r为根的二叉树，level为层次数，可设根结点的层次数为1
{
  if (r != nullptr) { // 空树不显式，只显式非空树
    DisplayBTWithTreeShape<ElemType>(r->rightChild, level + 1); // 显示右子树
    cout << endl;                                               // 显示新行
    for (int i = 0; i < level - 1; i++)
      cout << " ";   // 确保在第level列显示结点
    cout << r->data; // 显示结点
    DisplayBTWithTreeShape<ElemType>(r->leftChild, level + 1); // 显示左子树
  }
}

template <class ElemType>
void DisplayBTWithTreeShape(BinaryTree<ElemType> &bt)
// 操作结果：树状形式显示二叉树
{
  DisplayBTWithTreeShape<ElemType>(bt.GetRoot(), 1);
  // 树状显示以bt.GetRoot()为根的二叉树
  cout << endl;
}

template <class ElemType>
void CreateBinaryTree(BinTreeNode<ElemType> *&r, ElemType pre[], ElemType in[],
                      int preLeft, int preRight, int inLeft, int inRight)
// 操作结果：已知二叉树的先序序列pre[preLeft..preRight]和中序序列in[inLeft..inRight]构造
//	以r为根的二叉树
{
  if (inLeft > inRight) // 二叉树无结点,空二叉树
    r = nullptr;           // 空二叉树根为空
  else {                // 二叉树有结点,非空二叉树
    r = new BinTreeNode<ElemType>(pre[preLeft]); // 生成根结点
    int mid = inLeft;
    while (
        in[mid] !=
        pre[preLeft]) // 查找pre[preLeft]在in[]中的位置,也就是中序序列中根的位置
      mid++;
    CreateBinaryTree(r->leftChild, pre, in, preLeft + 1, preLeft + mid - inLeft,
                     inLeft, mid - 1);
    // 生成左子树
    CreateBinaryTree(r->rightChild, pre, in, preLeft + mid - inLeft + 1,
                     preRight, mid + 1,
                     inRight); // 生成右子树
  }
}

template <class ElemType>
BinaryTree<ElemType> &CreateBinaryTree(ElemType pre[], ElemType in[], int n)
// 操作结果：已知先序和中序序列构造二叉树
{
  BinTreeNode<ElemType> *r; // 二叉树的根
  CreateBinaryTree<ElemType>(r, pre, in, 0, n - 1, 0, n - 1);
  // 由先序和中序序列构造以r为根的二叉树
  BinaryTree<ElemType> *bt = new BinaryTree<ElemType>(r); // 生成二叉树
  return *bt;
}

template<typename T>
void CreateBinaryTreePre(std::string &str, BinTreeNode<T> *&root) {
  char ch;
  if (!str.empty()) {
    ch = str[0];
    str = str.substr(1);
  }

  if (ch == ' ') {
    root = nullptr;
  }else {
    root->data = ch;
    root->leftChild = new BinTreeNode<char>;
    root->rightChild = new BinTreeNode<char>;
    CreateBinaryTreePre(str, root->leftChild);
    CreateBinaryTreePre(str, root->rightChild);
  }
}
// 已知二叉树的先序序列，根据该序列构造二叉树，并且返回根 
// 注意这里的先序序列是有处理的，即如果结点的左孩子或者右孩子为空的话，就会置为‘ ’
// 

#endif
