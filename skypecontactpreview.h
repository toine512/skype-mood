#ifndef SKYPECONTACTPREVIEW_H
#define SKYPECONTACTPREVIEW_H

#include <QWidget>
#include <QByteArray>
#include <QPixmap>
#include <QLabel>
#include <QGridLayout>

class SkypeContactPreview : public QWidget
{
    Q_OBJECT
public:
    explicit SkypeContactPreview(QWidget *parent = 0);

public slots:
    void setPicture(const QByteArray &profile_picture);
    void setName(const QString &lab_name);
    void setMood(const QString &lab_mood);

protected:
    QLabel *lab_picture, *lab_status, *lab_name, *lab_mood;
    QGridLayout *layout;
};

#endif // SKYPECONTACTPREVIEW_H
