#ifndef SKYPECONTACTPREVIEW_H
#define SKYPECONTACTPREVIEW_H

#include <QWidget>
#include <QByteArray>
#include <QPixmap>
#include <QLabel>
#include <QGridLayout>
#include <QRegularExpression>

class SkypeContactPreview : public QWidget
{
    Q_OBJECT

public:
    explicit SkypeContactPreview(QWidget *parent = 0);

public slots:
    void setPicture(const QByteArray &profile_picture);
    void setName(const QString &name);
    void setMood(QString mood);

private:
    QLabel *lab_picture, *lab_name, *lab_mood;
};

#endif // SKYPECONTACTPREVIEW_H
