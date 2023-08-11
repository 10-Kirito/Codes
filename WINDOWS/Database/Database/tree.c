#define _CRT_SECURE_NO_WARNINGS

#include "global.h"
#include "node.h"
#include "tree.h"
#include "queue.h"

#include <stdio.h>
#include <stdlib.h>

EXEC_RST BTree_create(Tree *tree)
{
	*tree = NULL;
	return SUCCESS;
}

// 在节点node中查找key
// 如果键被找到，那么返回其下标
// 否则返回键的可以被插入的合理下标
static size_t BTree_search_node(ptrTreeNode node, int key)
{
	size_t index;
	for (index = 0;
			index < node->_u_KeyNum && node->_iarr_Keys[index + 1] <= key;
			index++)
	{

	}

	return index;
}

EXEC_RST BTree_search(Tree tree, int key, BTreeSearch *result)
{
	ptrTreeNode cur = tree, prev = NULL;
    // 标志位，记录是否找到了键
	BOOL is_found= FALSE;
	size_t index;

    // 当树没有被遍历到叶节点，而且没有找到键，就继续寻找
	while (cur != NULL && !is_found)
	{
        // 获得"合理下标"
		index = BTree_search_node(cur, key);
        // 如果找到了键的下标，循环结束
		if (index > 0 && cur->_iarr_Keys[index] == key)
		{
			is_found = TRUE;
		}
        // 否则尝试向下一级子树寻找
		else
		{
            // 记录当前级的节点，以防没有找到
			prev = cur;
            // 进入对应的子树
			cur = cur->_ptrArr_children[index];
		}
	}

    // 根据是否找到来进行结果赋值
	if (is_found)
	{
		result->_ptrNode_node = cur;
		result->_u_keyIndex = index;
		result->_exec_flag = SUCCESS;
	}
	else
	{
		result->_ptrNode_node = prev;
		result->_u_keyIndex = index;
		result->_exec_flag = FAIL;
	}

	return SUCCESS;
}

// 创建一个新的结点，这个节点将成为树的新根
// 将key作为新节点的键，将ori_node作为左子树，new_node作为右子树
static void BTree_newRoot(ptrTree pTree, int key, ptrTreeNode ori_node, ptrTreeNode new_node)
{
    // 申请空间和初始化
	*pTree = (Tree)malloc(sizeof(TreeNode));
	(*pTree)->_u_KeyNum = 1;
	(*pTree)->_ptrArr_children[0] = ori_node;
	(*pTree)->_ptrArr_children[1] = new_node;
	(*pTree)->_iarr_Keys[1] = key;
	(*pTree)->_ptr_Parent = NULL;

    // 设置子节点的父节点
	if (ori_node) { ori_node->_ptr_Parent = *pTree; }
	if (new_node) { new_node->_ptr_Parent = *pTree; }
}

// 在节点pNode的下标index处插入键key和子树to_insert
static void BTree_insert_node(ptrTreeNode pNode, size_t index, int key, ptrTreeNode to_insert)
{
    // 循环变量
	int i;
    // 将下标index及以后得数据向后移一个位置
	for (i = pNode->_u_KeyNum; i > index; i--)
	{
		pNode->_iarr_Keys[i + 1] = pNode->_iarr_Keys[i];
		pNode->_ptrArr_children[i + 1] = pNode->_ptrArr_children[i];
	}

    // 将key放入到对应的位置
	pNode->_iarr_Keys[index + 1] = key;
    // 将子树插入到对应的位置
	pNode->_ptrArr_children[index + 1] = to_insert;
    // 更新节点的键数
	pNode->_u_KeyNum++;

    // 更新子树父节点
	if (to_insert) { to_insert->_ptr_Parent = pNode; }
}

// 分裂节点ori_node，将后半部分放入new_node
static void BTree_split_node(ptrTreeNode ori_node, ptrTreeNode* new_node)
{
	int index;
	int split_index = 2;

    // 申请内存
	*new_node = (ptrTreeNode)malloc(sizeof(TreeNode));
    // 保存子树
	(*new_node)->_ptrArr_children[0] = ori_node->_ptrArr_children[split_index];
    // 保存键
	for (index = split_index + 1; index <= 3; index ++)
	{
		(*new_node)->_iarr_Keys[index - split_index] = ori_node->_iarr_Keys[index];
		(*new_node)->_ptrArr_children[index - split_index] = ori_node->_ptrArr_children[index];
	}
	(*new_node)->_u_KeyNum = ori_node->_u_KeyNum - split_index;
	(*new_node)->_ptr_Parent = ori_node->_ptr_Parent;
    // 设置子树的父节点
	for (index = 0; index <= ori_node->_u_KeyNum - split_index; index++)
	{
		if ((*new_node)->_ptrArr_children[index])
		{
			(*new_node)->_ptrArr_children[index]->_ptr_Parent = (*new_node);
		}
	}

    // 更新源节点的键个数
	ori_node->_u_KeyNum = split_index - 1;
}

