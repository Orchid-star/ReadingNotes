```c++
#include <QApplication>
#include <QLabel>
#include <QDebug>
QString get_tool_tip()
{
    /*
    font设置字体、颜色、大小
    <i>文本</i>设置文本为斜体
    <b>文本</b>设置文本加粗
    <br>等同于换行符\n，但二者不能混用。使用\n时html语法将失效
    &#[数字];表示特殊字符，如"&#10;"表示换行符，注意分号
    */
    QString text1 = "<font color=#ff0000 size=14 face=Times New Roman>China</font>";
    QString text2 = "<font color=#00ff00 size=10 face=Arial> in</font>";
    QString text3 = "<font color=#00ff00 size=14 face=Times New Roman><i><b> 2023</b></i></font>";
    QString text4 = "<br>Awinic is a IC company<br> loacted in Shanghai Minhang.";
    return text1 + text2 + text3 + text4;
}
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QString text = get_tool_tip();
    QLabel w;
    w.setToolTip(text);
    w.setText(text);
    w.show();
    return a.exec();
}
```