# 1 Stream Class

**I（读） / O（写）**

```c++
using istream       = basic_istream<char, char_traits<char>>;
using ostream       = basic_ostream<char, char_traits<char>>;
```



## 1.1 全局的Stream对象

- cin / wcin，istream的实例化，标准输入通道，对应C的stdin，与键盘连接
- cout / wcout，ostream的实例化，标准输出通道，对应C的stdout，与显示器连接
- cerr / wcerr，ostream的实例化，报错信息使用的标准报错输出通道，对应C的stderr，与显示器连接，*与cout区别是默认无缓冲*
- clog / wclog，ostream的实例化，标准日志输出通道。无C对应物，连接与cerr相同，有缓冲

*问题：为什么正常输出与报错信息输出加以分离？*

可以让程序以不同的方式对待两种输出，如重定向至不同文件或控制台。



## 1.2 操控器manipulator

操控器的作用是改变输入的解释方式或输出的格式化方式。

重要的操控器：

- ostream
  - endl 输出'\\n'并刷新缓冲区
  - ends 输出'\\0'
  - flush 刷新缓冲区
- istream
  - ws 读入并忽略空白字符



## 1.3 Stream的Class层次体系

```c++
using istream       = basic_istream<char, char_traits<char>>;
using ostream       = basic_ostream<char, char_traits<char>>;

class basic_istream : virtual public basic_ios<char, char_traits<char>>;
class basic_ostream : virtual public basic_ios<char, char_traits<char>>;

class basic_ios : public ios_base;
```

```c++
using streambuf     = basic_streambuf<char, char_traits<char>>;
```

简述：istream和ostream分别是basic_istream和basic_ostream的模板char型实例化，这两个模板继承自basic_ios，basic_ios继承自ios_base（一个模板实例化，两层继承关系）。

- ios_base 定义状态和格式标识相关的组件和函数
- basic_streambuf负责实际的读写操作
- char_traits用于提供字符类型的一些操作和特性，如复制、比较、查找等



## 1.4 标准stream的操作符<< 和 >>

箭头方向指向即流的方向，也是数据的目标方向。



## 1.5 具体数据类型IO

在输入输出之前，流的failbit一定不能置位，否则是无法IO的。可通过clear恢复流的状态。

- 数值类型

  ```c++
  int x = -1;
  std::cin >> x;
  ```

  从缓冲区获取第一个数字，直到遇到非数字字符；如果获取失败，则failbit置位，x被置为0

  ```c++
  double y = 0;
  std::cin >> y;
  ```

  从缓冲区获取的第一个字符是数字或小数点，直到遇到不能构成数字的字符；如果失败则failbit置位，y被置为0

- bool类型

  ```c++
  bool flag = false;
  std::cin >> flag;
  ```

  bool类型的输入只能使用字符0或字符1。0对应false，1对应true。其他数字下，failbit会被置位（目标设为true）。

- char或wchar

  默认跳过起头空白字符。如果想读入所有字符，清除skipws flag或使用成员get()

- char *

  默认跳过起头空白字符，一致读到空白字符或end-of-file为止（设置skipws改变跳过空白字符）



## 1.6 时间日期

```c++
#include <iostream>
#include <chrono>
#include <iomanip>

int main()
{
    auto now = std::chrono::system_clock::now();
    //std::time_t t = std::chrono::system_clock::to_time_t(now);
    std::time_t t = std::time(nullptr);
    std::tm nowTM;
    localtime_s(&nowTM, &t);

    std::cout << std::put_time(&nowTM, "date: %x\ntime: %X\n") << std::endl;
    std::cout << "Current time: " << std::put_time(&nowTM, "%Y-%m-%d %H:%M:%S") << std::endl;
}
```

```
date: 05/27/23
time: 22:14:46

Current time: 2023-05-27 22:14:46
```



## 1.7 表示“Stream状态”的常量

```c++
using iostate = int;
```

- goodbit 一切都好，指所有位均为0
- eofbit 遇到end-of-file
- failbit 某个I/O动作未成功；该标识被置位无法进行其他操作
- badbit 毁灭性错误，不确定的状态

**注意**：读取到文件最后一个字符后，继续读取，end-of-file和failbit会同时置位

**注意：**上述所有标志都只能反映最后一次操作的stream状态

iostate定义在ios_base内，但basic_ios继承自ios_base，ios又是basic_ios模板的实例化，所以访问标志可以用std::ios::eofbtt.



***状态函数***

- good() 
- eof()
- fail()
- bad()
- rdstate() 返回当前已设置的所有flag
- clear 清除所有flag
- clear(state) 清除所有flag后，设置state
- setstate(state) 加设state flag

rdstate返回一个int数据，该数据的不同位表示stream的各状态。

```c++
good(){
    rdstate() & std::ios::goodbit;
}
fail(){
    rdstate() & (ios_base::badbit | ios_base::failbit);
}
```

**注意：**前4个获取状态的函数不会改变状态，只是单纯获取状态。



## 1.8 Stream状态与bool条件测试

- ***operator bool ()*** 相当于***! fail()***
- ***operator bool ! ()*** 相当于***fail()***

```c++
if (std::cin) {
    
}
if (!std::cin) {
    
}

```



## 1.9 异常

stream默认不抛出异常，但也可通过exceptions(flag)设置来在标志被置位时抛出异常。



## 1.10 区别于操作符(<<、>>)的I/O函数

操作符<<、>>用于读写格式化数据（跳过起始空白字符，根据具体类型决定读到哪个位置停止）。

I/O函数可以取代标准stream操作符<<>>的成员函数，均可用于读写无格式（unformatted）数据（不跳过起始空白）。