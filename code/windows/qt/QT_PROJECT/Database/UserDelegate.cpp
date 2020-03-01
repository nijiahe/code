#include "UserDelegate.h"
#include <QDebug>
#include <QComboBox>

QWidget *UserDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if(index.column()==1)
    {
        return nullptr;
    }
    else if(index.column()==5)
    {
        qDebug()<<"yes";
        QComboBox * combo = new QComboBox(parent);
        combo->addItem("1班");
        combo->addItem("2班");
        combo->addItem("3班");
        return combo;
    }
    else return QItemDelegate::createEditor(parent,option,index);
}
