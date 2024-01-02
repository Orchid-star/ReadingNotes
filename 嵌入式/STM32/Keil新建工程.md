1. 建立工程文件夹，Keil新建工程，选择型号
2. 工程文件夹里建立Start、Library、User等文件夹，复制固件库里面的文件到工程文件夹
3. 工程里对应建立Start、Library、User等同名称的分组，然后将文件夹内的文件添加到工程分组里
4. 工程选项，C/C++,Include Paths内声明所有包含头文件的文件夹
5. 工程选项，C/C++,Define内定义USER_STDPERIPH_DRIVER
6. 工程选项，Debug，下拉列表选择对应调试器，Settings，Flash Download里勾选Reset and Run