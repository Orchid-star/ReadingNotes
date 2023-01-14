# .bashrc文件

.bashrc文件在普通用户目录（/home/xxx）或root用户目录（/root），属于隐藏文件（使用ls -al查看）。Linux系统中很多shell，包括bash，sh，zsh，dash和kron等，不管哪种shell都会有一个.bashrc的隐藏文件。它相当于**shell的配置文件**。.bashsh文件在每次打开新的终端时都会被读取并执行。这个文件主要保存一些**终端配置**和**环境变量**，例如别名alias、路径path等。

修改/root下的.bashrc文件将会应用到整个系统，属于系统级配置。建议修改用户目录下的.bashrc，此属于用户级别设置。

例如：修改每次打开终端时的路径，可在文件中添加命令：

```markd
cd /home/orchid/
```

另外：

./bash_history记录之前输入的命令

./bash_logout推出shell时执行的命令

./profile登录shell时执行的命令。一般会在.profile文件中显式调用.bashrc