# 广义表

> 顾名思义，广义表是线性表的推广。

# 1. 抽象数据类型广义表的定义

抽象数据类型的广义表的定义如下：

```C
ADT GList{
    数据对象：D = {ei | 1,2,···,n; n>=0; ei ∈ AtomSet 或 ei ∈GList,
             AtomSet 为某一个数据对象}
    数据关系：Rl ={<ei-1,ei>|ei-1,ei∈D，2<=i<=n }
}
```

关键就是广义表中的元素既可能为原子元素也可能为列表元素。

广义表的基本操作有:

1. ***广义表初始化，创建空的广义表L；***

```C
Init_GList(& L);
```

2. ***根据广义表的书写形式字符串S构造广义表L；***

```C
CreateGList(&L, S);
```

3. ***如果广义表存在，销毁广义表L；***

```C
DestroyGList(& L);
```

4. ***广义表的复制操作，如果广义表L存在，复制广义表L得到广义表T；***

```C
CopyGList(L);
```

5. ***求得广义表的长度，即元素个数；***

```C
GListLength(L);
```

6. ***求的广义表的深度，广义表为空的时候，深度为1；***

```C
GListDepth(L);
```

7. ***判断广义表L是否为空***；

```C
GListEmpty(L);
```

8. ***取广义表的头；***

```C
GetHead();
```

9. ***取广义表的尾；***

```C
GetTail();
```

10. ***插入元素e作为广义表L的第一元素***；

```C
InsertFirst_GL(&L, e);
```

11. ***删除广义表的第一个元素并且返回其值；***

```C
DeleteFirst_GL(&L, &e);
```

12. ***遍历广义表的每一个元素，并使用函数Visit来处理每一个元素；***

```C
Traverse_GL(L, Visit());
```

广义表一般记为：${LS = (a_{1},a_{2},\dots,a_{n})}$

其中，***n为广义表的长度***. 广义表中，${a_{i}}$可以是单个元素，也可以是广义表，分别称为广义表的***原子***和***子表***。当广义表非空的时候，称第一个元素${a_{1}}$为${LS}$广义表的***表头***，称其余元素所组成的表${(a_{2}, a_{3},a_{4}, \dots, a_{n})}$为${LS}$广义表的表尾。

> ***注意！！！！***
>
> 广义表  ${LS1 = ()}$   和广义表  ${LS2 = (())}$ 是不一样的！！！
>
> 前者为空表，长度为0，没有表头或者表尾；
>
> **后者不为空表，长度为1，其表头为第一个元素为${()}$ , 其表尾元素也为${()}$ **

# 2. 广义表的存储结构

> 广义表中的数据元素可以具有不同的结构(或是原子，或是列表)，因此难以用顺序结构表示，***我们通常使用链式存储结构，每一个数据元素可以用一个结点来表示。***

## 2.1 广义表的头尾链表存储表示

该种存储结构的想法是任何广义表都是由一个表头和表尾组成的，特殊情况即为空表，此时的广义表的表头结点指向`nullptr`；其余情况下表头结点均指向一个***表结点***，因为广义表起码是一个表嘛！然后其中的`ptr.hp`指针指向的结点类型可能为原子结点，也可能为表结点!

```C
// ---------------广义表的头尾链表存储表示-----------------
typedef enum {ATOM, LIST} ElemTag; // ATOM == 0 : 原子; LIST == 1 : 子表
typedef struct GLNode {
    ElemTag tag;				     // 公共部分，用于区分原子结点和表结点
    union { 					     // 原子结点和表结点的联合部分
        AtomType atom; 				// atom是原子结点的值域，AtomType由用户定义
        struct { struct GLNode * head_ptr, * tail_ptr; } ptr;
        // ptr是表结点的指针域，ptr.head_ptr 和ptr.tail_ptr 分别指向子表的表头和表尾
    };
} * GList; // 广义表类型
```

如果广义表为空的话，有：

```C
GList glist = nullptr;
```

如果广义表非空的话，有：

```C
GList glist = (GList )malloc (sizeof (GLNode));
glist ->tag = LIST;
glist ->head_ptr = ...;
glist ->tail_ptr = ...;
```

## 2.2 广义表的扩展线性链表存储表示

> 该种存储结构是最和我们平时学习的线性表相似的地方，该种存储结构就是真正将广义表中的元素都看成一个结点，然后使用指针将这些结点串联起来，所有的广义表看做成最大的结点！

```C
// -----------------------广义表的扩展线性链表存储表示-----------------------
typedef enum {ATOM, LIST} ElemTag; // ATOM == 0 : 原子, LIST == 1 :子表
typedef struct GLNode {
    ElemTag tag;  					// 公共部分，用于区分原子结点和表结点
    union {
        AtomType atom; 				   // 原子结点的值域
        struct GLNode * head_ptr; 		 // 原子结点的表头指针
    };
    struct GLNode * next_ptr;  			      // 相当于线性链表的next, 指向下一个元素结点
} * GList;						    // 广义表类型GList 是一种扩展的线性链表
```

如果广义表为空的话，则有：

```C
GList glist = (GList)malloc(sizeof(GLNode));
glist -> tag = 1;
glist -> head_ptr = nullptr;
glist -> next_ptr = nullptr;
```

如果广义表不为空的话，则有:

```C
GList glist = (GList)malloc(sizeof(GLNode));
glist -> tag = 1;
glist -> head_ptr = other_node;
glist -> next_ptr = nullptr;  // 每一个广义表都可以看做一个巨大的结点，该节点肯定是单独的，是没有下一个结点的!!
```

