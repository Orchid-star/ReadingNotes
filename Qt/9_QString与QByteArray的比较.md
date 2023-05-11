**QString**

QString以UTF16编码方式保存Unicode字符。使用const char *初始化时，QString会将第一个‘\0'前的字符转换为QChar保存起来。

```c++
QString str1 = "abc";
QString str2 = "abc\0aw";
//str1与str2相等
```

QString的length()、count()以及size()没有区别，都是字符的个数（不包括'\0')



**QByteArray**

QByteArray是字节数组。QByteArray的特点是能够很方便地处理字符’\0'。

以const char *构造QByteArray时，默认以字符串的方式构造字符数组。如：

```c++
QByteArray ar1 = "abc";
QByteArray ar2 = "abc\0aw";
//ar1与ar2相等，size都是3
```

如果需要以实际裸数据保存所有字节，就需要指定长度（不管是构造函数还是fromRawData)。

```c++
QByteArray ar1("abc", 3); //size = 3
QByteArray ar2("abc\0aw", 6); //size = 6
```

QByteArray的length()、count()以及size()没有区别，表示字节数。

data()返回指向字节数组的指针，可用于修改QByeArray，*字节数组末尾为'\0'*。

data()和constData()适用于以‘\0'结尾的字符串为参数的函数。

QByteArray字节访问使用at比[]更快。at[idx]与data()[idx]相等，区别是at中idx不能等于size，而data()[idx]中idx可以为size且data()[size(0)] = '\0'。

```c++
QByteArray ar("abcd\0aw", 7);
int size = ar.size(); // size = 7

ar.at(size - 1); // w
ar.data()[size - 1]; //w

//ar.at(size); crash
ar.data()[size]; //'0'
```