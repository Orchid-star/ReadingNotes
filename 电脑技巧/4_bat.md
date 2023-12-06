# Windows DOS命令

## 1 算术运算

```shell
@echo off
set /a value = 1+2
echo value
```



## 2 重定向

重定向：将命令的执行结果移交给下一条命令，或保存到某个具体的文件当中。

- `>`    `<`覆盖原有的内容
- `>>`  `<<` 追加内容

```powershell
@echo off
echo "hello world" >> a.txt
```



## 3 查看文件内容

```powershell
type a.txt
```



## 4 逻辑判断

- `<  >`  小于、大于



## 5 多命令运算

同时执行多条命令：

- `&&`   具有短路效果，第一条命令错误不会执行第二条命令
- `||`

```powershell
aaaa && ipconfig  ::aaaa错误，ipconfig也不会执行
ipconfig && net user
aaaa || ipconfig  ::ipconfig可运行
```



## 6 管道符号

- `|`  命令A和B，则`A | B`表示A的输出结果作为B的输入

```powershell
dir | find ".txt"

netstat -an | find "ESTABLISHED"
```

