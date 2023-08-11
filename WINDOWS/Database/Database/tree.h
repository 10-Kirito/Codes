#ifndef _TREE_
#define _TREE_

#include "global.h"
#include "node.h"

#include <stddef.h>

/*
 * ��Ƶ�B���ļ����±�1��ʼ��ţ����Ƕ��ڸ����ļ����±�index
 * �����ӵ��±�Ϊindex - 1�����Һ��ӵ��±�Ϊindex
 */
typedef TreeNode* Tree;     // ����������
typedef TreeNode** ptrTree; // ��ָ�룬����е�ʱ����Ҫ�����ĸ��ڵ���иĶ����ͻ�ʹ���������

// ��¼B���������
// ����ҵ��˽ڵ㣬��ô���صľ��ǽڵ㱾��
// ���û���ҵ��ڵ㣬���ص���Ӧ�ò���Ľڵ�
typedef struct BTreeSearch
{
	ptrTreeNode _ptrNode_node;	// ��¼�����������һ���ڵ�
	size_t _u_keyIndex;			// ��¼�����±�
	EXEC_RST _exec_flag;		// ��¼�����Ľ��
} BTreeSearch;

// ��ʼ��
EXEC_RST BTree_create(ptrTree pTree);
// ��������key��ӵ�pTree�еĽڵ�node���±�index��
// �ڵ��ñ�����֮ǰ��Ҫ�ȵ���BTree_search��������ȡpTree��index
EXEC_RST BTree_insert(ptrTree pTree, ptrTreeNode node, size_t index, int key);
// ɾ��ɾ��pTree�еļ�key
EXEC_RST BTree_delete(ptrTree pTree, int key);
// �飺��tree��������key�����������������result��
// �������ʧ�ܣ���ôresult�е�_exec_flagλ�ᱻ����ΪFAIL
//      _ptrNode_node��ָ��Ҫ����Ľڵ�
//      _u_keyIndex��ָ��Ҫ������±�
// ��������ɹ���_exec_flag�ᱻ����ΪSUCCESS
//      _ptrNode_node��ָ������ڵĽڵ�
//      _u_keyIndex��ָ�������ڵ��±�
EXEC_RST BTree_search(Tree tree, int key, BTreeSearch* result);
// �ͷſռ�
EXEC_RST Btree_free(ptrTree pTree);
// ��ӡ�����߼�Ϊ�㼶����
EXEC_RST BTree_print(Tree tree);

#endif
