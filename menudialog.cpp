#include "menudialog.h"

MenuDialog::MenuDialog(QSettings *settings, QWidget *parent) :
    QDialog(parent, Qt::MSWindowsFixedSizeDialogHint | Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint), settings(settings)
{
    QLabel *lab_notice = new QLabel(QString(tr("<p align=\"center\"><b>Skype Richtext Mood Editor v. %1</b><br />Copyright © 2014 toine512<br />Compiled on [%2] [%3]<br /><br />This software is distributed under <a href=\"https://www.gnu.org/licenses/gpl.html\">GNU General Public License v. 3</a>.</p><p>Written in C++ using <a href=\"http://qt-project.org/\">Qt</a> 5.2 (<a href=\"https://www.gnu.org/licenses/gpl.html\">GNU GPL v. 3</a>).</p><p>Uses <a href=\"http://brsev.deviantart.com/gallery/#/d24gow2\">Token icon set</a> by <a href=\"http://brsev.com/\">Evan Brooks</a>,<br /><a href=\"https://dribbble.com/shots/1383631-ilepixeli-icons\">ilepixeli icons</a> by Piotr Makarewicz (public domain),<br />and <a href=\"http://cgit.freedesktop.org/libreoffice/core/tree/icon-themes\">various icons</a> from LibreOffice 4.3.</p>")).arg(SKYPE_MOOD_VERSION_HUMAN, __DATE__, __TIME__));
    lab_notice->setOpenExternalLinks(true);

    QLabel *lab_gplv3 = new QLabel;
    lab_gplv3->setPixmap(QPixmap(":img/gplv3.png"));

    QPushButton *btn_aboutQt = new QPushButton(tr("About Qt"));
    connect(btn_aboutQt, SIGNAL(clicked()), this, SLOT(aboutQt()));

    QPushButton *btn_close = new QPushButton(tr("Close"));
    connect(btn_close, SIGNAL(clicked()), this, SLOT(close()));

    cb_lang = new QComboBox;
    listTranslations();
    connect(cb_lang, SIGNAL(activated(int)), this, SLOT(langSelected(int)));

    QFrame *line = new QFrame;
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    line->setLineWidth(1);
    line->setMidLineWidth(0);
    line->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Preferred);

    //Layout
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(lab_notice, 0, 0, 1, 2);
    layout->addWidget(new EntitledSeparator(tr("Parameters")), 1, 0, 1, 2);
    layout->addWidget(new QLabel(tr("Language:")), 2, 0, 1, 1);
    layout->addWidget(cb_lang, 2, 1, 1, 1);
    layout->addWidget(line, 3, 0, 1, 2);
    layout->addWidget(lab_gplv3, 4, 0, 2, 1);
    layout->addWidget(btn_aboutQt, 4, 1, 1, 1);
    layout->addWidget(btn_close, 5, 1, 1, 1);
    setLayout(layout);

    setWindowTitle(tr("Menu"));
}

void MenuDialog::langSelected(int index)
{
    settings->setValue("ui/lang", cb_lang->itemData(index).toString());
    QMessageBox::information(this, tr("Translation"), tr("Please restart the application for the change to take effect."));
}

void MenuDialog::aboutQt()
{
    QMessageBox::aboutQt(this);
}

void MenuDialog::listTranslations()
{
    cb_lang->addItem("English", "");
    QDir res(":translations");
    QStringList list = res.entryList(QStringList("*.qm"), QDir::Files, QDir::Name);
    foreach(QString qmf, list)
    {
        QString path = res.filePath(qmf);
        QTranslator tr;
        if(tr.load(path))
        {
            QString lang = tr.translate("meta", "language");
            cb_lang->addItem(lang, path);
            if(lang == qApp->translate("meta", "language"))
            {
                cb_lang->setCurrentIndex(cb_lang->count() - 1);
            }
        }
    }
}
