**类的属性与方法**

（1）类的属性与方法分2种，公有和私有，没有protected

（2）公有可完全继承

（3）类实例化时，先执行父类构造，再执行子类构造，注意是______init______，不是______int______

（4）公有属性方法不带双前导下划线，私有方法带双前导下划线

（5）约定单前导下划线为protected，属性访问提供函数接口（配@property）

按照C++的编程习惯，类属性只要单前导下划线和双前导下划线属性。