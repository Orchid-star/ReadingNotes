对比C++的虚函数与纯虚函数，python的虚函数与纯虚函数是有很大区别的。

首先理清一下重载（overload）与覆盖（override）的区别。

函数名相同、形参不同、功能相似的一组函数构成**函数重载**。C++中我们可以对继承自父类的函数（非virtual修饰的）进行重写。这类函数的调用取决于对象指针类型所限定的唯一的命名空间。如，父指针指向子对象，父子针调用方法时调用的是父类中定义的方法，而不会调用子类中的同名方法。为了实现父指针指向父对象，调用方法时，调用子类的方法，所以引入了虚函数，使用virtual和override修饰。

我们依然可以简单的认为，函数调用取决于对象类型定义的唯一的命名空间。而父类中的虚函数，给了子类来**覆盖**父类中virtual函数的能力，相当于改写了父类命名空间的virtual函数。所以父类指针调用virtual方法时，在自身命名空间内调用了被子类覆盖的函数。

在python中的逻辑依然遵循**函数调用取决于对象类型定义的唯一的命名空间**这一原则。python不会出现父指针指向子对象同时出现两个命名空间的情况，所以它的多态的实现更像是C++中模板的概念，在运行阶段根据类型的命名空间来调用相应的函数，传入的对象不同，调用的同名函数效果自然也不相同。



纯虚函数：

```pyt
from abc import ABC, abstractmethod

class CBase(ABC):
	@abstractmethod
	def func(self):
		pass
```

使用abstractmethod修饰的就是纯虚函数，不管函数体内有具体实现还是pass。一般都使用pass。





注意以下代码可能存在的问题：

```pyt
class CModuleBase(QtCore.QObject):
    signal_activated = QtCore.pyqtSignal(QtWidgets.QWidget)

    def __init__(self, parent=None):
        super(CModuleBase, self).__init__(parent)
        self._name_btn = QtWidgets.QPushButton()
        self._name_btn.clicked.connect(lambda: self.signal_activated.emit(self._widget))
        self._name_btn.setText(self.module_name())
        self._widget = self.create_widget()


class CDirVisible(CModuleBase):
    def __init__(self, parent=None):
        self.dir_edit = None
        self.info_plain = None
        super(CDirVisible, self).__init__(parent)
    
    def create_widget(self):
    	...
    	pass

```

子类对父类的create_widget()进行了覆盖，父类的构造中又调用了create_widget()函数。需要注意的有几点：

（1）子类实例化时，调用了super函数，所以会执行父类的构造。执行父类的构造时，self的类型是子类型，不是父类型，所以执行父类的构造时，调用create_widget()函数是执行的子类的create_widget()函数

（2）子类的create_widget()函数中实例化的类成员，初始化时注意需要在super之前

