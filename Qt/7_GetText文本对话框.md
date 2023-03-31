```c++
class CGetText : public QDialog
{
    Q_OBJECT
public:
    CGetText(QString title, QString tips, QStringList except_strs = {});
    QString get_text();
    static QString get_text(QString title, QString tips, QStringList except_strs = {});

private:
    void init_param();
    void init_interface();
    void bind_event();
    void create_layout();

    QLabel m_tips_label;
    QLineEdit m_text_edit;
    QLabel m_status_info;
    QPushButton m_ok_btn;
    QPushButton m_cancel_btn;

    QString m_title;
    QString m_tips;
    QStringList m_except_strs;

    void on_ok_clicked();
    void on_cancel_clicked();
    void on_text_changed(QString text);
protected:
    void keyPressEvent(QKeyEvent *event);
};

CGetText::CGetText(QString title, QString tips, QStringList except_strs)
    :m_except_strs(except_strs)
    , m_tips(tips)
    , m_title(title)
{
    init_param();
    init_interface();
    bind_event();
}

QString CGetText::get_text()
{
    return m_text_edit.text();
}

QString CGetText::get_text(QString title, QString tips, QStringList except_strs)
{
    CGetText text_dlg(title, tips, except_strs);
    QString ret = "";
    if (QDialog::Accepted == text_dlg.exec()) {
        ret = text_dlg.get_text();
    }
    return ret;
}

void CGetText::init_param()
{
    m_ok_btn.setEnabled(false);
    m_tips_label.setText(m_tips);
    m_ok_btn.setText("OK");
    m_cancel_btn.setText("Cancel");
    m_text_edit.setValidator(new QRegExpValidator(CHAIN_NAME_REG));
    setWindowTitle(m_title);
}

void CGetText::init_interface()
{
    create_layout();
}

void CGetText::bind_event()
{
    connect(&m_ok_btn, &QPushButton::clicked, this, &CGetText::on_ok_clicked);
    connect(&m_cancel_btn, &QPushButton::clicked, this, &CGetText::on_cancel_clicked);
    connect(&m_text_edit, &QLineEdit::textChanged, this, &CGetText::on_text_changed);
}

void CGetText::create_layout()
{
    QVBoxLayout *p_main_lay = new QVBoxLayout;
    QHBoxLayout *p_toolbox_lay = new QHBoxLayout;
    setLayout(p_main_lay);
    p_toolbox_lay->addStretch();
    p_toolbox_lay->addWidget(&m_ok_btn);
    p_toolbox_lay->addWidget(&m_cancel_btn);
    p_main_lay->addWidget(&m_tips_label);
    p_main_lay->addWidget(&m_text_edit);
    p_main_lay->addWidget(&m_status_info);
    p_main_lay->addLayout(p_toolbox_lay);
    m_tips_label.setWordWrap(true);
    m_text_edit.setFocus();
    resize(600, 150);
}

void CGetText::on_ok_clicked()
{
    accept();
}

void CGetText::on_cancel_clicked()
{
    m_text_edit.clear();
    reject();
}

void CGetText::on_text_changed(QString text)
{
    if (text.isEmpty()) {
        m_status_info.setText("<font color=#f00>chain name can not be empty.</font>");
    } else if (m_except_strs.contains(text)) {
        m_status_info.setText(QString("<font color=#f00>chain %1 already exists.</font>").arg(text));
    } else if (text.length() > CHAIN_NAME_MAX_LEN) {
        m_status_info.setText(QString("<font color=#f00>%1 is too long.</font>").arg(text));
    } else {
        m_status_info.clear();
    }
    m_ok_btn.setEnabled(m_status_info.text().isEmpty());
}

void CGetText::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
        if (m_ok_btn.isEnabled()) {
            on_ok_clicked();
        }
    }
}
```

