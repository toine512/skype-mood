#ifndef ENTITLEDSEPARATOR_H
#define ENTITLEDSEPARATOR_H

#include <QWidget>
#include <QString>
#include <QLabel>
#include <QFrame>
#include <QHBoxLayout>

class EntitledSeparator : public QWidget
{
    Q_OBJECT

public:
    explicit EntitledSeparator(const QString &title, QFrame::Shape shape = QFrame::HLine, QFrame::Shadow shadow = QFrame::Sunken, int lineWidth = 1, int midLineWidth = 0, QWidget *parent = 0);
};

#endif // ENTITLEDSEPARATOR_H
