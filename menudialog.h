#ifndef MENUDIALOG_H
#define MENUDIALOG_H

#include "defines.h"

#include <QApplication>

#include <QSettings>
#include <QString>
#include <QStringList>
#include <QDir>
#include <QTranslator>

#include <QDialog>
#include <QLabel>
#include <QPixmap>
#include <QPushButton>
#include <QIcon>
#include <QGridLayout>
#include <QMessageBox>
#include <QComboBox>
#include <QFrame>
#include "entitledseparator.h"

class MenuDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MenuDialog(QSettings *settings, QWidget *parent = 0);

private slots:
    void langSelected(int index);
    void aboutQt();

private:
    void listTranslations();

    QSettings *settings;

    QComboBox *cb_lang;
};

#endif // MENUDIALOG_H
