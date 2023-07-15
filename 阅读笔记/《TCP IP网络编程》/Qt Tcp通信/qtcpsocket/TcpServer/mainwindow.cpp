#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTcpServer>
#include <QTcpSocket>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_p_server(nullptr)
    , m_p_socket(nullptr)
{
    ui->setupUi(this);
    init_mainwindow();
    init_socket();
    ui_protect(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init_mainwindow()
{
    ui->history_edit->setReadOnly(true);
}

void MainWindow::init_socket()
{
    m_p_server = new QTcpServer(this);

    connect(m_p_server, &QTcpServer::newConnection, this, [=](){
        m_p_socket = m_p_server->nextPendingConnection();
        ui->statusbar->showMessage("已连接1");
        ui_protect(false);
        connect(m_p_socket, &QTcpSocket::disconnected, this, [=](){
            ui->statusbar->showMessage("已断开");
            ui_protect(true);
        });
        connect(m_p_socket, &QTcpSocket::readyRead, this, [=](){
            QByteArray data = m_p_socket->readAll();
            ui->history_edit->append(QString("客户端：") + data);
        });
    });
}


void MainWindow::on_listen_clicked()
{
    quint16 port = ui->port->text().toUInt();

    m_p_server->listen(QHostAddress::Any, port);
}

void MainWindow::ui_protect(bool flag)
{
    ui->listen->setEnabled(flag);
    ui->disconnect->setEnabled(!flag);
}

void MainWindow::on_send_data_clicked()
{
    QString contects;
    if (m_p_socket != Q_NULLPTR && m_p_socket->isValid()) {
        if (m_p_socket->state() & QTcpSocket::ConnectedState) {
            contects = ui->emit_edit->toPlainText();
            m_p_socket->write(contects.toUtf8());
            ui->emit_edit->clear();
            ui->history_edit->append("服务端：" + contects);
        }
    }
}

void MainWindow::on_disconnect_clicked()
{
    if (m_p_socket != Q_NULLPTR && m_p_socket->isValid()) {
        m_p_socket->close();
        m_p_socket->deleteLater();
    }
}
