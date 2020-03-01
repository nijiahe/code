#ifndef MYDELEGATE_H
#define MYDELEGATE_H

#include <QItemDelegate>

class MyDelegate : public QItemDelegate
{
public:
    QWidget *createEditor(QWidget *parent,
                          const QStyleOptionViewItem &option,
                          const QModelIndex &index) const override;


};

#endif // MYDELEGATE_H
