#ifndef _TREE_
#define _TREE_

#include "global.h"
#include "node.h"

#include <stddef.h>

/*
 * 设计的B树的键从下标1开始存放，于是对于给定的键的下标index
 * 其左孩子的下标为index - 1，其右孩子的下标为index
 */
typedef TreeNode* Tree;     // 定义树类型
typedef TreeNode** ptrTree; // 树指针，如果有的时候需要对树的根节点进行改动，就会使用这个类型

// 记录B树搜索结果
// 如果找到了节点，那么返回的就是节点本身
// 如果没有找到节点，返回的是应该插入的节点
typedef struct BTreeSearch
{
	ptrTreeNode _ptrNode_node;	// 记录搜索到的最后一个节点
	size_t _u_keyIndex;			// 记录键的下标
	EXEC_RST _exec_flag;		// 记录搜索的结果
} BTreeSearch;

// 初始化
EXEC_RST BTree_create(ptrTree pTree);
// 增：将键key添加到pTree中的节点node的下标index中
// 在调用本函数之前需要先调用BTree_search函数，获取pTree和index
EXEC_RST BTree_insert(ptrTree pTree, ptrTreeNode node, size_t index, int key);
// 删：删除pTree中的键key
EXEC_RST BTree_delete(ptrTree pTree, int key);
// 查：在tree中搜索键key，将搜索结果保存在result中
// 如果搜索失败，那么result中的_exec_flag位会被设置为FAIL
//      _ptrNode_node会指向要插入的节点
//      _u_keyIndex会指明要插入的下标
// 如果搜索成功，_exec_flag会被设置为SUCCESS
//      _ptrNode_node会指向键所在的节点
//      _u_keyIndex会指明键所在的下标
EXEC_RST BTree_search(Tree tree, int key, BTreeSearch* result);
// 释放空间
EXEC_RST Btree_free(ptrTree pTree);
// 打印树，逻辑为层级遍历
EXEC_RST BTree_print(Tree tree);

#endif
