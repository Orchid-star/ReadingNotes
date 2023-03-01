**问题引入**

在查看全局的.gitconfig文件时，发现经常使用的代码推送指令alias review的实现比较复杂：


```shell
review = "!f() { if [ -z $1 ];then currBra=`git symbolic-ref -q --short HEAD`;else currBra=$1;fi;git push origin HEAD:refs/for/$currBra; }; f"
```

以下简要分析一下。



**分析**

该语句中，*f*(){    }是一个shell函数。函数前的“!”是git标注将该函数作为git命令。花括号内是函数的实现。最后的*f*是对该函数的调用，完成相应的操作。

首先函数体花括号内必须以空格开始，并以空格结尾。if [ -z \$1]表示对条件进行判断，-z表示对后面的字符进行判空，如果\$1为空这条件为真，执行后面的then语句，否则执行后面的else语句。\$1表示命令行参数的第1个参数。**fi**表示if语句结束。

then分支中，git symbolic-ref -q --short HEAD表示获取当前分支名。该指令解释如下（具体解释见[Git - git-symbolic-ref Documentation (git-scm.com)](https://git-scm.com/docs/git-symbolic-ref)）：

- git symbolic-ref -q --short指令是查看对象引用。-q表示如果命令执行异常，不报错。--short表示需要的是简要信息。
- HEAD是当前.git文件夹内的一个文件，记录了当前所在分支，如ref: refs/heads/master表面当前在master分支。一般将HEAD称为引用或指针，这里HEAD就是对refs/heads/master的引用。而refs/heads/master是master分支最后一个commiter对象的引用。
- HEAD作为git symbolic-ref -q --short的参数，会返回分支名称。例如HEAD指向refs/heads/master，则返回master，也就是当前分支的名称。

这里的if语句实际上是获取要推送的远程目标分支，并将其存储在currBra变量中。

if语句完成后，紧接着是git push origin HEAD:refs/for/$currBra语句。该语句分析如下：

- 该命令的原型是git push [远程主机名] **commiter引用**：refs/for/[远程分支名]
- HEAD指向的是当前的分支commiter对象。该指令是将HEAD指向的分支的commiter对象推送到远程（需要review）。这会将当前分支上所有的未推送到远程的本地提交推送到远程分支。
- 如果只希望推送本地部分提交，如希望推送HEAD之前的提交，但不提交HEAD，将此命令的HEAD替换为HEAD^即可。其他以此类推。

最后的f即是对该函数的调用。



**扩展**

如果本地有多笔提交，要保留最近几笔不提交，只提交最早的一笔或多笔修改，可以参考上述指令编写如下指令：

```shell
[alias]
pushs = "!f() { if [ -z $1 ];then SHA=HEAD;else SHA=$1;fi;if [ -z $2 ];then currBra=`git symbolic-ref -q --short HEAD`;else currBra=$2;fi;git push origin $SHA:refs/for/$currBra; }; f"
```