#include "node.h"

#include <stdlib.h>

ptrQueueNode QueueNode_create(ptrTreeNode data)
{
    // 申请内存
	ptrQueueNode new_node = (ptrQueueNode)malloc(sizeof(QueueNode));

    // 如果申请成功，那么就对其中的值进行设置
	if (new_node)
	{
		new_node->_ptrTNode_data = data;
		new_node->_ptrQNode_next = NULL;
	}

	return new_node;
}
