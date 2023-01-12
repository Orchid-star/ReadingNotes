问题1：Ubuntu下软件安装包的常见格式有哪些？

问题2：Ubuntu下软件如何安装？

问题3：Ubuntu下软件安装的位置在哪？

问题4：Ubuntu下如何卸载



# 1 安装方式

**第一种**：App Store

通过App Store安装，或卸载



**第二种**：apt工具

在sudo下使用root权限，使用apt工具安装，例如安装gcc

```markdown
sudo apt-get install gcc
```



**第三种**：deb安装包

使用deb软件包安装。deb安装包对应windows下的exe安装程序。如：

```markdown
sudo dpkg -i xxx.deb
```





**第四种**：源码编译安装

