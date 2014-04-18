#include "progressdialog.h"

ProgressDialog::ProgressDialog(QWidget *parent) :
    QDialog(parent, Qt::Dialog | Qt::FramelessWindowHint), close_lock(true)
{
    setAttribute(Qt::WA_DeleteOnClose);
    setFixedSize(300, 60);
    setModal(true);

    bar = new QProgressBar;
    bar->setMinimum(1);
    bar->setFormat("%v/%m");
    text = new QLabel;
    layout = new QVBoxLayout;
    layout->addWidget(bar);
    layout->addWidget(text);
    setLayout(layout);
}

void ProgressDialog::closeEvent(QCloseEvent *event)
{
    if(close_lock)
    {
        event->ignore();
    }
    else
    {
        event->accept();
    }
}

void ProgressDialog::progress(const QString &msg, int step, int on)
{
    bar->setMaximum(on);
    bar->setValue(step);
    text->setText(msg);
}

void ProgressDialog::success()
{
    close_lock = false;
    close();
}

void ProgressDialog::error(const QString &dialog_title, const QString &error)
{
    close_lock = false;
    QMessageBox::warning(this, dialog_title, error);
    close();
}
