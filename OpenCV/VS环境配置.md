**VC++目录**：

包含目录：添加.\OpenCV\opencv\build\include

库目录：添加.\OpenCV\opencv\build\x64\vc16\lib



**链接器-->输入**：

附加依赖项：64位debug添加opencv_world481d.lib, 64位Release添加opencv_world481.lib



测试程序：

```c++
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
using namespace cv;
int main()
{
    std::string image_path = "E:\\Snipaste_2023-07-12_22-50-41.png";
    Mat img = imread(image_path, IMREAD_GRAYSCALE);

    imshow("Display window", img);
    int k = waitKey(0); // Wait for a keystroke in the window
    return 0;
}
```

