#ifndef MENUDIALOG_H
#define MENUDIALOG_H

#include "defines.h"

#include <QApplication>

#include <QString>

#include <QDialog>
#include <QLabel>
#include <QPixmap>
#include <QPushButton>
#include <QIcon>
#include <QGridLayout>
#include <QMessageBox>

class MenuDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MenuDialog(QWidget *parent = 0);

protected slots:
    void aboutQt();

protected:
    QLabel *lab_notice, *lab_gplv3;
    QPushButton *btn_aboutQt;
    QGridLayout *layout;
};

#endif // MENUDIALOG_H
