#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QTcpServer;
class QTcpSocket;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void init_mainwindow();
    void init_socket();
    void on_listen_clicked();
    void ui_protect(bool flag);

    void on_send_data_clicked();

    void on_disconnect_clicked();

private:
    Ui::MainWindow *ui;
    QTcpServer *m_p_server;
    QTcpSocket *m_p_socket;
};
#endif // MAINWINDOW_H