EXEC_RST BTree_insert(ptrTree pTree, ptrTreeNode node, size_t index, int key)
{
	ptrTreeNode pNode_tmp;
	BOOL flag_finished, flag_need_new_root;
	size_t split_index;
	int key_tmp;

	if (!node) { BTree_newRoot(pTree, key, NULL, NULL); }
	else
	{
		key_tmp = key;
		pNode_tmp = NULL;
		flag_finished = FALSE;
		flag_need_new_root = FALSE;
		while (!flag_finished && !flag_need_new_root)
		{
			BTree_insert_node(node, index, key_tmp, pNode_tmp);
			if (node->_u_KeyNum <= 2) { flag_finished = TRUE; }
			else
			{
				split_index = 2;
				BTree_split_node(node, &pNode_tmp);
				key_tmp = node->_iarr_Keys[split_index];

				if (node->_ptr_Parent)
				{
					node = node->_ptr_Parent;
					index = BTree_search_node(node, key_tmp);
				}
				else
				{
					flag_need_new_root = TRUE;
				}
			}
		}

		if (flag_need_new_root)
		{
			BTree_newRoot(pTree, key_tmp, node, pNode_tmp);
		}
	}

	return SUCCESS;
}

static EXEC_RST BTree_traverse(Tree tree, Queue queue, size_t flag_keepLine, size_t sum)
{
	size_t index;
	Tree tree_tmp;

	if (tree)
	{
		printf("  [");
		Queue_enqueue(queue, tree->_ptrArr_children[0]);
		for (index = 1; index <= tree->_u_KeyNum; index++)
		{
			printf(" %d ", tree->_iarr_Keys[index]);
			Queue_enqueue(queue, tree->_ptrArr_children[index]);
		}
		sum += tree->_u_KeyNum + 1;
		printf("]");
		if (!flag_keepLine)
		{
			printf("\n");
			flag_keepLine = sum - 1;
			sum = 0;
		}
		else
		{
			flag_keepLine--;
		}
	}

	if (!Queue_isEmpty(queue))
	{
		Queue_dequeue(queue, &tree_tmp);
        BTree_traverse(tree_tmp, queue, flag_keepLine, sum);
	}

	return SUCCESS;
}

EXEC_RST BTree_print(Tree tree)
{
	if (!tree) { printf("\tB树为空树\n"); return SUCCESS; }

	Queue queue;
	Queue_init(&queue);

	BTree_traverse(tree, queue, 0, 0);

	Queue_free(queue);

	return SUCCESS;
}

EXEC_RST Btree_free(ptrTree pTree)
{
    int index;
    ptrTreeNode iter = *pTree;
    if (iter != NULL)
    {
        for (index = 0; index <= iter->_u_KeyNum; index++)
        {
            Btree_free(&(iter->_ptrArr_children[index]));
        }
        free(iter);
    }

    *pTree = NULL;
    return SUCCESS;
}

static int FindBTNode(ptrTreeNode node, int key, int* index)
{
    if (key < node->_iarr_Keys[1])
    {
        *index = 0;
        return 0;
    }
    else
    {
        *index = node->_u_KeyNum;
        while (key < node->_iarr_Keys[*index] && (*index) > 1) { (*index)--; }

        if (key == node->_iarr_Keys[*index]) { return 1; }
    }
    return 0;
}

void BTree_set_node_substitution(ptrTreeNode node, int index)
{
    ptrTreeNode iter;
    for (iter = node->_ptrArr_children[index];
        iter->_ptrArr_children[0] != NULL;
        iter = iter->_ptrArr_children[0])
    {

    }
    node->_iarr_Keys[index] = iter->_iarr_Keys[1];
}

static void BTree_remove_node(ptrTreeNode node, int index)
{
    int iter;
    for (iter = index + 1; iter <= node->_u_KeyNum; iter++)
    {
        node->_iarr_Keys[iter - 1] = node->_iarr_Keys[iter];
        node->_ptrArr_children[iter - 1] = node->_ptrArr_children[iter];
    }
    node->_u_KeyNum--;
}

static void BTree_move_keys_left(ptrTreeNode node, int index)
{
    int iter;
    ptrTreeNode left = node->_ptrArr_children[index - 1];
    ptrTreeNode right = node->_ptrArr_children[index];

    left->_u_KeyNum++;
    left->_iarr_Keys[left->_u_KeyNum] = node->_iarr_Keys[index];
    left->_ptrArr_children[left->_u_KeyNum] = node->_ptrArr_children[index]->_ptrArr_children[0];

    node->_iarr_Keys[index] = right->_iarr_Keys[1];
    right->_ptrArr_children[0] = right->_ptrArr_children[1];
    right->_u_KeyNum--;

    for (iter = 1; iter <= left->_u_KeyNum; iter++)
    {
        left->_iarr_Keys[iter] = left->_iarr_Keys[iter + 1];
        left->_ptrArr_children[iter] = left->_ptrArr_children[iter + 1];
    }
}

