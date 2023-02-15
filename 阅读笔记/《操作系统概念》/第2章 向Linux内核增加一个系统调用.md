https://blog.csdn.net/sheziqiong/article/details/125458435



https://blog.csdn.net/LYGCSDN_/article/details/124850258



https://zhuanlan.zhihu.com/p/487648323



**过程调用**

用户模式下调用一个过程（即函数调用），是通过堆栈或寄存器传递参数给被调用的过程来完成的。过程执行前，要保存当前的状态和程序计数值，再跳至被调用过程相对应的编码开始部分。

**系统调用**

对用户程序而言，系统调用和过程调用类似。Linux中，系统调用过程如下：

- 首先将**系统调用号**存储在EAX寄存器中，将**参数**存储在另一个硬件寄存器中，
- 执行一个**陷阱指令**（汇编指令）。陷阱执行时，系统调用号作为**代码指针表的索引**，从而获得系统调用的开始地址。
- 进程跳到该地址，**进程特权从**用户模式转换到内核模式，得到特权的进程就开始执行内核代码。

**相关文件**

系统调用号位置：/user/src/linux-2.x/include/asm-i386/unistd.h

（如close()对于的系统调用是_NR_close，系统调用号被定义为6）

系统调用句柄的指针列表位置：/usr/src/linux-2.x/arch/i386/kernel/entry.S的ENTRY(sys_call_table)下。

在指针列表中，sys_close被保存在entry number为6的地方，和系统调用号一致。

**新内核的构建**

- 从内核源代码构造内核二进制码

  - 获取源代码

    - 如果机器上安装了代码包，/usr/src/linux或/usr/src/linux-2.x目录下文件可用
    - 如果没有安装此代码，从Linux发行版提供商或http://www.kernel.org下载

  - 配置、编译和安装Linux二进制文件，构建内核(进入保存内核代码的目录后)的一些典型命令包括：

    - make xconfig
    - make dep
    - make baImage

  - 增加新的内核集的entry(内核集，即多个内核，机器启动时可从中加以选择)。如系统支持lilo工具，可向lilo.conf增加一个entry:

    - image=/boot/bzImage.mykernel
    - label=mukernel
    - root=/dev/hda5
    - read-only

    其中/boot/bzImage.mykernel是内核image，mykernel是新的内核相关标签。

- 用新构造的内核启动机器

**内核源代码的扩展**

通常源代码保存在/usr/src/linux-2.x/kernel目录下。

增加系统调用有两种方法：

- 增加SYSCALL到一个该目录下已经存在的**源文件**中
- 在源文件目录下生成一个**新的文件**，并修改/usr/src/linux-2.x/kernel/**Makefile**以编译过程中包括新生成的文件。

（1）系统调用源码文件

```c
//hellowworld.c
#include <linux/linkage.h>
#include <linux/kernel.h>

asmlinkage int sys_hellowworld()
{
    printk(KERN_EMERG "hellow world!");
    return 1;
}
```

该源码会生成sys_hellowworld()的系统调用。如果将此源码增加到源代码目录下已存在的文件中，所需要做的就是将sys_hellowworld()函数增加到所选择的文件中。asmlinkage指示代码是用C语言写的。printk()函数被用来打印给内核日志文件的信息，仅能从内核调用。printk()参数中指定的内核消息被记录到文件/var/log/kernel/warnings中。printk()调用的函数原型在/usr/include/linux/kernel.h中。

（2）在/usr/src/linux-2.x/include/asm-i386/unistd.h中，为__NR_hellowworld定义一个**新的系统调用号**。用户程序可以用此号来识别新增加的系统调用，同时还有保证增加——**NR_syscalls**的值，它在相同文件中，是一个常数。

（3）增加一个条目.long sys_hellowworld到.usr/src/linux-2.x/arch/i386/kernel/entry.S文件中的sys_call_tabel中，系统调用号用作该表的索引。

（4）将hellowworld.c文件增加到Makefile(如果为系统调用生成新的文件)。保存一个旧的内核二进制码镜像的备份。开始构建新的内核，并重新命名以区别未修改的内核，并向装入程序配置文件增加一个entry(如lilo.conf)。此时可以选择性的启动旧内核还是新内核。



**用户程序使用新的系统调用**

```c
#include <linux/errno.h>
#include <sys/syscall.h>
#include <linux/unistd.h>

_syscall0(int, helloworld);
main()
{
    helloworld();
}
```

- _syscall0()采用了两个参数，第一个参数定义系统调用的返回值类型，第二个参数是系统调用的名称，该名称被用来标识在执行陷阱指令前保存在硬件寄存器中的系统调用号。syscall0()的数字表示系统调用需要的参数个数。syscall0()的作用是代替完成系统调用所需的汇编代码（陷阱）。
- 用新构建的内核编译并执行程序，在内核日志文件/var/log/kernel/warnings中应该有一个”hello world"，以表明系统调用被执行。



