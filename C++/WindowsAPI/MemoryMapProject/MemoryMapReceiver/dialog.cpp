#include "dialog.h"
#include "ui_dialog.h"
#include <QMessageBox>
#include <QTimer>
#include <QDebug>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    m_h_map_object = OpenFileMapping(FILE_MAP_READ, NULL, L"test_shared_memory");
    if (!m_h_map_object) {
        QMessageBox::warning(this, "Failed", "Open file mappding failed");
    } else {
        m_p_map_view = (char *)MapViewOfFile(m_h_map_object, FILE_MAP_READ, 0, 0, 0);
        if (!m_p_map_view) {
            QMessageBox::warning(this, "Error", "amp view of file failed");
        }
    }
    QTimer *ptimer = new QTimer(this);
    connect(ptimer, &QTimer::timeout, this, &Dialog::on_timer);
    ptimer->setInterval(200);
    ptimer->start();
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_timer()
{
    if (m_p_map_view != nullptr) {
        QString text(m_p_map_view);
        ui->text_edit->setText(text);
    }
}

