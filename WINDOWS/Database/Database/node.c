#include "node.h"

#include <stdlib.h>

ptrQueueNode QueueNode_create(ptrTreeNode data)
{
    // �����ڴ�
	ptrQueueNode new_node = (ptrQueueNode)malloc(sizeof(QueueNode));

    // �������ɹ�����ô�Ͷ����е�ֵ��������
	if (new_node)
	{
		new_node->_ptrTNode_data = data;
		new_node->_ptrQNode_next = NULL;
	}

	return new_node;
}
