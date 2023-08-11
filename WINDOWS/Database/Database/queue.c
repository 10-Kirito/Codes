#include "queue.h"
#include "global.h"
#include "node.h"

#include <assert.h>
#include <stdlib.h>

EXEC_RST Queue_enqueue(Queue queue, ptrTreeNode ptrNode)
{
	// 如果队列没有被初始化，那么直接返回
	if (!queue) { return FAIL; }

	// 找到队列尾
	while (queue->_ptrQNode_next) { queue = queue->_ptrQNode_next; }
	// 插入元素
	queue->_ptrQNode_next = QueueNode_create(ptrNode);

	return SUCCESS;
}

EXEC_RST Queue_dequeue(Queue queue, ptrTreeNode *pptrNode_return)
{
	// 如果队列没有初始化，或者队列为空，直接返回
	if (!queue || !(queue->_ptrQNode_next)) { return FAIL; }

	// 队列的第一个节点是头结点，不存数据，因此直接找到队列的头结点之后的一个节点
	// 这个节点就是我们要返回的数据节点
	ptrQueueNode to_return = queue->_ptrQNode_next;
	queue->_ptrQNode_next = to_return->_ptrQNode_next;
	// 存入
	*pptrNode_return = to_return->_ptrTNode_data;
	// 释放空间
	free(to_return);

	return SUCCESS;
}

BOOL Queue_isEmpty(Queue queue)
{
	// 首先确保队列是有效的
	assert(queue);

	if (queue->_ptrQNode_next) { return FALSE; }
	return TRUE;
}

EXEC_RST Queue_init(ptrQueue pQueue)
{
	// 申请空间
	*pQueue = (ptrQueueNode)malloc(sizeof(QueueNode));
	// 检查是否申请成功
	assert(*pQueue);
	// 设置第一个数据为空
	(*pQueue)->_ptrQNode_next = NULL;

	return SUCCESS;
}

EXEC_RST Queue_free(Queue queue)
{
	// 指向前一个，用于释放
	ptrQueueNode prev;

	// 当队列非空
	while (queue)
	{
		// 记录第一个节点
		prev = queue;
		// queue切换到下一个
		queue = queue->_ptrQNode_next;
		// 释放资源
		free(prev);
	}

	return SUCCESS;
}
