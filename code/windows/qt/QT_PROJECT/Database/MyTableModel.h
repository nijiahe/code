#ifndef MYTABLEMODEL_H
#define MYTABLEMODEL_H


#include <QSqlTableModel>

class MyTableModel : public QSqlTableModel
{
public:
    QVariant data(const QModelIndex &idx, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
};

#endif // MYTABLEMODEL_H
