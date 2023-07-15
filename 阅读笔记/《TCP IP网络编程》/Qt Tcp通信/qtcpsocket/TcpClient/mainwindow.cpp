#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QHostAddress>
#include <QTcpSocket>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_p_socket(nullptr)
{
    ui->setupUi(this);
    init_mainwindow();
    init_socket();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init_mainwindow()
{
    ui->history_edit->setReadOnly(true);
    ui_protect(true);
}

void MainWindow::init_socket()
{
    m_p_socket = new QTcpSocket(this);
    connect(m_p_socket, &QTcpSocket::connected, this, [=](){
        ui->statusbar->showMessage("当前状态: 连接成功");
        ui_protect(false);
    });
    connect(m_p_socket, &QTcpSocket::disconnected, this, [=](){
        ui->statusbar->showMessage("当前状态: 未连接");
        ui_protect(true);
    });
    connect(m_p_socket, &QTcpSocket::readyRead, this, [=](){
        QString contents = m_p_socket->readAll();
        contents = QString("客户端:") + contents;
        ui->history_edit->append(contents);
    });
}

void MainWindow::ui_protect(bool flag)
{
    ui->connect->setEnabled(flag);
    ui->disconnect->setEnabled(!flag);
}


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

void MainWindow::on_send_data_clicked()
{
    QString contents;

    if (m_p_socket->state() & QTcpSocket::ConnectedState) {
        contents = ui->emit_edit->toPlainText();
        if (!contents.isEmpty()) {
            m_p_socket->write(contents.toUtf8());
            ui->emit_edit->clear();
            ui->history_edit->append("客户端：" + contents);
        }
    }
}

