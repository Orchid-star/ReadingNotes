# Qt任务描述

1. 在qt creator中建立一个解决方案，解决方案下包含一个窗口工程，一个动态库工程，一个静态库工程，一个插件工程
2. 窗口工程调用动态库、静态库、插件



# 注意事项

- 新建项目，选择模板***其他项目*** --> ***子目录项目***

- pro文件中，路径`$$PWD`表示当前pro所在文件夹，如`$$PWD/../Win32`

- 由于`$$PWD/../Win32`若带空格则会失效，所以可用单引号括起来，如`'$$PWD/../Win32'`

- `INSTALLS`可以用于拷贝文件至指定路径，用法是

  ```
  copy1.path = '$$PWD/../main_pro/includes'
  copy1.files += \
      test_dll_b.h \
      test_dll_global.h \
      test_dll_a.h
  
  copy2.path = '$$PWD/../Win32'
  copy2.files += '$$PWD/lib/test_mydll.dll'
  INSTALLS += copy1 copy2
  ```

  但注意，需要在***项目*** --> ***Build步骤*** --> ***添加Build步骤*** --> ***Make arguments中输入install***，详情折叠起来即设置好了

  这里的使用场景是将dll工程产生的库以及相关的头文件拷贝到指定位置供其他项目调用。

- 主项目中，需要注意的是`LIBS`的设置，参考如下

  ```
  //格式 LIBS += -L库路径 -l库名称
  INCLUDEPATH += includes
  LIBS += -L$$PWD/../Win32 -ltest_mydll
  TARGET = main_pro
  DESTDIR = '$$PWD/../Win32'
  ```

- 静态库与动态库中，pro的设置区别很小

  ```
  # 静态库
  TEMPLATE = lib
  CONFIG += staticlib
  ```

  ```
  # 动态库
  TEMPLATE = lib
  ```

  



# VS

## 注意事项

- 新建一个空项目，在属性中，做如下修改

  - 配置设置为***所有配置***和***所有平台***
  - 将***配置属性***修改为***动态库（.dll）***
  - 根据实际修改输出目录（如$(SolutionDir)Win32\）目标文件名（如test_dll)

- 添加一个***global.h***头文件，用于定义决定是导出库还是导入库

  ```c++
  #pragma once
  
  #ifdef DLL_PRO
  #define DLL_CLASS _declspec(dllexport)
  #else
  #define DLL_CLASS _declspec(dllimport)
  #endif
  ```

- 添加第一个类CTest1，**注意声明添加宏DLL_CLASS**

  ```c++
  //test1.h
  #pragma once
  #include "global.h"
  
  class DLL_CLASS CTest1
  {
  public:
  	CTest1();
  	void echo_msg(const char *msg);
  };
  ```

  ```c++
  //test1.cpp
  #include "test1.h"
  #include <iostream>
  
  CTest1::CTest1()
  {
  }
  
  void CTest1::echo_msg(const char* msg)
  {
  	std::cout << "test1:" << msg << std::endl;
  }
  ```

- 添加第二个类CTest2，**注意声明添加宏DLL_CLASS**

  ```c++
  //test2.h
  #pragma once
  #include "global.h"
  
  class DLL_CLASS CTest2
  {
  public:
  	CTest2();
  	void echo_msg(const char* msg);
  };
  ```

  ```c++
  //test2.h
  #include "test2.h"
  #include <iostream>
  
  CTest2::CTest2()
  {
  }
  
  void CTest2::echo_msg(const char* msg)
  {
  	std::cout << "test2:" << msg << std::endl;
  }
  ```

  

- 在***属性*** --> ***C/C++*** --> ***预处理器***，添加宏***DLL_PRO***(如果没有上面添加CTest1和CTest2，导致没有cpp文件，则找不到C/C++选项)（时刻注意属性修改的是debug还是release，是32还是64，所以属性中要针对***所有配置***和***所有平台***设置）。

- 生成解决方案，在WIn32下有目标文件

下面新建工程用于使用上述动态库

- 新建空工程，添加main函数
- 将库对应的头文件（test1.h test2.h global.h)拷贝到当前工程并添加到当前工程中
- ***属性*** -->  ***链接器*** --> ***常规*** --> ***附加库目录*** 设置库所在的目录（如上面的Win32，也意味着lib库可不在exe同目录，但exe必须在同目录）
- ***属性*** -->  ***链接器*** --> ***输入*** --> ***附加依赖项***s 设置库名称，注意是***lib***,如上面的test_dll.lib

