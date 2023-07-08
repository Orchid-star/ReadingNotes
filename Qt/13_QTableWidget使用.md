***第1步：初始化纵向表头***

```c++
void Widget::init_v_header()
{
    QString sty1 = "QHeaderView {background-color:#92bd6c;}"
              "QHeaderView::section{background-color:transparent;}";
    QHeaderView *p_vheader = verticalHeader(); //获取纵向表头对象

    p_vheader->setFixedWidth(100);		//设置固定宽度
    p_vheader->setStyleSheet(sty1);		//设置样式，使section透明；表头是一个窗口，section是表头中的子控件。设置section背景透明可以使表头整体颜色统一

    connect(p_vheader, &QHeaderView::sectionPressed, this, [=](int a){
        qDebug() << "logical v index = " << a;
    });  //section是一个控件，鼠标按下是有相应信号的。
}
```



***第2步：初始化横向表头***

```c++
void Widget::init_h_header()
{
    QString sty2 = "QHeaderView {background-color:#ffde81;}"
              "QHeaderView::section{background-color:transparent;}";
    QHeaderView *p_hheader = horizontalHeader();

    //p_hheader->setStretchLastSection(true);  最后一列是否填充剩余空间
    p_hheader->setFixedHeight(30);
    p_hheader->setStyleSheet(sty2);

    connect(p_hheader, &QHeaderView::sectionPressed, this, [=](int a){
        qDebug() << "logical h index = " << a;
    });
}
```



***第3步：设置表的行、列数量***

```c++
void Widget::init_table()
{
    int row = 10;
    int col = 5;
    QString bba = "QTableView QTableCornerButton::section{background-color:#ffde81;}"; //设置左上角button的背景色

    QStringList ls_row, ls_col;
    for (int i = 0; i < row; ++i) {
        ls_row << QString("row %1").arg(i);
    }
    for (int i = 0; i < col; ++i) {
        ls_col << QString("col %1").arg(i);
    }

    setRowCount(row); //横行数
    setColumnCount(col);  //竖列数
    setHorizontalHeaderLabels(ls_col);  //设置对应的表头标签
    setVerticalHeaderLabels(ls_row);  //设置对应的表头标签

    setCornerWidget(new QPushButton("ahahhaahah", this));  //这个与表无关，是QScrollArea出现滚动条时右下角的空间
    setStyleSheet(bba);  //设置样式
}
```

