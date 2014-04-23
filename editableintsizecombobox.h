#ifndef EDITABLEINTSIZECOMBOBOX_H
#define EDITABLEINTSIZECOMBOBOX_H

#include <QString>
#include <QStringList>

#include <QComboBox>
#include <QIntValidator>
#include <QLineEdit>

#define DEFAULT_SIZE_LIST QStringList() << "6" << "7" << "8" << "9" << "10" << "11" << "12" << "13" << "14" << "15" << "16" << "17" << "18" << "20" << "22" << "24" << "26" << "28" << "32" << "36" << "40" << "44" << "48" << "54" << "60" << "66" << "72" << "80" << "88" << "96"

class EditableIntSizeComboBox : public QComboBox
{
    Q_OBJECT

public:
    explicit EditableIntSizeComboBox(const QStringList &default_values = DEFAULT_SIZE_LIST, int range_bottom = 1, int range_top = 99, QWidget *parent = 0);

signals:
    void sizeSelected(const QString &);

private slots:
    void onReturnPressed();
};

#endif // EDITABLEINTSIZECOMBOBOX_H
