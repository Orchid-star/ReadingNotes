**场景**

现在有一个动态库Project1.dll和对应的Project1.lib，已经对应的头文件ctest.h文件，如下。要求在exe运行路径Win32下新建一个文件夹dll，将Project1.dll和Project1.lib放在里面。在main函数中导出dll中的类，并调用。

```c++
// ctest.h
#pragma once

#ifdef DLL_EXPORT
#define DLL_API __declspec(dllexport)
#else
#define DLL_API __declspec(dllimport)
#endif // DLL_EXPORT

#include <iostream>
using namespace std;

#define CLASS_PRIVATE(x) private:class x##Private *pd;

class DLL_API CTest
{
public:
	CTest();
	void show_ret(string op, double v1, double v2);
	CLASS_PRIVATE(CTest)
};
```



**具体操作**

1. VS新建控制台工程，解决方案平台选择Release以及x86（由dll决定）

2. 修改属性*配置属性*  --> *常规*  -->  *输出目录*为 $(SolutionDir)Win32\

3. 生成解决方案

4. 在Win32目录下新建dll文件夹，拷贝Project1.dll和Project1.lib放置其中

5. *属性*----*链接器*-----*常规*-----*附加库目录*  中，添加dll路径 $(SolutionDir)\Win32\dll\

6. *属性*-----*链接器*-----*输入* 中，*附加依赖项* 添加Project1.lib，*延迟加载的DLL* 中添加 Project1.dll

7. 在工程中导入ctest.h文件，在main函数所在文件中包含该头文件

8. 在main函数中包含Windows.h头文件，并添加获取exe运行路径的函数，相关代码如下：

   ```c++
   #ifdef UNICODE
   #define std_string std::wstring
   #define std_cout std::wcout
   #else
   #define std_string std::string
   #define std_cout std::cout
   #endif // UNICODE
   
   std_string get_exe_dir();
   
   std_string get_exe_dir()
   {
       TCHAR exe_path[MAX_PATH];
       std_string str_path = TEXT("");
       int pos = 0;
   
       GetModuleFileName(NULL, exe_path, MAX_PATH);
       str_path = std_string(exe_path);
       pos = str_path.find_last_of('\\', str_path.length());
       return str_path.substr(0, pos);
   }
   ```

9. 在使用dll中的类之前，设置dll的搜索路径

   ```c++
   SetDllDirectory((get_exe_dir() + std_string(TEXT("\\dll\\"))).c_str());
   ```

10. 最终的main所在文件如下：

    ```c++
    // TestDll5.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
    //
    #include <Windows.h>
    #include <iostream>
    #include "ctest.h"
    
    #ifdef UNICODE
    #define std_string std::wstring
    #define std_cout std::wcout
    #else
    #define std_string std::string
    #define std_cout std::cout
    #endif // UNICODE
    
    std_string get_exe_dir();
    
    int main()
    {
        SetDllDirectory((get_exe_dir() + std_string(TEXT("\\dll\\"))).c_str());
        CTest test;
        test.show_ret("/", 20, 45);
    
        return 0;
    }
    
    std_string get_exe_dir()
    {
        TCHAR exe_path[MAX_PATH];
        std_string str_path = TEXT("");
        int pos = 0;
    
        GetModuleFileName(NULL, exe_path, MAX_PATH);
        str_path = std_string(exe_path);
        pos = str_path.find_last_of('\\', str_path.length());
        return str_path.substr(0, pos);
    }
    
    ```

    