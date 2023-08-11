#include "queue.h"
#include "global.h"
#include "node.h"

#include <assert.h>
#include <stdlib.h>

EXEC_RST Queue_enqueue(Queue queue, ptrTreeNode ptrNode)
{
	// �������û�б���ʼ������ôֱ�ӷ���
	if (!queue) { return FAIL; }

	// �ҵ�����β
	while (queue->_ptrQNode_next) { queue = queue->_ptrQNode_next; }
	// ����Ԫ��
	queue->_ptrQNode_next = QueueNode_create(ptrNode);

	return SUCCESS;
}

EXEC_RST Queue_dequeue(Queue queue, ptrTreeNode *pptrNode_return)
{
	// �������û�г�ʼ�������߶���Ϊ�գ�ֱ�ӷ���
	if (!queue || !(queue->_ptrQNode_next)) { return FAIL; }

	// ���еĵ�һ���ڵ���ͷ��㣬�������ݣ����ֱ���ҵ����е�ͷ���֮���һ���ڵ�
	// ����ڵ��������Ҫ���ص����ݽڵ�
	ptrQueueNode to_return = queue->_ptrQNode_next;
	queue->_ptrQNode_next = to_return->_ptrQNode_next;
	// ����
	*pptrNode_return = to_return->_ptrTNode_data;
	// �ͷſռ�
	free(to_return);

	return SUCCESS;
}

BOOL Queue_isEmpty(Queue queue)
{
	// ����ȷ����������Ч��
	assert(queue);

	if (queue->_ptrQNode_next) { return FALSE; }
	return TRUE;
}

EXEC_RST Queue_init(ptrQueue pQueue)
{
	// ����ռ�
	*pQueue = (ptrQueueNode)malloc(sizeof(QueueNode));
	// ����Ƿ�����ɹ�
	assert(*pQueue);
	// ���õ�һ������Ϊ��
	(*pQueue)->_ptrQNode_next = NULL;

	return SUCCESS;
}

EXEC_RST Queue_free(Queue queue)
{
	// ָ��ǰһ���������ͷ�
	ptrQueueNode prev;

	// �����зǿ�
	while (queue)
	{
		// ��¼��һ���ڵ�
		prev = queue;
		// queue�л�����һ��
		queue = queue->_ptrQNode_next;
		// �ͷ���Դ
		free(prev);
	}

	return SUCCESS;
}
