#ifndef TAGSPLAINTEXTEDIT_H
#define TAGSPLAINTEXTEDIT_H

#include <QWidget>
#include <QPlainTextEdit>
#include <QTextCursor>
#include <QToolBar>
#include <QAction>
#include <QToolButton>
#include <QLabel>
#include <QPixmap>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QInputDialog>
#include <QColorDialog>
#include <QColor>
#include <QUrl>

#include "editableintsizecombobox.h"
//#include "fontlistcombobox.h"
#include "emoticonmenu.h"
#include "emoticonstack.h"

class TagsPlainTextEdit : public QWidget
{
    Q_OBJECT

public:
    explicit TagsPlainTextEdit(QWidget *parent = 0);
    QString toPlainText();
    static void decodeXMLEntities(QString &str);
    static void encodeXMLEntities(QString &str);
    static QString filterTags(const QString &input);
    static QString prepareForPreview(const QString &mood);

public slots:
    void clear();
    void setPlainText(const QString &text);

signals:
    void textChanged();

private:
    void insertTags(const QString &open_tag, const QString &close_tag, const QString &inner_text = QString(), bool force_inner_text = false);

    QPlainTextEdit *pte;

private slots:
    void processAction(QAction *action);
    //void processFontFace(const QString &font);
    void processFontSize(const QString &size);
    void processEmoticon(QAction *action);
};

#endif // TAGSPLAINTEXTEDIT_H
