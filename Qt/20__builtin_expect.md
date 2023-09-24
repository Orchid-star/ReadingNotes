# __builtin_expect

**一、问题引入**：

看下面一段程序：

```c++
#define QWIDGETSIZE_MAX (16777215)

void set_size(qint32 width, qint32 height)
{
    int mw = width;
    int mh = height;
    
    if (width > QWIDGETSIZE_MAX || height > QWIDGETSIZE_MAX) {  //条件跳转1
        mw = qMin<int>(minw, QWIDGETSIZE_MAX);
        mh = qMin<int>(minh, QWIDGETSIZE_MAX);
    }
    if (mw < 0 || mh < 0) { //条件跳转2
        mw = qMax(mw, 0);
        mh = qMax(mh, 0);
    } 
    setSize(mw, mh);
}
```

分析：这是一段设置窗口尺寸的示例程序。两个条件跳转语句1和2分别将预设置的宽高进行了有效性检查，若不在合理范围0-16777215内，就进行修正，最后使用修正值设置窗口的尺寸。

**1.1 场景的特殊性**

一般用户在调用这个接口时，使用的参数都是合法的，也就是说，绝大多数情况下，上述程序在执行条件跳转1和2时，判断完if语句内的条件后不会进入if对应的语句块。

**1.2 CPU的流水线设计**

一条指令的生命周期分为5个阶段（stage)，依次是***取指、译码、执行、访存、写回***。

- 取指：指将指令从存储器中读取出来的过程
- 译码：存储器中取出的指令进行翻译的过程，经过译码之后得到指令需要的操作数寄存器索引
- 执行：最常见的算术逻辑部件运算器（ Arithmetic Logical Unit, ALU)，进行真正运算的过程
- 访存：指存储器访问指令将数据从存储器中读出，或者写入存储器的过程
- 写回：指将指令执行的结果写回通用寄存器组的过程

CPU的流水线设计下，一条指令处于生命周期五个阶段内的执行阶段时，该条指令的下一条指令在已经完成了取指，正在进行译码，下下条正在进行取指。

**1.3 看程序的一点小小的效率问题**

根据上述的CPU流水线设计相关的描述，程序在执行第8行的条件跳转指令时，第9行指令已经完成了取指，正在进行译码，第10行指令正在进行取址。但是因为场景的特殊性，执行完第8行的跳转指令，会跳转到第12行处的指令，而已经进入生命周期的第9行和第10行指令并不需要执行。这样就需要重新开始对第12行的代码进行取指、译码、执行等过程，导致效率下降。

对此，gcc引入了__builtin_expect宏。



**二、__builtin_expect**

Qt使用__builtin_expect定义了两个宏：

```c++
#  define Q_LIKELY(expr)    __builtin_expect(!!(expr), true)
#  define Q_UNLIKELY(expr)  __builtin_expect(!!(expr), false)
```

__builtin_expect是GCC(version>=2.9)引进的宏，其作用就是帮助编译器判断条件跳转的预期值，避免跳转造成时间浪费。

`__builtin_expect(!!(expr), value)`的意思是exptr的值预期的value，或者说exptr的值在大多数情况下是value。在条件跳转语句中使用时，编译器获得了判断条件的预期值，然后根据预期值设定该指令的下一条指令是什么。

对上面的程序修改如下：

```c++
#define QWIDGETSIZE_MAX (16777215)

void set_size(qint32 width, qint32 height)
{
    int mw = width;
    int mh = height;
    
    if (Q_UNLIKELY(width > QWIDGETSIZE_MAX || height > QWIDGETSIZE_MAX)) {  //条件跳转1
        mw = qMin<int>(minw, QWIDGETSIZE_MAX);
        mh = qMin<int>(minh, QWIDGETSIZE_MAX);
    }
    if (Q_UNLIKELY(mw < 0 || mh < 0)) { //条件跳转2
        mw = qMax(mw, 0);
        mh = qMax(mh, 0);
    } 
    setSize(mw, mh);
}
```

在执行第8行跳转指令1时时，第12行指令已经完成取指，正在译码。因为大多数情况下（前面讲的情况的特殊性）第8行语句执行后就会跳转到第12行，这样第12行已经完成了取指、译码，就可以直接执行了。



**总结：__builtin_expect只是一种编译优化，不影响程序的执行逻辑。**

