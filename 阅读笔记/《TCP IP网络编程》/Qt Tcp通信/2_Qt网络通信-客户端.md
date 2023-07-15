**QTcpSocket搭建客户端基本步骤**



***第1步：准备全局的QTcpSocket对象指针m_p_socket***

```c++
/*MainWindow.h*/
class MainWindow : public QMainWindow
{
private:
    QTcpSocket *m_p_socket;
}
```



***第2步：实例化QTcpSocket对象并绑定3个信号槽***

```c++
void MainWindow::init_cilent()
{
    m_p_socket = new QTcpSocket(this);
    connect(m_p_socket, &QTcpSocket::connected, this, &MainWindow::connected_slot);
    connect(m_p_socket, &QTcpSocket::disconnected, this, &QMainWindow::disconnected_slot);
    connect(m_p_socket, &QTcpSocket::readyRead, this, &MainWindow::read_data);
}
```



***第3步：完成上一步中的各信号对应的槽函数***

```c++
void MainWindow::connected_slot()
{
    
}
void MainWindow::disconnected_slot()
{
    
}
void MainWindow::read_data()
{
    //1 读取数据
    QString contents = m_p_socket->readAll();
    //2 数据处理
    contents = QString("客户端:") + contents;
    ui->history_edit->append(contents);
}
```



***第4步：完成主动连接槽和主动断开槽***

```c++
void MainWindow::on_connect_clicked()
{
    QHostAddress addr(ui->addr->text());
    quint16 port = ui->port->text().toUInt();

    m_p_socket->connectToHost(addr, port);
}

void MainWindow::on_disconnect_clicked()
{
    m_p_socket->close();
}
```



***第5步：完成数据发送槽***

```c++
void MainWindow::on_send_data_clicked()
{
    QString contents;

    if (m_p_socket->state() & QTcpSocket::ConnectedState) {
        contents = ui->emit_edit->toPlainText();
        if (!contents.isEmpty()) {
            m_p_socket->write(contents.toUtf8()); //数据发送
            ui->emit_edit->clear();
            ui->history_edit->append("客户端：" + contents);
        }
    }
}
```

