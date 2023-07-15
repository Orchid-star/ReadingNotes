#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QTcpSocket;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_disconnect_clicked();

    void on_send_data_clicked();

    void on_connect_clicked();

private:
    void init_mainwindow();
    void init_socket();
    void ui_protect(bool flag);
    Ui::MainWindow *ui;
    QTcpSocket *m_p_socket;
};
#endif // MAINWINDOW_H
