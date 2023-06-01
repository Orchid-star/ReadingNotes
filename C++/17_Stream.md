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

**注意：**stream读字符，遇到EOF，stream的fail就会置位

### 1.10.1 Input

***（1）int istream::get()***

返回读取的字符或EOF。字符可以是任意字符，包括空格、换行符等。EOF是常量，可以是更大的数字类型，所以返回值类型不一定是字符类型。因此返回值是int。

本函数相当于C的getchar()或getc().

***(2) istream& istream::get(char &c)***

把下一个字符值传给c（任意字符），返回的stream可说明是否读取成功（遇到EOF则读取失败）。

***(3) istream& istream::get(char\* str，streamsize count)***

从缓冲中取一定字符外加一个'\0'存进str中（遇到换行符截至且不读入换行符到str中，个数包括'\0'不超过count）。**换行符依然在stream的缓冲内**。

***(4) istream& istream::get(char\* str，streamsize count，char delim)***

从缓冲中取一定字符外加一个'\0'存进str中（遇到delim截至且不读入delim到str中，个数包括'\0'不超过count）。**delim依然在stream的缓冲内**。

***(5) istream& istream::getline(char\* str, streamsize count)***

***(6) istream& istream::getline(char\* str, stremsize count, char delim***)

同（3）（4），区别在于**读取后换行符或delim会从stream的缓冲内清除**。

***(7) istream& istream::read(char\* str，streamsize count)***

读取count个字符存入str中。不会在末尾添加null（即'\0')。读入过程遇到EOF则failbit会被设置。

***(8) int istream::peak()***

返回缓冲中的字符，但不取出。

### 1.10.2 Output

output的put和write都是不论char是什么，都往stream写。

***(1) ostream& ostream::put(char c)***

将c写入stream。

***(2) ostream& ostream::write(const char\* str, streamsize count)***

从str中取count个字符，写入stream

***(3) ostream& ostream::flush()***

刷新缓冲区，也就是把数据强制写入所属设备或I/O通道。



## 1.11 操控器（manipulator）

操控器，只是函数而已。以std::endl为例，原理如下。

```c++
ostream& ostream::operator<<(ostream& (*p)(ostream&))
{
    return p(*this);
}

std::ostream& std::endl(std::ostream& strm)
{
    strm.put('\n');
    strm.flush();
    return strm;
}
```

可以参照此自定义操控器。这也是运算符重载的绝佳示范。



## 1.12 格式化（formatting）

**stream格式化**：按照一定的格式输入输出。

**字符串格式化**：将变量的值插入到一个包含占位符的字符串中，生成一个新的字符串。



## 1.13 文件访问（file access）

***ifstream 、ofstream、fstream***

**注意：**文件流分别继承自istream、ostream、iostream。

**文件标志**：

- ***in***
- ***out***
- ***app***
- ***ate***
- ***trunc***
- ***binary***

打开文件时同时考虑以下三点决定使用哪些标志：

- 是读还是写？（in、out）
- 追加还是清空？（app、trunc、ate）
- 二进制还是文本？（binary）

***文件什么时候打开？***

- 构造时设置了文件名和文件模式，则立即打开
- 构造时没有设置文件名，通过open设置文件名和文件模式之后打开

```c++
string path = "D:\\1.txt";
ofstream file(path, std::ios::binary | std::ios::out);
if (file) {
    file.write(...);
}
```

```c++
string path = "D:\\1.txt";
ofstream file;
file.open(path, std::ios::binary | std::ios::out);
if (file) {
    file.write(...);
}
```



***数据如何写入或读入？***

所有的数据都是二进制数据，唯一注意点是二进制模式和文本模式下对换行符的差异。



***随机访问（random access）***

ifstream包括tellg、seekg。

ofstream包括tellp、seekp

g = get, p = put。tell返回的是绝对位置，seek可移动到指定绝对位置或相对位置。有3个表示相对位置的常量，分别是beg、cur、end。

stream的位置类型是std::ios::pos_type或std::streampos。