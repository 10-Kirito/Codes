#ifndef _NODE_
#define _NODE_

#include <stddef.h>

// B���ڵ�
typedef struct TreeNode
{
    size_t _u_KeyNum;                   // ��¼�ڵ�ļ�����
    int _iarr_Keys[4];                  // ��¼�ڵ�ļ�
    struct TreeNode* _ptr_Parent;           // ��¼�ڵ�ĸ��ڵ�
    struct TreeNode* _ptrArr_children[4];   // ��¼�ڵ���ӽڵ�
} TreeNode, * ptrTreeNode;

// ���нڵ�
typedef struct QueueNode
{
    ptrTreeNode _ptrTNode_data;         // ��¼���ڵ�
    struct QueueNode* _ptrQNode_next;   // ��¼���е���һ���ڵ�
} QueueNode, * ptrQueueNode;

// ��һ��B���ڵ㴴��һ�����нڵ�
ptrQueueNode QueueNode_create(ptrTreeNode data);

#endif
