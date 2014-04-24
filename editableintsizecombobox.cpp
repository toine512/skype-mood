#include "editableintsizecombobox.h"

EditableIntSizeComboBox::EditableIntSizeComboBox(const QStringList &default_values, int range_bottom, int range_top, QWidget *parent) :
    QComboBox(parent)
{
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    setFixedWidth(computeBoxWidth(countIntDigits(range_top)));
    setEditable(true); //Set the validator AFTER this !
    setInsertPolicy(QComboBox::NoInsert);
    setValidator(new QIntValidator(range_bottom, range_top, this));
    addItems(default_values);
    connect(lineEdit(), SIGNAL(returnPressed()), this, SLOT(onReturnPressed()));
    connect(this, SIGNAL(activated(const QString &)), this, SIGNAL(sizeSelected(const QString &)));
}

//Called when Return is pressed in the edit of the QComboBox
void EditableIntSizeComboBox::onReturnPressed()
{
    QString input = lineEdit()->text();
    validator()->fixup(input); //Used to remove preceding zeros
    emit sizeSelected(input);
}
