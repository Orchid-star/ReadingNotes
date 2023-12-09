#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <Windows.h>

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void on_send_btn_clicked();

private:
    Ui::Dialog *ui;
    HANDLE m_h_map_object;
    char *m_p_mapview;
};
#endif // DIALOG_H
