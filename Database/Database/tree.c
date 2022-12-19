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

// �ڽڵ�node�в���key
// ��������ҵ�����ô�������±�
// ���򷵻ؼ��Ŀ��Ա�����ĺ����±�
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
    // ��־λ����¼�Ƿ��ҵ��˼�
	BOOL is_found= FALSE;
	size_t index;

    // ����û�б�������Ҷ�ڵ㣬����û���ҵ������ͼ���Ѱ��
	while (cur != NULL && !is_found)
	{
        // ���"�����±�"
		index = BTree_search_node(cur, key);
        // ����ҵ��˼����±꣬ѭ������
		if (index > 0 && cur->_iarr_Keys[index] == key)
		{
			is_found = TRUE;
		}
        // ����������һ������Ѱ��
		else
		{
            // ��¼��ǰ���Ľڵ㣬�Է�û���ҵ�
			prev = cur;
            // �����Ӧ������
			cur = cur->_ptrArr_children[index];
		}
	}

    // �����Ƿ��ҵ������н����ֵ
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

// ����һ���µĽ�㣬����ڵ㽫��Ϊ�����¸�
// ��key��Ϊ�½ڵ�ļ�����ori_node��Ϊ��������new_node��Ϊ������
static void BTree_newRoot(ptrTree pTree, int key, ptrTreeNode ori_node, ptrTreeNode new_node)
{
    // ����ռ�ͳ�ʼ��
	*pTree = (Tree)malloc(sizeof(TreeNode));
	(*pTree)->_u_KeyNum = 1;
	(*pTree)->_ptrArr_children[0] = ori_node;
	(*pTree)->_ptrArr_children[1] = new_node;
	(*pTree)->_iarr_Keys[1] = key;
	(*pTree)->_ptr_Parent = NULL;

    // �����ӽڵ�ĸ��ڵ�
	if (ori_node) { ori_node->_ptr_Parent = *pTree; }
	if (new_node) { new_node->_ptr_Parent = *pTree; }
}

// �ڽڵ�pNode���±�index�������key������to_insert
static void BTree_insert_node(ptrTreeNode pNode, size_t index, int key, ptrTreeNode to_insert)
{
    // ѭ������
	int i;
    // ���±�index���Ժ�����������һ��λ��
	for (i = pNode->_u_KeyNum; i > index; i--)
	{
		pNode->_iarr_Keys[i + 1] = pNode->_iarr_Keys[i];
		pNode->_ptrArr_children[i + 1] = pNode->_ptrArr_children[i];
	}

    // ��key���뵽��Ӧ��λ��
	pNode->_iarr_Keys[index + 1] = key;
    // ���������뵽��Ӧ��λ��
	pNode->_ptrArr_children[index + 1] = to_insert;
    // ���½ڵ�ļ���
	pNode->_u_KeyNum++;

    // �����������ڵ�
	if (to_insert) { to_insert->_ptr_Parent = pNode; }
}

// ���ѽڵ�ori_node������벿�ַ���new_node
static void BTree_split_node(ptrTreeNode ori_node, ptrTreeNode* new_node)
{
	int index;
	int split_index = 2;

    // �����ڴ�
	*new_node = (ptrTreeNode)malloc(sizeof(TreeNode));
    // ��������
	(*new_node)->_ptrArr_children[0] = ori_node->_ptrArr_children[split_index];
    // �����
	for (index = split_index + 1; index <= 3; index ++)
	{
		(*new_node)->_iarr_Keys[index - split_index] = ori_node->_iarr_Keys[index];
		(*new_node)->_ptrArr_children[index - split_index] = ori_node->_ptrArr_children[index];
	}
	(*new_node)->_u_KeyNum = ori_node->_u_KeyNum - split_index;
	(*new_node)->_ptr_Parent = ori_node->_ptr_Parent;
    // ���������ĸ��ڵ�
	for (index = 0; index <= ori_node->_u_KeyNum - split_index; index++)
	{
		if ((*new_node)->_ptrArr_children[index])
		{
			(*new_node)->_ptrArr_children[index]->_ptr_Parent = (*new_node);
		}
	}

    // ����Դ�ڵ�ļ�����
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
	if (!tree) { printf("\tB��Ϊ����\n"); return SUCCESS; }

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
    /*��˫�׽��p�е����һ���ؼ��������ҽ��q��
    ������left�е����һ���ؼ�������˫�׽��p��*/
    int iter;
    ptrTreeNode right = node->_ptrArr_children[index];
    ptrTreeNode left = node->_ptrArr_children[index - 1];

    for (iter = right->_u_KeyNum; iter > 0; iter--)
    { //�����ֵ�q�����йؼ�������ƶ�һλ
        right->_iarr_Keys[iter + 1] = right->_iarr_Keys[iter];
        right->_ptrArr_children[iter + 1] = right->_ptrArr_children[iter];
    }

    right->_ptrArr_children[1] = right->_ptrArr_children[0]; //��˫�׽��p�ƶ��ؼ��ֵ����ֵ�q��
    right->_iarr_Keys[1] = node->_iarr_Keys[index];
    right->_u_KeyNum++;

    node->_iarr_Keys[index] = left->_iarr_Keys[left->_u_KeyNum]; //�����ֵ�left�����һ���ؼ����ƶ���˫�׽��p��
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
    //ɾ�����p�еĵ�i���ؼ��ֺ�,����B��
    if (index == 0)                      //ɾ����������߹ؼ���
        if (node->_ptrArr_children[1]->_u_KeyNum > 1) //�ҽ����Խ�
            BTree_move_keys_left(node, 1);
        else //���ֵܲ�����
            BTree_combine_keys(node, 1);
    else if (index == node->_u_KeyNum)             //ɾ���������ұ߹ؼ���
        if (node->_ptrArr_children[index - 1]->_u_KeyNum > 1) //������Խ�
            BTree_move_keys_right(node, index);
        else //���㲻����
            BTree_combine_keys(node, index);
    else if (node->_ptrArr_children[index - 1]->_u_KeyNum > 1) //ɾ���ؼ������в������㹻��
        BTree_move_keys_right(node, index);
    else if (node->_ptrArr_children[index + 1]->_u_KeyNum > 1) //ɾ���ؼ������в����ҽ�㹻��
        BTree_move_keys_left(node, index + 1);
    else //ɾ���ؼ������в������ҽ�㶼������
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

    if (!a) { printf("   �ؼ���%d����B����\n", key); }
    else if (!(*pTree)->_u_KeyNum)
    {
        iter = *pTree;
        *pTree = (*pTree)->_ptrArr_children[0];
        if (*pTree) { (*pTree)->_ptr_Parent = NULL; }
        free(iter);
    }

    return SUCCESS;
}
