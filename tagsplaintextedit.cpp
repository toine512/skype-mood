#include "tagsplaintextedit.h"

TagsPlainTextEdit::TagsPlainTextEdit(QWidget *parent) :
    QWidget(parent)
{
    pte = new QPlainTextEdit;
    pte->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Ignored);
    connect(pte, SIGNAL(textChanged()), this, SIGNAL(textChanged()));

    QToolBar *bar = new QToolBar;
    bar->setIconSize(QSize(20, 20));
    bar->setStyleSheet("spacing: 2px;");
    QAction *act = new QAction(QIcon(":editor_icons/linkdialog.png"), tr("Link"), this);
    act->setData("a");
    bar->addAction(act);
    bar->addSeparator();
    act = new QAction(QIcon(":editor_icons/bold.png"), tr("Bold"), this);
    act->setData("b");
    bar->addAction(act);
    act = new QAction(QIcon(":editor_icons/italic.png"), tr("Italic"), this);
    act->setData("i");
    bar->addAction(act);
    act = new QAction(QIcon(":editor_icons/underline.png"), tr("Underlined"), this);
    act->setData("u");
    bar->addAction(act);
    act = new QAction(QIcon(":editor_icons/strikeout.png"), tr("Strikethrough"), this);
    act->setData("s");
    bar->addAction(act);
    act = new QAction(QIcon(":editor_icons/lightning.png"), tr("Blink"), this);
    act->setData("blink");
    bar->addAction(act);
    act = new QAction(QIcon(":editor_icons/pilcrow.png"), tr("New Line"), this);
    act->setData("br");
    bar->addAction(act);
    bar->addSeparator();
    /*FontListComboBox *cb_font = new FontListComboBox(11, this);
    bar->addWidget(cb_font);*/
    EditableIntSizeComboBox *cb_size = new EditableIntSizeComboBox(QStringList() << "4" << "6" << "7" << "8" << "9" << "10" << "11" << "12" << "13" << "14" << "15" << "16" << "17" << "18" << "20", 1, 99, this);
    QLabel *lab_size = new QLabel;
    lab_size->setBuddy(cb_size);
    lab_size->setToolTip(tr("Font size"));
    lab_size->setPixmap(QPixmap(":editor_icons/fontheight.png"));
    lab_size->setScaledContents(true);
    lab_size->setFixedSize(cb_size->height(), cb_size->height());
    bar->addWidget(lab_size);
    bar->addWidget(cb_size);
    act = new QAction(QIcon(":editor_icons/fontcolor.png"), tr("Color"), this);
    act->setData("color");
    bar->addAction(act);

    connect(bar, SIGNAL(actionTriggered(QAction *)), this, SLOT(processAction(QAction *)));
    //connect(cb_font, SIGNAL(activated(const QString &)), this, SLOT(processFontFace(const QString &)));
    connect(cb_size, SIGNAL(sizeSelected(const QString &)), this, SLOT(processFontSize(const QString &)));

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(bar);
    layout->addWidget(pte);
    setLayout(layout);
}

QString TagsPlainTextEdit::toPlainText()
{
    return pte->toPlainText();
}

void TagsPlainTextEdit::clear()
{
    pte->clear();
}

void TagsPlainTextEdit::setPlainText(const QString &text)
{
    pte->setPlainText(text);
}

void TagsPlainTextEdit::processAction(QAction *action)
{
    QString tag = action->data().toString();
    if(tag == "a")
    {
        bool ok;
        QUrl link(QInputDialog::getText(this, tr("Hypertext link target"), tr("URL:"), QLineEdit::Normal, QString(), &ok), QUrl::TolerantMode);
        if(ok && link.isValid())
        {
            insertTags(QString("<a href=\"%1\">").arg(QString(link.toEncoded(QUrl::FullyEncoded))), "</a>");
        }
    }
    else if(tag == "br")
    {
        insertTags("", " <br />");
    }
    else if(tag == "b")
    {
        insertTags("<b>", "</b>");
    }
    else if(tag == "i")
    {
        insertTags("<i>", "</i>");
    }
    else if(tag == "u")
    {
        insertTags("<u>", "</u>");
    }
    else if(tag == "s")
    {
        insertTags("<s>", "</s>");
    }
    else if(tag == "blink")
    {
        insertTags("<blink>", "</blink>");
    }
    else if(tag == "color")
    {
        QColor color = QColorDialog::getColor(Qt::black, this, tr("Font color"));
        if(color.isValid())
        {
            insertTags(QString("<font color=\"%1\">").arg(color.name()), "</font>");
        }
    }
}

/*void TagsPlainTextEdit::processFontFace(const QString &font)
{
    //FIXME Make font input secure ! (htmlspecialchars)
    insertTags(QString("<font face=\"%1\">").arg(font), "</font>");
}*/

void TagsPlainTextEdit::processFontSize(const QString &size)
{
    insertTags(QString("<font size=\"%1\">").arg(size), "</font>");
}

void TagsPlainTextEdit::insertTags(const QString &open_tag, const QString &close_tag)
{
    QTextCursor cur = pte->textCursor();
    if(cur.hasSelection())
    {
        cur.beginEditBlock();
        int sel_end = cur.selectionEnd();
        cur.setPosition(cur.selectionStart(), QTextCursor::MoveAnchor);
        cur.insertText(open_tag);
        cur.setPosition(sel_end + open_tag.size(), QTextCursor::MoveAnchor);
        cur.insertText(close_tag);
        cur.endEditBlock();
    }
    else
    {
        cur.insertText(QString(open_tag).append(close_tag));
    }
    pte->setTextCursor(cur);
}
