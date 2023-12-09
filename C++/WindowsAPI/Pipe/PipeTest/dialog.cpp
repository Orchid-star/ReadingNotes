#include "dialog.h"
#include "ui_dialog.h"
#include <Windows.h>
#include <QMessageBox>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_run_btn_clicked()
{
    BOOL b_create = FALSE;

    //准备管道
    HANDLE h_pipe_write, h_pipe_read;
    SECURITY_ATTRIBUTES sa = {0};
    sa.nLength = sizeof (sa);
    sa.bInheritHandle = TRUE;
    sa.lpSecurityDescriptor = NULL;
    b_create = CreatePipe(&h_pipe_read, &h_pipe_write, &sa, 0/*管道实际是共享内存，0表示使用默认大小*/);
    if (!b_create) {
        QMessageBox::warning(this, "Failed", "Create pip failed");
    }

    PROCESS_INFORMATION pi = {0};
    STARTUPINFO si = {0};
    si.cb = sizeof (si);
    /******设置管道*******/
    //如果只是普通创建进程，准备管道和设置管道的步骤省略即可
    si.hStdInput = GetStdHandle(STD_INPUT_HANDLE);
    si.hStdOutput = si.hStdError = h_pipe_write;
    /*******************/
    si.wShowWindow = SW_HIDE; //隐藏子进程窗口 TRUE则显示窗口,下方dwFlags去掉STARTF_USESTDHANDLES
    si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;

    TCHAR sz_cmd[512] = {0};
    QString cmd_str = ui->cmd_edit->text();
    memcpy(sz_cmd, cmd_str.utf16(), cmd_str.length() * 2);
    b_create = CreateProcess(
                NULL,
                (LPTSTR)sz_cmd,
                NULL,
                NULL,
                TRUE,
                CREATE_NEW_CONSOLE,
                NULL,
                NULL,
                &si,
                &pi);
    if (!b_create) {
        QMessageBox::warning(this, "Failed", "Create process failed");
    } else {
        WaitForSingleObject(pi.hProcess, INFINITE); //等待进程结束
        CloseHandle(h_pipe_write); //读取管道数据时必须先关闭
        char sz_buff[4096] = {0};
        DWORD dw_read = 0;
        QString cmd_ret;
        while (TRUE) {
            memset(sz_buff, 0, 4096);
            //管道关闭时才会返回0，无数据时阻塞
            if (!ReadFile(h_pipe_read, sz_buff, 4096, &dw_read, NULL)) {
                break;
            }
            cmd_ret += QString::fromLocal8Bit(sz_buff);
        }
        ui->result_edit->setText(cmd_ret);
        CloseHandle(h_pipe_read);
    }
}
