//Retrieved from https://stackoverflow.com/questions/1956542/how-to-make-item-view-render-rich-html-text-in-qt
#ifndef HTMLDELEGATE_H
#define HTMLDELEGATE_H

#include <QApplication>
#include <QStyledItemDelegate>
#include <QPainter>
#include <QStyleOptionViewItem>
#include <QModelIndex>
#include <QStyleOptionViewItem>
#include <QStyle>
#include <QPalette>
#include <QAbstractTextDocumentLayout>
#include <QTextDocument>

#include "tagsplaintextedit.h"

class HtmlDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit HtmlDelegate(QObject *parent = 0);

protected:
    void paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const;
    QSize sizeHint(const QStyleOptionViewItem & option, const QModelIndex & index) const;
};

#endif // HTMLDELEGATE_H
