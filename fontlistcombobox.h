#ifndef FONTLISTCOMBOBOX_H
#define FONTLISTCOMBOBOX_H

#include <QComboBox>
#include <QLineEdit>
#include <QFontDatabase>
#include <QFont>
#include <QStringList>

class FontListComboBox : public QComboBox
{
    Q_OBJECT

public:
    explicit FontListComboBox(int preview_point_size = 10, QWidget *parent = 0);

private slots:
    void updateCurrentTextFont(const QString &font);
};

#endif // FONTLISTCOMBOBOX_H
