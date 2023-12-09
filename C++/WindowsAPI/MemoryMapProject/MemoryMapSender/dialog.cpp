#include "dialog.h"
#include "ui_dialog.h"
#include <QMessageBox>
#include <QDebug>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    m_h_map_object = CreateFileMapping(
                (HANDLE)0xffffffff, //hFile
                NULL, //security_attributes
                PAGE_READWRITE, //文件对象的页保护
                0, //size high dword
                0x1000, //size low dword
                L"test_shared_memory" //文件映射对象的名称
                );
    if (!m_h_map_object) {
        QMessageBox::warning(this, "Failed", "Create test_shared_memory failed");
    } else {
        m_p_mapview = (char *)MapViewOfFile(m_h_map_object, FILE_MAP_WRITE, 0, 0, 0);
        if (!m_p_mapview) {
            QMessageBox::warning(this, "Failed", "Unable to map shared memory file");
        }
    }

}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_send_btn_clicked()
{
    QString text = ui->text_edit->toPlainText();
    if (m_p_mapview != nullptr) {
        memcpy(m_p_mapview, text.toUtf8().data(), text.toUtf8().length());
    }
}
