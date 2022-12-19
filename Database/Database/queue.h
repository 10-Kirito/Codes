#ifndef _QUEUE_
#define _QUEUE_

#include "global.h"
#include "node.h"

typedef QueueNode* Queue;       // 定义队列类型
typedef QueueNode** ptrQueue;   // 队列指针，如果要对队列首部进行处理，需要这个类型

// 创建队列，结束后pQueue指向创建好的队列
// 注意，队列的第一个节点为头结点，不存储数据
EXEC_RST Queue_init(ptrQueue pQueue);

// 入队，将pNode插入到队列queue
EXEC_RST Queue_enqueue(Queue queue, ptrTreeNode pNode);

// 出队，将出队的节点放到pptrNode_return指向的内存
// 如果出队失败，返回FAIL，否则返回SUCCESS
EXEC_RST Queue_dequeue(Queue queue, ptrTreeNode* pptrNode_return);

// 队列是否为空
BOOL Queue_isEmpty(Queue queue);

// 释放队列空间
EXEC_RST Queue_free(Queue queue);

#endif
