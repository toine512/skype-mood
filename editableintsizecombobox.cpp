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
    //connect(this, SIGNAL(activated(const QString &)), this, SIGNAL(sizeSelected(const QString &)));
    connect(this, SIGNAL(activated(const QString &)), this, SLOT(emitSizeSelectedProxy(const QString &)));
}

//Called when Return is pressed in the edit of the QComboBox
void EditableIntSizeComboBox::onReturnPressed()
{
    emitSizeSelectedProxy(lineEdit()->text(), true);
}

void EditableIntSizeComboBox::emitSizeSelectedProxy(const QString &size, bool return_pressed)
{
    //Working around a stupid QComboBox inconsistency that makes sizeSelected() [signal] emitted twice in a row in certain circumstances !
    static QString previous_size;
    if(return_pressed)
    {
        if(!(findText(size, Qt::MatchFixedString) > -1 && size != previous_size)) //activated() [signal] is problematically emitted when return is pressed if the item alread exists in the list AND is different from the previous (activated() is not emitted when the same item is return-pressed several times in a row)
        {
            QString to_clean = size;
            validator()->fixup(to_clean); //Used to remove preceding zeros
            emit sizeSelected(to_clean);
        }
    }
    else
    {
        emit sizeSelected(size);
    }
    previous_size = size;
}
