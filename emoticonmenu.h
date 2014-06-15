#ifndef EMOTICONMENU_H
#define EMOTICONMENU_H

#include <cmath>

#include <QMenu>
#include <QWidgetAction>
#include <QWidget>
#include <QGridLayout>
#include <QToolButton>
#include <QIcon>
#include <QSize>
#include <QPixmap>
#include <QByteArray>
#include <QSignalMapper>

#include "emoticonstack.h"

class EmoticonMenuWidgetAction : public QWidgetAction
{
    Q_OBJECT

public:
    explicit EmoticonMenuWidgetAction(QObject *parent = 0);
    static int computeItemsPerLineCount(int item_count, int preferred_column_count, int maximum_row_count);

protected slots:
    void buttonPressed(const QString &id);

protected:
    EmoticonStack emoticons;
    QSignalMapper *mapper;
    QWidget * createWidget(QWidget *parent);
    //void deleteWidget(QWidget *widget);
};


class EmoticonMenu : public QMenu
{
    Q_OBJECT

public:
    explicit EmoticonMenu(QWidget *parent = 0);
    static QIcon getIcon();

protected:


signals:

public slots:

};

#endif // EMOTICONMENU_H
