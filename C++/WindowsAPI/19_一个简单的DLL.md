# 一个简单的DLL

- **导出函数声明**

  ***extern “C" __declspec (dllexport)***

- **三个重要文件**

  ***xxx.h   xxx.lib   xxx.dll***



```c++
//edr.h
#ifdef __cplusplus
#define EXPORT extern "C" __declspce(dllexport)  //源文件是c文件，C++调用时需要加extern "C"
#else
#define EXPORT __declspec(dllexport)
#endif

EXPORT BOOL CALLBACK EdrCenterTextA(HDC hdc, PRECT prc, PCSTR pString);
EXPORT BOOL CALLBACK EdrCenterTextW(HDC hdc, PRECT prc, PCSTR pString);

#ifdef UNICODE
#define EdrCenterText EdrCenterTextA
#else
#define EdrCenterText EdrCenterTextW
#endif
```



```c++
//edr.c
#include <Windows.h>
#include "edr.h"

//入口函数
int WINAPI DllMain(HINSTANCE hInstance, DWORD fdwReason, PVOID pvReserved) {
    return TRUE;
}

EXPORT BOOL CALLBACK EdrCenterTextA(HDC hdc, PRECT prc, PCSTR pString)
{
    
}

EXPORT BOOL CALLBACK EdrCenterTextB(HDC hdc, PRECT prc, PCSTR pString)
{
    
}
```

`__declspec(dllecport) `: 将函数、变量或对象标记为可在动态链接库（DLL）内导出的符号。作为导出库的.c源文件，extern "C"是可加可不加的，但是对于使用这个库的cpp文件，即必须加了。

`CALLBACK`：是一个函数指针类型。这个函数在窗口的过程处理函数中使用，是由windows调用的，所以定义为回调指针类型。



**调用**

同时提供.h  .dll  .lib三个文件。

链接器 -- 输入 -- 附加依赖项中添加dll的导入文件lib