static void BTree_move_keys_right(ptrTreeNode node, int index)
{
    /*将双亲结点p中的最后一个关键字移入右结点q中
    将左结点left中的最后一个关键字移入双亲结点p中*/
    int iter;
    ptrTreeNode right = node->_ptrArr_children[index];
    ptrTreeNode left = node->_ptrArr_children[index - 1];

    for (iter = right->_u_KeyNum; iter > 0; iter--)
    { //将右兄弟q中所有关键字向后移动一位
        right->_iarr_Keys[iter + 1] = right->_iarr_Keys[iter];
        right->_ptrArr_children[iter + 1] = right->_ptrArr_children[iter];
    }

    right->_ptrArr_children[1] = right->_ptrArr_children[0]; //从双亲结点p移动关键字到右兄弟q中
    right->_iarr_Keys[1] = node->_iarr_Keys[index];
    right->_u_KeyNum++;

    node->_iarr_Keys[index] = left->_iarr_Keys[left->_u_KeyNum]; //将左兄弟left中最后一个关键字移动到双亲结点p中
    node->_ptrArr_children[index]->_ptrArr_children[0] = left->_ptrArr_children[left->_u_KeyNum];
    left->_u_KeyNum--;
}

static void BTree_combine_keys(ptrTreeNode node, int index)
{
    int j;
    ptrTreeNode right = node->_ptrArr_children[index];
    ptrTreeNode left = node->_ptrArr_children[index - 1];

    left->_u_KeyNum++;
    left->_iarr_Keys[left->_u_KeyNum] = node->_iarr_Keys[index];
    left->_ptrArr_children[left->_u_KeyNum] = right->_ptrArr_children[0];

    for (j = 1; j <= right->_u_KeyNum; j++)
    {
        left->_u_KeyNum++;
        left->_iarr_Keys[left->_u_KeyNum] = right->_iarr_Keys[j];
        left->_ptrArr_children[left->_u_KeyNum] = right->_ptrArr_children[j];
    }

    for (j = index; j < node->_u_KeyNum; j++)
    {
        node->_iarr_Keys[j] = node->_iarr_Keys[j + 1];
        node->_ptrArr_children[j] = node->_ptrArr_children[j + 1];
    }
    node->_u_KeyNum--;
    free(right);
}

static void BTree_adjust_node(ptrTreeNode node, int index)
{
    //删除结点p中的第i个关键字后,调整B树
    if (index == 0)                      //删除的是最左边关键字
        if (node->_ptrArr_children[1]->_u_KeyNum > 1) //右结点可以借
            BTree_move_keys_left(node, 1);
        else //右兄弟不够借
            BTree_combine_keys(node, 1);
    else if (index == node->_u_KeyNum)             //删除的是最右边关键字
        if (node->_ptrArr_children[index - 1]->_u_KeyNum > 1) //左结点可以借
            BTree_move_keys_right(node, index);
        else //左结点不够借
            BTree_combine_keys(node, index);
    else if (node->_ptrArr_children[index - 1]->_u_KeyNum > 1) //删除关键字在中部且左结点够借
        BTree_move_keys_right(node, index);
    else if (node->_ptrArr_children[index + 1]->_u_KeyNum > 1) //删除关键字在中部且右结点够借
        BTree_move_keys_left(node, index + 1);
    else //删除关键字在中部且左右结点都不够借
        BTree_combine_keys(node, index);
}

static int BTree_delete_node(ptrTreeNode node, int key)
{
    int index;
    int found_tag;
    if (node == NULL)
        return 0;
    else
    {
        found_tag = FindBTNode(node, key, &index);
        if (found_tag == 1)
        {
            if (node->_ptrArr_children[index - 1] != NULL)
            {
                BTree_set_node_substitution(node, index);
                BTree_delete_node(node->_ptrArr_children[index], node->_iarr_Keys[index]);
            }
            else
                BTree_remove_node(node, index);
        }
        else
            found_tag = BTree_delete_node(node->_ptrArr_children[index], key);
        if (node->_ptrArr_children[index] != NULL)
            if (node->_ptrArr_children[index]->_u_KeyNum < 1)
                BTree_adjust_node(node, index);
        return found_tag;
    }
}

EXEC_RST BTree_delete(ptrTree pTree, int key)
{
    ptrTreeNode iter;
    int a = BTree_delete_node(*pTree, key);

    if (!a) { printf("   关键字%d不在B树中\n", key); }
    else if (!(*pTree)->_u_KeyNum)
    {
        iter = *pTree;
        *pTree = (*pTree)->_ptrArr_children[0];
        if (*pTree) { (*pTree)->_ptr_Parent = NULL; }
        free(iter);
    }

    return SUCCESS;
}
