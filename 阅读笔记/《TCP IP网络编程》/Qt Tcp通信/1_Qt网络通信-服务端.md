**QTcpServer和QTcpSocket服务端搭建基本步骤**



***第1步：准备全局的QTcpServer和QTcpSocket对象指针m_p_server、m_p_socket***

```c++
/*mainwindow.h*/
class MainWindow : public QMainWindow
{
    ... 
private:
	QTcpServer *m_p_server;
    QTcpSocket *m_p_socket;
}
```



***第2步：实例化QTcpServer对象并绑定newConnection信号***

```c++
void MainWindow::instantiate_tcp_server()
{
    m_p_server = new QTcpServer(this);
    connect(m_p_server, &QTcpServer::newConnection, this, [=](){
        //1 获取通信套接字指针
        m_p_socket = m_p_server->nextPendingCOnnection();
        // 2 连接成功，在此处服务端可做相应处理，如信息提示、防呆
        /*...*/
        //3 绑定disconnected和readyRead信号和槽
        connect(m_p_socket, &QTcpSocket::disconnected, this, &MainWindow::disconnect_slot));
        connect(m_p_socket, &QTcpSocket::readyRead, this, &MainWindow::read_data);  
    }
}
```



***第3步：完成上一步中的两个槽函数***

```c++
void MainWindow::disconnect_slot()
{
    //1 断开信息提示
    //2 断开防呆
}

//此处的read_data能够读取到客户端发送来的所有数据，但是每一次read_data到的数据大小是随机不确定的
void MainWindow::read_data()
{
    //1 获取数据
    QByteArray data = m_p_socket->readAll();
    //2 处理数据
    ui->history_edit->append(QString("客户端：") + data);
}
```



***第4步：制作数据发送槽函数***

```c++
void MainWindow::on_send_data_clicked()
{
    QString contects;
    if (m_p_socket != Q_NULLPTR) {
        if (m_p_socket->state() & QTcpSocket::ConnectedState) {
            contects = ui->emit_edit->toPlainText();
            m_p_socket->write(contects.toUtf8());
            ui->emit_edit->clear();
            ui->history_edit->append("服务端：" + contects);
        }
    }
}
```



***第5步：完成断开连接槽***

```c++
void MainWindow::on_disconnect_clicked()
{
    if (m_p_socket != Q_NULLPTR) {
        m_p_socket->close();
        m_p_socket->deleteLater();
    }
}
```



***第6步：完成监听槽***

```c++
void MainWindow::on_listen_clicked()
{
    quint16 port = ui->port->text().toUInt();

    m_p_server->listen(QHostAddress::Any, port);
}

```

