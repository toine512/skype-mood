#include "menudialog.h"

MenuDialog::MenuDialog(QWidget *parent) :
    QDialog(parent, Qt::MSWindowsFixedSizeDialogHint | Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint)
{
    lab_notice = new QLabel(QString("<p align=\"center\"><b>Skype Richtext Mood Editor v. %1</b><br />Copyright © 2014 toine512<br />Compiled on [%2] [%3]<br /><br />This software is distributed under <a href=\"https://www.gnu.org/licenses/gpl.html\">GNU General Public License v. 3</a>.</p><p>Written in C++ using <a href=\"http://qt-project.org/\">Qt</a> 5.2 (<a href=\"https://www.gnu.org/licenses/gpl.html\">GNU GPL v. 3</a>).<br />Uses <a href=\"http://brsev.deviantart.com/gallery/#/d24gow2\">Token icon set</a> by <a href=\"http://brsev.com/\">Evan Brooks</a>.</p>").arg(SKYPE_MOOD_VERSION_HUMAN, __DATE__, __TIME__));
    lab_notice->setOpenExternalLinks(true);

    lab_gplv3 = new QLabel;
    lab_gplv3->setPixmap(QPixmap(":img/gplv3.png"));

    btn_aboutQt = new QPushButton("About Qt");

    //Layout
    layout = new QGridLayout;
    layout->addWidget(lab_notice, 0, 0, 1, 2);
    layout->addWidget(lab_gplv3, 1, 0, 1, 1);
    layout->addWidget(btn_aboutQt, 1, 1, 1, 1);

    setLayout(layout);
    setWindowTitle(tr("Menu"));

    connect(btn_aboutQt, SIGNAL(clicked()), this, SLOT(aboutQt()));
}

void MenuDialog::aboutQt()
{
    QMessageBox::aboutQt(this);
}
