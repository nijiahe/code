#include "MyTableModel.h"
#include <QDebug>

QVariant MyTableModel::data(const QModelIndex &idx, int role) const
{
    QVariant var = QSqlTableModel::data(idx,role);

    if(idx.column()==5)
    {
        if(var==1)
        {
            return "1班";
        }
        else if(var==2)
        {
            return "2班";
        }
        else if(var==3)
        {
            return "3班";
        }
    }



    return var;
}

bool MyTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(index.column()==5)
    {
        if(value=="1班")
        {
            return QSqlTableModel::setData(index,1,role);
        }
        else if(value=="2班")
        {
            return QSqlTableModel::setData(index,2,role);
        }
        else if(value=="3班")
        {
            return QSqlTableModel::setData(index,3,role);
        }
    }
    else
    {
        return QSqlTableModel::setData(index,value,role);
    }


}
