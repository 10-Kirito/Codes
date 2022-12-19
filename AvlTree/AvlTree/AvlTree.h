#include <iostream>
#include <algorithm>
using namespace std;
#pragma once

//平衡二叉树结点
template <typename T>
struct AvlNode
{
    T data;
    int height; //结点所在高度
    AvlNode<T>* left;
    AvlNode<T>* right;
    AvlNode<T>(const T theData) : data(theData), left(NULL), right(NULL), height(0) {}
};

//AvlTree
template <typename T>
class AvlTree
{
public:
    AvlTree<T>() {}
    ~AvlTree<T>() {}
    AvlNode<T>* root;
    //插入结点
    void Insert(AvlNode<T>*& t, T x);
    //删除结点
    bool Delete(AvlNode<T>*& t, T x);
    //查找是否存在给定值的结点
    bool Contains(AvlNode<T>* t, const T x) const;
    //中序遍历
    void InorderTraversal(AvlNode<T>* t);
    //前序遍历
    void PreorderTraversal(AvlNode<T>* t);
    //最小值结点
    AvlNode<T>* FindMin(AvlNode<T>* t) const;
    //最大值结点
    AvlNode<T>* FindMax(AvlNode<T>* t) const;
private:
    //求树的高度
    int GetHeight(AvlNode<T>* t);
    //单旋转 左
    AvlNode<T>* LL(AvlNode<T>* t);
    //单旋转 右
    AvlNode<T>* RR(AvlNode<T>* t);
    //双旋转 右左
    AvlNode<T>* LR(AvlNode<T>* t);
    //双旋转 左右
    AvlNode<T>* RL(AvlNode<T>* t);
};

template <typename T>
AvlNode<T>* AvlTree<T>::FindMax(AvlNode<T>* t) const
{
    if (t == NULL)
        return NULL;
    if (t->right == NULL)
        return t;
    return FindMax(t->right);
}

template <typename T>
AvlNode<T>* AvlTree<T>::FindMin(AvlNode<T>* t) const
{
    if (t == NULL)
        return NULL;
    if (t->left == NULL)
        return t;
    return FindMin(t->left);
}


template <typename T>
int AvlTree<T>::GetHeight(AvlNode<T>* t)
{
    if (t == NULL)
        return -1;
    else
        return t->height;
}


//单旋转
//左左插入导致的不平衡
template <typename T>
AvlNode<T>* AvlTree<T>::LL(AvlNode<T>* t)
{
    AvlNode<T>* q = t->left;
    t->left = q->right;
    q->right = t;
    t = q;
    t->height = max(GetHeight(t->left), GetHeight(t->right)) + 1;
    q->height = max(GetHeight(q->left), GetHeight(q->right)) + 1;
    return q;
}

//单旋转
//右右插入导致的不平衡
template <typename T>
AvlNode<T>* AvlTree<T>::RR(AvlNode<T>* t)
{
    AvlNode<T>* q = t->right;
    t->right = q->left;
    q->left = t;
    t = q;
    t->height = max(GetHeight(t->left), GetHeight(t->right)) + 1;
    q->height = max(GetHeight(q->left), GetHeight(q->right)) + 1;
    return q;
}

//双旋转
//插入点位于t的左儿子的右子树
template <typename T>
AvlNode<T>* AvlTree<T>::LR(AvlNode<T>* t)
{
    //双旋转可以通过两次单旋转实现
    //对t的左结点进行RR旋转，再对根节点进行LL旋转
    RR(t->left);
    return LL(t);
}

//双旋转
//插入点位于t的右儿子的左子树
template <typename T>
AvlNode<T>* AvlTree<T>::RL(AvlNode<T>* t)
{
    LL(t->right);
    return RR(t);
}


template <typename T>
void AvlTree<T>::Insert(AvlNode<T>*& t, T x)
{
    if (t == NULL)
        t = new AvlNode<T>(x);
    else if (x < t->data)
    {
        Insert(t->left, x);
        //判断平衡情况
        if (GetHeight(t->left) - GetHeight(t->right) > 1)
        {
            //分两种情况 左左或左右

            if (x < t->left->data)//左左
                t = LL(t);
            else                  //左右
                t = LR(t);
        }
    }
    else if (x > t->data)
    {
        Insert(t->right, x);
        if (GetHeight(t->right) - GetHeight(t->left) > 1)
        {
            if (x > t->right->data)
                t = RR(t);
            else
                t = RL(t);
        }
    }
    else
        ;//数据重复
    t->height = max(GetHeight(t->left), GetHeight(t->right)) + 1;
}

template <typename T>
bool AvlTree<T>::Delete(AvlNode<T>*& t, T x)
{
    //t为空 未找到要删除的结点
    if (t == NULL)
        return false;
    //找到了要删除的结点
    else if (t->data == x)
    {
        //左右子树都非空
        if (t->left != NULL && t->right != NULL)
        {//在高度更大的那个子树上进行删除操作

            //左子树高度大，删除左子树中值最大的结点，将其赋给根结点
            if (GetHeight(t->left) > GetHeight(t->right))
            {
                t->data = FindMax(t->left)->data;
                Delete(t->left, t->data);
            }
            else//右子树高度更大，删除右子树中值最小的结点，将其赋给根结点
            {
                t->data = FindMin(t->right)->data;
                Delete(t->right, t->data);
            }
        }
        else
        {//左右子树有一个不为空，直接用需要删除的结点的子结点替换即可
            AvlNode<T>* old = t;
            t = t->left ? t->left : t->right;//t赋值为不空的子结点
            delete old;
        }
    }
    else if (x < t->data)//要删除的结点在左子树上
    {
        //递归删除左子树上的结点
        Delete(t->left, x);
        //判断是否仍然满足平衡条件
        if (GetHeight(t->right) - GetHeight(t->left) > 1)
        {
            if (GetHeight(t->right->left) > GetHeight(t->right->right))
            {
                //RL双旋转
                t = RL(t);
            }
            else
            {//RR单旋转
                t = RR(t);
            }
        }
        else//满足平衡条件 调整高度信息
        {
            t->height = max(GetHeight(t->left), GetHeight(t->right)) + 1;
        }
    }
    else//要删除的结点在右子树上
    {
        //递归删除右子树结点
        Delete(t->right, x);
        //判断平衡情况
        if (GetHeight(t->left) - GetHeight(t->right) > 1)
        {
            if (GetHeight(t->left->right) > GetHeight(t->left->left))
            {
                //LR双旋转
                t = LR(t);
            }
            else
            {
                //LL单旋转
                t = LL(t);
            }
        }
        else//满足平衡性 调整高度
        {
            t->height = max(GetHeight(t->left), GetHeight(t->right)) + 1;
        }
    }

    return true;
}

//查找结点
template <typename T>
bool AvlTree<T>::Contains(AvlNode<T>* t, const T x) const
{
    if (t == NULL)
        return false;
    if (x < t->data)
        return Contains(t->left, x);
    else if (x > t->data)
        return Contains(t->right, x);
    else
        return true;
}

//中序遍历
template <typename T>
void AvlTree<T>::InorderTraversal(AvlNode<T>* t)
{
    if (t)
    {
        InorderTraversal(t->left);
        cout << t->data << ' ';
        InorderTraversal(t->right);
    }
}

//前序遍历
template <typename T>
void AvlTree<T>::PreorderTraversal(AvlNode<T>* t)
{
    if (t)
    {
        cout << t->data << ' ';
        PreorderTraversal(t->left);
        PreorderTraversal(t->right);
    }
}