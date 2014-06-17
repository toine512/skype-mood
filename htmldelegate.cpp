//Retrieved from https://stackoverflow.com/questions/1956542/how-to-make-item-view-render-rich-html-text-in-qt
#include "htmldelegate.h"

HtmlDelegate::HtmlDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{ }

void HtmlDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyleOptionViewItemV4 optionV4 = option;
    initStyleOption(&optionV4, index);

    QStyle *style = optionV4.widget? optionV4.widget->style() : QApplication::style();

    QTextDocument doc;
    doc.setHtml(TagsPlainTextEdit::prepareForPreview(TagsPlainTextEdit::filterTags(optionV4.text)));
    doc.setTextWidth(optionV4.rect.width());

    //Painting item without text
    optionV4.text = QString();
    style->drawControl(QStyle::CE_ItemViewItem, &optionV4, painter);

    QAbstractTextDocumentLayout::PaintContext ctx;

    //Highlighting text if item is selected or hovered
    if (optionV4.state & QStyle::State_Selected)
    {
        ctx.palette.setColor(QPalette::Text, optionV4.palette.color(QPalette::Active, QPalette::HighlightedText));
    }
    else if(optionV4.state & QStyle::State_MouseOver)
    {
        ctx.palette.setColor(QPalette::Text, optionV4.palette.color(QPalette::Active, QPalette::Highlight));
    }

    QRect textRect = style->subElementRect(QStyle::SE_ItemViewItemText, &optionV4);
    painter->save();
    painter->translate(textRect.topLeft());
    painter->setClipRect(textRect.translated(-textRect.topLeft()));
    doc.documentLayout()->draw(painter, ctx);
    painter->restore();
}

QSize HtmlDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyleOptionViewItemV4 optionV4 = option;
    initStyleOption(&optionV4, index);

    QTextDocument doc;
    doc.setHtml(TagsPlainTextEdit::prepareForPreview(TagsPlainTextEdit::filterTags(optionV4.text)));
    doc.setTextWidth(optionV4.rect.width());
    return QSize(doc.idealWidth(), doc.size().height());
}
