# Linux常用命令梳理

https://www.cnblogs.com/quchunhui/p/5286899.html

## 一 基本命令

### 1.1 立即重启

```
shutdown -r now 或 reboot
```



### 1.2 立即关机

```
shutdown -f now 或 poweroff
```



### 1.3 等待2分钟重启

```
shutdown -r 2
```



### 1.4 等待2分钟关机

```
shutdown -h 2
```



### 1.5 使用当前用户的历史命令

```
history
```

将会显示使用过的每条历史命令及其序号，可利用序号重复执行该命令

例如输入!1并回车，将会重复执行第一条历史命令



### 1.6 清除当前用户的历史命令

```
history -r
```



### 1.7 显示内核版本号

```
uname -r
```



### 1.8 清除屏幕

```
clear
```



### 1.9 显示操作系统时钟

```
date
```



### 1.10 加载光盘到/media

```
mount /dev/cdrom/ /media
```



### 1.11 卸载光盘

```
umount /dev/cdrom 或 umount /media
```



### 1.12 查看存储设备

```
fdisk -l
```



### 1.13 加载U盘到/media

```
mount /dev/sdb1 /media
```



### 1.14 卸载U盘

```
umount /dev/sdb1 或 umount /media
```



### 1.15 中断shell命令

```
Ctrl + C
```



## 二 文件目录操作命令

### 2.1 显示当前的绝对路径

```
pwd
```



### 2.2 改变当前目录

```
cd /etc/yum
```



### 2.3 回到当前目录的父目录

```
cd ..
```



### 2.4 创建目录

```
mkdir /usr/tigger
```



### 2.5 删除目录

```
rmdir /usr/bigger
```

待删除目录必须为空



### 2.6 列出目录中的内容

```
ls /
```



### 2.7 列出目录中的所有内容（包括隐藏文件或点文件）

```
ls /root -a
```



### 2.8 用长格式列出目录中的内容

```
ls /boot -l
```



### 2.9 创建空文件

```
touch /a.dat
```



### 2.10 复制文件

```
cp /etc/host/conf /boot
```



### 2.11 复制整个子目录（不改变目录名）

```
cp -r /usr/include /root
将整个子目录/usr/include（不改变目录名）复制到目录/root中
```



### 2.12 复制整个子目录（改变目录名）

```
cp -r /usr/include /root/include2
```



### 2.13 移动文件或给文件改名

```
mv /root/host.conf /root/myfile
```



### 2.14 删除文件

```
rm /root/myfile2  需要y键确认
rm -f /a.dat
```



### 2.15 删除非空目录

```
系统提示非空：rmdir /root/mysub
系统无错误提示：rm -rf /root/mysub
```



### 2.16 分屏显示文件内容

```
more /etc/services
按空格键显示下一屏，按q键返回命令行状态
```



### 2.17 显示文件内容

```
more filename一次一屏的显示内容，空格或回车显示下一屏
less filename 一次一屏的显示内容，空格或回车显示下一屏
cat filename 一次显示全部内容
cat file1 file2 > file3 将file1和file2的内容写到file3，并覆盖file3原有的内容
cat file >> file2 将file的内容追加到file2,file2原内容不变
head file  只显示文件的前10行
head -n file 显示文件的前n行
tail file只显示文件的后10行
tail -n file 显示文件的后n行
nl file以文件编号的形式一次全部显示文件内容，忽略空格
```



### 2.18 合并文件

```
cat /etc/resolv.conf /etc/yum.conf > /b.dat
>和>>是重定向，>会覆盖，>>会追加
```



### 2.19 文件查找

```
find [路径] [选项]
```



### 2.20 文件内容查找

```
grep
```

