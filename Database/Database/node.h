#ifndef _NODE_
#define _NODE_

#include <stddef.h>

// B树节点
typedef struct TreeNode
{
    size_t _u_KeyNum;                   // 记录节点的键数量
    int _iarr_Keys[4];                  // 记录节点的键
    struct TreeNode* _ptr_Parent;           // 记录节点的父节点
    struct TreeNode* _ptrArr_children[4];   // 记录节点的子节点
} TreeNode, * ptrTreeNode;

// 队列节点
typedef struct QueueNode
{
    ptrTreeNode _ptrTNode_data;         // 记录树节点
    struct QueueNode* _ptrQNode_next;   // 记录队列的下一个节点
} QueueNode, * ptrQueueNode;

// 用一个B树节点创建一个队列节点
ptrQueueNode QueueNode_create(ptrTreeNode data);

#endif
