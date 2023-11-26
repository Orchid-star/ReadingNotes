# GDI

GDI：图形设备接口

- ***DC***   设备上下文
- ***GetDC***
- ***ReleaseDC***
- ***CreatePen***
- ***CreateSolidBrush***
- ***RGB***
- ***SelectObject***
- ***LineTo***
- ***Rectangle***



以下截取MFC示例程序：

```c++
VOID GdiOut(HDC hdc)
{
    HPEN hpen, hpenOld;
    HBRUSH hbrush, hbrushOld;
    
    BYTE bRed = 0;
    BYTE bGreen = 0;
    BYTE bBlue = 0;
    COLORREF cPen = RGB(bRed, bGreen, bBlue);
    COLORREF cBrush = RGB(233, 0, 255);
    hpen = CreatePen(PS_SOLID, 10, cPen);
    hbrush = CreateSolidBrush(cBrush);
    hpenOld = SelectObject(hdc, hpen);
    hbrushOld = (HBRUSH)SelectObject(hdc, hbrush);
     
    ::LineTo(hdc, 500, 500);
    ::Rectange(hdc, 200, 200, 500, 500);
    
    SelectObject(hdc, hpenOld);
    DeleteObject(hpen);
    SelectObject(hdc, hBrushOld);
    DeleteObject(hbrush);
}

void CDemoDlg::OnBnCLickedButton1
{
    HWND hwnd = GetSafeHwnd(); //获取当前主dialog的句柄
    HDC hdc = ::GetDC(hwnd);
    GdiOut(hdc);
    ::ReleaseDC(hwnd, hdc);
}

void CDemoDlg::OnBnClickedButton2
{
    HDC hdc = ::GetDC(NULL);  //桌面的hdc
    GdiOut(hdc);
    ::ReleaseDC(MULL, hdc);
}
```

