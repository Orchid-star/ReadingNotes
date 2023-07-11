***记录程序运行时间***

```c++
void func()
{
    QELapsedTimer time;
    time.start();
    //耗时操作
    int milsec = time.elapsed();  //即 耗时操作运行的时间
}
```

