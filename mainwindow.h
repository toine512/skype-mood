#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "defines.h"

#include <QSettings>
//#include <QStandardPaths>
#include <QString>
#include <QRegularExpression>
#include <QStringList>
#include <QDir>
#include <QFile>
#include <QDateTime>
#include <QProcess>
#include <QThread>
#include <QApplication>

#include <QMainWindow>
#include <QMessageBox>
#include <QDesktopWidget>
#include <QRect>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QToolButton>
#include <QIcon>
#include <QFileDialog>
#include <QPlainTextEdit>
#include <QListView>
#include <QStringListModel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include "progressdialog.h"
#include "skypecontactpreview.h"
#include "entitledseparator.h"
#include "htmldelegate.h"
#include "menudialog.h"

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected slots:
    void enableEditing();
    void disableEditing();
    void browseMaindb();
    void onMaindbSelected(int index);
    void onMoodTextChanged();
    void applyAndClose();
    void historyPushToMood();
    void historyRemove();
    void historyClear();

protected:
    bool listMaindb();
    QString decodeXMLEntities(QString str) const;
    QString encodeXMLEntities(QString str) const;
    QString removeTags(QString str) const;

    bool skype_was_killed;

    QSettings *settings;

    QLabel *lab_maindb, *lab_mood_preview;
    QComboBox *cb_maindb;
    QPushButton *btn_maindb, *btn_apply, *btn_menu;
    QPlainTextEdit *pte_mood;
    SkypeContactPreview *contact_preview;
    QListView *history_view;
    QToolButton *btn_history_push, *btn_history_rm, *btn_history_clear;
    QStringListModel *history_model;
    HtmlDelegate *history_itemDelegate;
    MenuDialog *dlg_menu;

    QVBoxLayout *layout_main, *layout_preview, *layout_history_btn;
    QHBoxLayout *layout_maindb, *layout_mood, *layout_history;
    //QGridLayout *layout_history;

    QSqlDatabase maindb;
};

#endif // MAINWINDOW_H
