#ifndef TAGSPLAINTEXTEDIT_H
#define TAGSPLAINTEXTEDIT_H

#include <QWidget>
#include <QPlainTextEdit>
#include <QTextCursor>
#include <QToolBar>
#include <QAction>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QInputDialog>
#include <QColorDialog>
#include <QColor>
#include <QUrl>

#include "editableintsizecombobox.h"
//#include "fontlistcombobox.h"

class TagsPlainTextEdit : public QWidget
{
    Q_OBJECT

public:
    explicit TagsPlainTextEdit(QWidget *parent = 0);
    QString toPlainText();

public slots:
    void clear();
    void setPlainText(const QString &text);

signals:
    void textChanged();

private:
    void insertTags(const QString &open_tag, const QString &close_tag);

    QPlainTextEdit *pte;

private slots:
    void processAction(QAction *action);
    //void processFontFace(const QString &font);
    void processFontSize(const QString &size);
};

#endif // TAGSPLAINTEXTEDIT_H