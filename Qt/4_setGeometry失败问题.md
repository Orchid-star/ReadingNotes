**问题描述**

为了添加美化效果，重写了QMainWindow等窗口的标题栏，通过自定义标题栏窗口实现最大化、最小化、还原、关闭等操作。这些操作涉及到窗口的尺寸变化。在调试过程中出现以下问题：

打开一个QMainWindow后，窗口正常显示。最大化窗口后，关闭窗口，再打开窗口。窗口绝大部分控件无法操作，呈现一种"假死"状态。所谓”假死“，是因为窗口与程序主窗口位于相同进程，而程序主窗口可正常显示并操作，该异常窗口也可被鼠标进行拖动，说明程序运行正常，只是该窗口的显示出现的问题。通过log发现抱错如下：

<font face=Consolas>    Warning:time:2023-02-27-20-19 <br><font color=red>QWindowsWindow::setGeometry: Unable to set geometry 1024x576+0+0</font> (frame: 1024x576+0+0) on QWidgetWindow/"CAwIvSimulationWidgetClassWindow" on "\\.\DISPLAY1". <br>Resulting geometry: 1536x824+0+0 (frame: 1536x824+0+0) margins: 0, 0, 0, 0 minimum size: 547x246 MINMAXINFO maxSize=0,0 maxpos=0,0 mintrack=547,246 maxtrack=0,0)  qwindowswindow.cpp  1878  void __thiscall QWindowsWindow::setGeometry(const class QRect &)</font><br>



**问题修复**

经过调试发现，最大化后的窗口在关闭后再次打开时，窗口的尺寸发生了变化，如错误信息所提示，窗口进行了setGeometry设置还原尺寸的操作。

目前未找到问题的根因。查询部分资料显示该现象由父子窗口尺寸不协调导致，且只出现再Windows系统中。但通过尝试找到了有效解决此问题的方法：

在窗口的resizeEvent()事件处理函数，调用resize()函数重新设置event事件携带的窗口尺寸信息即可。但一般情况下，resizeEvent()事件处理函数不推荐调用窗口尺寸操作相关函数，可能会陷入递归循环问题。