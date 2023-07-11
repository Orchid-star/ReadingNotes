一个类的信号槽中使用了自定义数据类型，需要在信号槽使用之前(connect之前)进行注册：

```c++
qRegisterMetatype<QVector<int>>("QVector<int>");
```

我们可以在使用了自定义类型数据的信号的类的构造函数一开始，就进行注册。在main函数实例化app后，就进行类型注册，效果是最好的。