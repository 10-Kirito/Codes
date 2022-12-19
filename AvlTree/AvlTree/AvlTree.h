#include <iostream>
#include <algorithm>
using namespace std;
#pragma once

//ƽ����������
template <typename T>
struct AvlNode
{
    T data;
    int height; //������ڸ߶�
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
    //������
    void Insert(AvlNode<T>*& t, T x);
    //ɾ�����
    bool Delete(AvlNode<T>*& t, T x);
    //�����Ƿ���ڸ���ֵ�Ľ��
    bool Contains(AvlNode<T>* t, const T x) const;
    //�������
    void InorderTraversal(AvlNode<T>* t);
    //ǰ�����
    void PreorderTraversal(AvlNode<T>* t);
    //��Сֵ���
    AvlNode<T>* FindMin(AvlNode<T>* t) const;
    //���ֵ���
    AvlNode<T>* FindMax(AvlNode<T>* t) const;
private:
    //�����ĸ߶�
    int GetHeight(AvlNode<T>* t);
    //����ת ��
    AvlNode<T>* LL(AvlNode<T>* t);
    //����ת ��
    AvlNode<T>* RR(AvlNode<T>* t);
    //˫��ת ����
    AvlNode<T>* LR(AvlNode<T>* t);
    //˫��ת ����
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


//����ת
//������뵼�µĲ�ƽ��
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

//����ת
//���Ҳ��뵼�µĲ�ƽ��
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

//˫��ת
//�����λ��t������ӵ�������
template <typename T>
AvlNode<T>* AvlTree<T>::LR(AvlNode<T>* t)
{
    //˫��ת����ͨ�����ε���תʵ��
    //��t���������RR��ת���ٶԸ��ڵ����LL��ת
    RR(t->left);
    return LL(t);
}

//˫��ת
//�����λ��t���Ҷ��ӵ�������
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
        //�ж�ƽ�����
        if (GetHeight(t->left) - GetHeight(t->right) > 1)
        {
            //��������� ���������

            if (x < t->left->data)//����
                t = LL(t);
            else                  //����
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
        ;//�����ظ�
    t->height = max(GetHeight(t->left), GetHeight(t->right)) + 1;
}

template <typename T>
bool AvlTree<T>::Delete(AvlNode<T>*& t, T x)
{
    //tΪ�� δ�ҵ�Ҫɾ���Ľ��
    if (t == NULL)
        return false;
    //�ҵ���Ҫɾ���Ľ��
    else if (t->data == x)
    {
        //�����������ǿ�
        if (t->left != NULL && t->right != NULL)
        {//�ڸ߶ȸ�����Ǹ������Ͻ���ɾ������

            //�������߶ȴ�ɾ����������ֵ���Ľ�㣬���丳�������
            if (GetHeight(t->left) > GetHeight(t->right))
            {
                t->data = FindMax(t->left)->data;
                Delete(t->left, t->data);
            }
            else//�������߶ȸ���ɾ����������ֵ��С�Ľ�㣬���丳�������
            {
                t->data = FindMin(t->right)->data;
                Delete(t->right, t->data);
            }
        }
        else
        {//����������һ����Ϊ�գ�ֱ������Ҫɾ���Ľ����ӽ���滻����
            AvlNode<T>* old = t;
            t = t->left ? t->left : t->right;//t��ֵΪ���յ��ӽ��
            delete old;
        }
    }
    else if (x < t->data)//Ҫɾ���Ľ������������
    {
        //�ݹ�ɾ���������ϵĽ��
        Delete(t->left, x);
        //�ж��Ƿ���Ȼ����ƽ������
        if (GetHeight(t->right) - GetHeight(t->left) > 1)
        {
            if (GetHeight(t->right->left) > GetHeight(t->right->right))
            {
                //RL˫��ת
                t = RL(t);
            }
            else
            {//RR����ת
                t = RR(t);
            }
        }
        else//����ƽ������ �����߶���Ϣ
        {
            t->height = max(GetHeight(t->left), GetHeight(t->right)) + 1;
        }
    }
    else//Ҫɾ���Ľ������������
    {
        //�ݹ�ɾ�����������
        Delete(t->right, x);
        //�ж�ƽ�����
        if (GetHeight(t->left) - GetHeight(t->right) > 1)
        {
            if (GetHeight(t->left->right) > GetHeight(t->left->left))
            {
                //LR˫��ת
                t = LR(t);
            }
            else
            {
                //LL����ת
                t = LL(t);
            }
        }
        else//����ƽ���� �����߶�
        {
            t->height = max(GetHeight(t->left), GetHeight(t->right)) + 1;
        }
    }

    return true;
}

//���ҽ��
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

//�������
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

//ǰ�����
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