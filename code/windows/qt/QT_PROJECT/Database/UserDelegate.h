#ifndef USERDELEGATE_H
#define USERDELEGATE_H

#include <QItemDelegate>

class UserDelegate : public QItemDelegate
{
public:
    QWidget *createEditor(QWidget *parent,
                          const QStyleOptionViewItem &option,
                          const QModelIndex &index) const override;
};

#endif // USERDELEGATE_H
