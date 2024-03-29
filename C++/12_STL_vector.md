**vector**

动态数组，或称可变数组



**vector特点**

- 连续存储，可通过下标进行随机访问
- 是一种单口容器，建议使用push_back()和pop_back()进行操作。虽然提供有insert操作，但是insert会导致插入位置开始的所有元素进行移动，效率低
- vector容量可根据需要动态增长，为了提高效率，在已知所需空间大小的基础上，可在初始进行reserve设定capacity
- vector的首元素地址不是vector的地址。加入有vector v，vector的指针是&v，首元素的地址是&(v[0])（注意vector是一个类对象）。
- vector添加元素时若容量不够会动态增长容量，但是删除元素，容量不会自动减少



**vector动态增长**

当插入新元素的时候，如果空间不足，那么vector会重新申请更大的一块内存空间，将原空间数据拷贝到新空间，释放旧空间的数据，再把新元素插入新申请空间。



**巧用swap收缩vector空间**

如果一个vector很大，resize操作不会改变capacity的大小，只会改变size的大小。如果capacity过大，size较小，可通过以下方式进行空间收缩：

```c++
vector<int>(v).swap(v);
```

收缩原理是两个vector执行swap交换数据时，实际上内部只是相互改变了指针指向，没有数据拷贝操作。使用v实例化新的容器，新的容器的capacity是v的size，所以空间变小了。



**reserv和resize的区别**

reserv是容器预留空间，但在空间内不真正创建元素对象，所以在没有添加新的对象之前，不能引用容器内的元素。在大概知道数据量时，使用reserv预留空间可增加程序效率。

resize是改变容器的大小，且在创建对象，因此，调用该函数后，就可以引用容器内的对象了



**vector的下标访问与at访问的区别**

- 下标访问越界程序会报错，at访问越界程序会抛出异常
- 下标访问和at访问，返回的都是对应位置元素的引用