#ifndef PROGRESSDIALOG_H
#define PROGRESSDIALOG_H

#include <QDialog>
#include <QString>
#include <QCloseEvent>
#include <QVBoxLayout>
#include <QProgressBar>
#include <QLabel>
#include <QMessageBox>

class ProgressDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ProgressDialog(QWidget *parent = 0);

public slots:
    void progress(const QString &msg, int step, int on);
    void success();
    void error(const QString &dialog_title, const QString &error);

protected:
    void closeEvent(QCloseEvent *event);
    bool close_lock;
    QVBoxLayout *layout;
    QProgressBar *bar;
    QLabel *text;

};

#endif // PROGRESSDIALOG_H
