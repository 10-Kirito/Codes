#ifndef __GEN_NODE_H__
#define __GEN_NODE_H__

#ifndef __REF_GEN_LIST_NODE_TYPE__
#define __REF_GEN_LIST_NODE_TYPE__
enum GenListNodeType { HEAD, ATOM, LIST };
#endif

// 广义表结点类
template <class ElemType> struct GenListNode {
  // 数据成员:
  GenListNodeType tag;
  // 标志域,HEAD(0):头结点, ATOM(1):原子结构, LIST(2):表结点
  GenListNode<ElemType> *tLink; // 指向同一层中的下一个结点指针域
  union // 每一个结点都会有一个tag标记，这个标记是为了区分广义表所存储的不同类型的数据，还有一个就是next指针，就是tLink，他存储的是下一个结点的
        // 位置，每一个结点可能不会有的是union里面的内容，里面三个成员变量只会存在一个的，根据用户所定义的不同的成员变量，而存在不一样的变量
  {
    int ref;                      // tag=HEAD,头结点,存放引用数
    ElemType atom;                // tag=ATOM,存放原子结点的数据域
    GenListNode<ElemType> *hLink; // tag=LIST,存放指向子表的指针域
  }; // uniom该联合体内部的成员公用一片储存区域，当我们定义其中一个成员变量的时候，其他成员变量就默认不能用啦
  // 构造函数:
  GenListNode(GenListNodeType tg = HEAD, GenListNode<ElemType> *next = nullptr);
  // 由标志tg和指针next构造广义表结点，默认构造函数肯定是默认构造一个空的广义表就是一个空的链表，传入HEAD是想创建一个头结点
};

// 广义表结点类的实现部分
template <class ElemType>
GenListNode<ElemType>::GenListNode(GenListNodeType tg,
                                   GenListNode<ElemType> *next)
// 操作结果：由标志tg和指针next构造广义表结点
{
  tag = tg;     // 标志
  tLink = next; // 后继
}

#endif
