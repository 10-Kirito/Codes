# DATA_STRUCTURES_ALGORITHMS # 1. LINEAR_TABLE(线性表) > 该部分讲述的是关于线性表的一些内容：
>
> - 顺序存储；
>   - ***顺序表的实现（√）；***
> - 链式存储；
>   - 单链表；
>   - 双链表；
>   - 循环链表；
>   - 静态链表（借助于数组实现）
>
> | 线性表的分类 |                   |      |
> | ------------ | ----------------- | ---- |
> | 顺序存储：   | 1. 顺序表的实现   | √    |
> |              |                   |      |
> | 链式存储：   | ***1. 单链表***   |      |
> |              | ***2. 双链表***   |      |
> |              | ***3. 循环链表*** |      |
> |              | ***4. 静态链表*** |      |

## 1.1 线性表的顺序表示

> 按照王道数据结构所写！

[LINEAR_TABLE](LINEAR_TABLE/sequence_list.h)  （顺序表的实现）

## 1.2 双向链表

> 来自: https://github.com/mandliya/algorithms_and_data_structures/blob/master/include/list.h

[LINEAR_TABLE_EXAMPLE](LINEAR_TABLE_EXAMPLE/list.h) 

这一份代码实现的是一个双向链表，其实现方法很值得学习！



# 2. STACK(栈的应用)

## 2.1 数进制的转换

[number_conversion](STACK/number_conversion.cpp)  

## 2.2 中缀表达式转化为后缀表达式

[infix_to_postfix](STACK/infix_to_postfix.cpp)

## 2.3 后缀表达式的计算

[postfixexpression_evaluation](STACK/postfixexpression_evaluation.cpp)

## 2.4 中缀表达式的计算

[infixexpression_evaluation](STACK/infixexpression_evaluation.cpp)

# 3. ARRAYS_MATRIX(数组和一些特殊的矩阵)

## 3.1 稀疏矩阵的

### 3.1.1 顺序存储(三元组)



### 3.1.2 十字链表法



# 4. GENERALIZED_LIST(广义表)

> 广义表(Generalized List)，线性表的推广，广义表允许一个元素既可以是单个数据项，也可以是表。

## 4.1 广义表的基本定义

### 4.1.1 广义表的表头和表尾

当广义表不是空表的时候，称***第一个数据项（注意该数据项既可能为原子，也可能为子表）***为表头，剩下的数据构成***新的广义表（注意，这里是新的广义表，并不是单独的一个元素）***为表尾。

> *示例*：
>
> - A = ();
> - B = (A);
> - C = (a, A);
> - D = (C, a, b, c);
>
> A为空表，**所以说我们不需要去考虑表的表头或者表尾**；
>
> B表不为空表，`head(B) = A`, 注意A是一个元素项，只不过该元素为一个表。`tail(B) = ()`,显然出去表头元素之后B表为空，但是仍然是表尾；
>
> `head(C) = a`, `tail(C) = (A)`;
>
> `head(D) = C`, `tail(D) = (a,b,c)`;
>
> ***ps:***关键是需要我们去注意表头是广义表中的一个元素，而表尾是除去表头元素生成的另外的一个广义表。

### 4.1.2 广义表的深度

广义表中括号的重数即为广义表的深度，空表的深度为1.

## 4.2 广义表的存储结构

> 广义表的实现是采用链式存储，简称广义链表。



