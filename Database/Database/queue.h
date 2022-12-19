#ifndef _QUEUE_
#define _QUEUE_

#include "global.h"
#include "node.h"

typedef QueueNode* Queue;       // �����������
typedef QueueNode** ptrQueue;   // ����ָ�룬���Ҫ�Զ����ײ����д�����Ҫ�������

// �������У�������pQueueָ�򴴽��õĶ���
// ע�⣬���еĵ�һ���ڵ�Ϊͷ��㣬���洢����
EXEC_RST Queue_init(ptrQueue pQueue);

// ��ӣ���pNode���뵽����queue
EXEC_RST Queue_enqueue(Queue queue, ptrTreeNode pNode);

// ���ӣ������ӵĽڵ�ŵ�pptrNode_returnָ����ڴ�
// �������ʧ�ܣ�����FAIL�����򷵻�SUCCESS
EXEC_RST Queue_dequeue(Queue queue, ptrTreeNode* pptrNode_return);

// �����Ƿ�Ϊ��
BOOL Queue_isEmpty(Queue queue);

// �ͷŶ��пռ�
EXEC_RST Queue_free(Queue queue);

#endif
