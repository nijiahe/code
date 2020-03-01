#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>

class MyTableModel;
class QTableView;

class MyWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MyWidget(QWidget *parent = nullptr);


    QTableView * _tableview;
    MyTableModel * _model;
signals:

public slots:
    void slotSubmitButton();
    void slotDelButton();
    void slotAddButton();
};

#endif // MYWIDGET_H
