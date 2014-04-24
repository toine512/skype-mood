#include "skypecontactpreview.h"

SkypeContactPreview::SkypeContactPreview(QWidget *parent) :
    QWidget(parent)
{
    lab_picture = new QLabel;
    lab_picture->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    QLabel *lab_status = new QLabel;
    lab_status->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    QPixmap pixmap;
    pixmap.loadFromData(QByteArray::fromBase64("iVBORw0KGgoAAAANSUhEUgAAAA4AAAAOBAMAAADtZjDiAAAAA3NCSVQICAjb4U/gAAAAKlBMVEV/ugC/3YCXxzD3++/n8s+n0FCHvhD////P5aCfy0Dv9t+PwyCv1GDH4ZB5aF3aAAAACXBIWXMAAA50AAAOdAFrJLPWAAAAHHRFWHRTb2Z0d2FyZQBBZG9iZSBGaXJld29ya3MgQ1M0BrLToAAAAFtJREFUCJljsGSYXA4EDBMYGBhylpczgEEKlGZbDhbX3XCcwYCBgdNcIZ2hgO3Y8UIGdoYCzqryBiBdxtBey8DAzFDDwBsAVMJQlQDRWu4GpauOMYDEQZYA7QIABzwWQCQgM5IAAAAASUVORK5CYII="));
    lab_status->setPixmap(pixmap);
    lab_name = new QLabel;
    lab_mood = new QLabel;

    QGridLayout *layout = new QGridLayout;
    layout->setContentsMargins(10, 5, 10, 5);
    layout->setHorizontalSpacing(10);
    layout->setVerticalSpacing(0);
    layout->addWidget(lab_picture, 0, 0, 2, 1, Qt::AlignLeft | Qt::AlignTop);
    layout->setColumnStretch(0, 0);
    layout->addWidget(lab_status, 0, 1, 1, 1, Qt::AlignTop | Qt::AlignHCenter);
    layout->setColumnStretch(1, 0);
    layout->addWidget(lab_name, 0, 2, 1, 1, Qt::AlignLeft | Qt::AlignVCenter);
    layout->addWidget(lab_mood, 1, 2, 1, 1, Qt::AlignLeft | Qt::AlignVCenter);
    layout->setColumnStretch(2, 1); //Only the third column will be stretched

    setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Fixed);
    setFixedHeight(42); //32 + 5 + 5
    setLayout(layout);

    //Set white background
    QPalette pal(palette());
    pal.setColor(QPalette::Background, Qt::white);
    setAutoFillBackground(true);
    setPalette(pal);
}

void SkypeContactPreview::setPicture(const QByteArray &profile_picture)
{
    QPixmap pixmap;
    pixmap.loadFromData(profile_picture);
    lab_picture->setPixmap(pixmap.scaled(32, 32, Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void SkypeContactPreview::setName(const QString &name)
{
    lab_name->setText(name);
}

void SkypeContactPreview::setMood(QString mood)
{
    mood.remove(QRegularExpression("<[^>]+>", QRegularExpression::CaseInsensitiveOption | QRegularExpression::DotMatchesEverythingOption));
    lab_mood->setText(QString("<font color=\"#979797\">%1</font>").arg(mood));
}
