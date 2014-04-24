#include "menudialog.h"

MenuDialog::MenuDialog(QSettings *settings, QWidget *parent) :
    QDialog(parent, Qt::MSWindowsFixedSizeDialogHint | Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint), settings(settings)
{
    QLabel *lab_notice = new QLabel(QString("<p align=\"center\"><b>Skype Richtext Mood Editor v. %1</b><br />Copyright © 2014 toine512<br />Compiled on [%2] [%3]<br /><br />This software is distributed under <a href=\"https://www.gnu.org/licenses/gpl.html\">GNU General Public License v. 3</a>.</p><p>Written in C++ using <a href=\"http://qt-project.org/\">Qt</a> 5.2 (<a href=\"https://www.gnu.org/licenses/gpl.html\">GNU GPL v. 3</a>).<br />Uses <a href=\"http://brsev.deviantart.com/gallery/#/d24gow2\">Token icon set</a> by <a href=\"http://brsev.com/\">Evan Brooks</a>.</p>").arg(SKYPE_MOOD_VERSION_HUMAN, __DATE__, __TIME__));
    lab_notice->setOpenExternalLinks(true);

    QLabel *lab_gplv3 = new QLabel;
    lab_gplv3->setPixmap(QPixmap(":img/gplv3.png"));

    QPushButton *btn_aboutQt = new QPushButton("About Qt");
    connect(btn_aboutQt, SIGNAL(clicked()), this, SLOT(aboutQt()));

    cb_lang = new QComboBox;
    listTranslations();
    connect(cb_lang, SIGNAL(activated(int)), this, SLOT(langSelected(int)));

    //Layout
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(lab_notice, 0, 0, 1, 2);
    layout->addWidget(new QLabel(tr("Language:")), 1, 0, 1, 1);
    layout->addWidget(cb_lang, 1, 1, 1, 1);
    layout->addWidget(lab_gplv3, 2, 0, 1, 1);
    layout->addWidget(btn_aboutQt, 2, 1, 1, 1);
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
