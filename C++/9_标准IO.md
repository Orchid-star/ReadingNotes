**标准输入输出**

- 标准输入：键盘输入数据到程序 cin
- 标准输出：程序数据输出到显示器

标准输入与标准输出即标准IO，与之对应的是文件IO



**缓冲**

标准输入与标准输出都各自有一个缓冲区。cin从缓冲区拿数据传送到程序，如果缓冲区无数据，则阻塞，等到缓冲区有数据为止。终端输入数据，按下回车后，数据则被传送到缓冲区。cout同理，数据被传送到输出缓冲区，输出缓冲区被刷新时（如调用endl）则输出到终端。



**标准输入流**

- cin.get() //一次读取一个字符
- cin.get(一个参数) //读取一个字符
- cin.get(两个参数) //可以读取字符串
- cin.getline()  //读取一行数据，不读取换行符
- cin.ignore()
- cin.peek()
- cin.pushback()

```c++
void test()
{
    char ch;
    while((ch = cin.get()) != EOF) {  //ctrl + z
        cout << ch << endl;
    }
}

void test01()
{
    int var = 0;
    while (cin >> var) {  //流直接作为判断条件，可判断流是否有效
        cout << val << endl;
    }
}
```



**标准输出流**

- cout.flush()
- cout.put()  //向缓冲区写字符
- cout.write()  //二进制流的输出
- cout.width()  //输出格式控制
- cout.fill()
- cout.setf(标记)

```c++
void test()
{
    cout << "hello world!" << endl;
    cout.put('h').put('e').put('l') << endl;
    cout.write("hello world!", strlen("hello world!"));
}
```

