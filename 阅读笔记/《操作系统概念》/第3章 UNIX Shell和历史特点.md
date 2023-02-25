https://www.cnblogs.com/xuesu/p/4382625.html



# 项目： UNIX Shell和历史特点

**shell**

shell用于接收用户命令并在单独的进程执行每个命令。



**shell的简单实现**

父进程首先读取用户命令行的输入（如ls -a)，然后创建一个独立的子进程来完成这个命令。父进程默认等待子进程退出，若允许子进程后台执行，在命令后加&即可，如cat prog.c &



**简单shell**

shell的主进程包含两个函数，分别是main和setup函数。main中存在一个while(1)循环，循环内，依次调用setup然后创建子进程。setup负责填充命令的参数向量。如果接收到Ctrl D，setup则调用exit 终止程序。



**shell和终端模拟器差别**

我们平时打开的黑漆漆的输入命令行的窗口叫做终端模拟器，主要负责输入输出。终端模拟器内输入一条命令后，会创建一个子进程运行shell，shell内部会分析命令参数，并再创建自己的一个子进程运行对应的命令。执行Ctrl D时，shell进程内的setup函数会调用exit退出shell，shell创建的子进程也会同时终止。

