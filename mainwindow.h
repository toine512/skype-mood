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
#include <QTranslator>
#include <QLocale>

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
#include "tagsplaintextedit.h"
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

private slots:
    /* GUI */
    void enableEditing();
    void disableEditing();
    /* Data */
    //main.db
    void browseMaindb();
    void onMaindbSelected(int index); //This slot does all the data loading
    //Mood
    void onMoodTextChanged();
    //General
    void applyAndClose();
    //History
    void historyPushToMood();
    void historyRemove();
    void historyClear();

private:
    /* Init functions */
    bool findSkype();
    QWidget * initContent();
    bool listMaindb();

    QString skype_path;
    bool skype_was_killed;

protected:
    void initTranslator();

    QSettings *settings;
    QSqlDatabase maindb;
    QStringListModel *history_model;

    QLabel *lab_mood_preview;
    QComboBox *cb_maindb;
    QPushButton *btn_apply;
    TagsPlainTextEdit *pte_mood;
    SkypeContactPreview *contact_preview;
    QListView *history_view;
    QToolButton *btn_history_push;
};

#endif // MAINWINDOW_H
