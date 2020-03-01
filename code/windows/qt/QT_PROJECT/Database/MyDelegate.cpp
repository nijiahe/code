#include "MyDelegate.h"
#include <QComboBox>


QWidget *MyDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QComboBox * combo = new QComboBox(parent);
    combo->addItem("1班");
    combo->addItem("2班");
    combo->addItem("3班");
    return combo;
}
