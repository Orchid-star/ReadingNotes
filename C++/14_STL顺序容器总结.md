**容器分类**

- 顺序容器  即线性表，按照顺序存储的有vector，deque，array，string；按照链式存储的有list，forward_list。
- 关联容器 由关键字决定元素存储位置的容器。



**顺序容器**

**特点**

采用顺序存储的线性表内存连续，因此支持快速随机访问，作为代价，插入元素可能非常耗时。

采用链式存储的线性表内存不连续，因此只支持顺序访问，但插入或删除元素会很高效。链式存储的另一个缺点是存储效率不如线性存储高。

*顺序存储结构*

- vector 可变大小数组，尾部插入很快
- deque 双端队列，头尾插入很快
- array 固定大小数组，无法增删元素
- string 只能存储字符的vector

*链式存储结构*

- list 双向链表
- forward_list 单向链表

**构造**

- 默认C c
- 拷贝C c1(c2)或C c1=c2
- 列表初始化C c{a,b,c,...}或C c={a,b,c,...}
- 指定大小 C c(size, value)

**迭代器**

- begin end
- cbegin cend
- rbegin rend
- crbegin crend

**assign**

分配内存，指定大小

**swap**

交换内部数据结构，很快速

**大小操作**

size()、max_size()、empty()

resize()

**容器操作可能使迭代器失效**

由于添加或删除元素可能会使迭代器失效，因此必须保证每次改变容器的操作之后都能正确地重新定位迭代器。

**string的搜索**

- s.find(args) 查找s中args第一次出现的位置
- s.rfind(args) 查找s中args最后一次出现的位置

搜索成功返回下标，搜索失败返回string::npos，即-1

**string的compare函数**

字符串大小比较



**容器适配器**

适配器（adapter)是一种机制，能使某种事物的行为看起来像另外一种事物一样。

标准库三个顺序容器适配器：

- stack 默认基于deque实现
- queue  默认基于deque实现
- priority_queue 默认基于vector实现





