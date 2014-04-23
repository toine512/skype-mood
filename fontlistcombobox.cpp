#include "fontlistcombobox.h"

FontListComboBox::FontListComboBox(int preview_point_size, QWidget *parent) :
    QComboBox(parent)
{
    setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed);
    //Fixes the height to the QComboBox standard height
    setFixedHeight(QComboBox().sizeHint().height());

    connect(this, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(updateCurrentTextFont(const QString &)));

    QStringList fonts_list(QFontDatabase().families());
    addItems(fonts_list);
    int size = fonts_list.size();
    for(int i = 0 ; i < size ; ++i)
    {
        setItemData(i, QFont(fonts_list.at(i), preview_point_size), Qt::FontRole);
    }
}

void FontListComboBox::updateCurrentTextFont(const QString &font)
{
    setFont(font);
}
