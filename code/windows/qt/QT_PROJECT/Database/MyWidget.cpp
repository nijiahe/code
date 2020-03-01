#include "MyWidget.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QSqlRecord>
#include <QTableView>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QMessageBox>

#include "MyTableModel.h"
#include "MyDelegate.h"
#include "ReadOnlyDelegate.h"
#include "UserDelegate.h"

#include <QDebug>

MyWidget::MyWidget(QWidget *parent) : QWidget(parent)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setUserName("root");
    db.setPassword("a512666#asdf");
    db.setDatabaseName("mydb1");
    if(db.open()==false)
    {
        qDebug()<<"error"<<db.lastError().text();
        exit(0);
    }
    //QSqlTableModel是QSqlQueryModel的子类,QSqlQueryModel用select语句获取数据,是只读的
    _model = new MyTableModel;

    _model->setTable("student");
    _model->select();

    //change tittle
    _model->setHeaderData(0,Qt::Horizontal,"编号");
    _model->setHeaderData(1,Qt::Horizontal,"姓名");
    _model->setHeaderData(2,Qt::Horizontal,"语文");
    _model->setHeaderData(3,Qt::Horizontal,"英语");
    _model->setHeaderData(4,Qt::Horizontal,"数学");
    _model->setHeaderData(5,Qt::Horizontal,"班级");

    //show datebase
    _tableview = new QTableView;
    _tableview->setModel(_model);

    //hide any column,now is hide id
    _tableview->hideColumn(0);

    //set delegate 修改方式变为复选框
    //_tableview->setItemDelegateForColumn(5,new MyDelegate);
    //设置第一列只读
    //_tableview->setItemDelegateForColumn(1,new ReadOnlyDelegate);
    _tableview->setItemDelegate(new UserDelegate);

    QVBoxLayout * lay = new QVBoxLayout(this);
    lay->addWidget(_tableview);

    /*
    QSqlTableModel::OnFieldChange
    0
    模型的任何更改将立即更新到数据库
    QSqlTableModel::OnRowChange
    1
    当用户选择不同的行时，将应用对行（改动过的行）的更改
    QSqlTableModel::OnManualSubmit
    2
    所有更改将在模型中缓存，直到submitAll() 或者 revertAll() 被调用。
    */
    QHBoxLayout * hbox = new QHBoxLayout;
    hbox->addStretch();
    lay->addLayout(hbox);


    //提交
    _model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    QPushButton * button = new QPushButton("提交");
    hbox->addWidget(button);
    connect(button,SIGNAL(clicked()),this,SLOT(slotSubmitButton()));

    //删除
    QPushButton * del = new QPushButton("删除行");
    hbox->addWidget(del);
    connect(del,SIGNAL(clicked()),this,SLOT(slotDelButton()));

    //添加一行
    QPushButton * add = new QPushButton("添加行");
    hbox->addWidget(add);
    connect(add,SIGNAL(clicked()),this,SLOT(slotAddButton()));

}

void MyWidget::slotSubmitButton()
{
    //if failed
    if(!_model->submitAll())
    {
        QMessageBox::critical(this,"error",QSqlDatabase::database().lastError().text());
        _model->database().rollback();
    }
    else
    {
        qDebug()<<"submit success";
        _model->database().commit();
    }
}

void MyWidget::slotDelButton()
{
    //选中了哪些
    QItemSelectionModel * selectModel = _tableview->selectionModel();
    QModelIndexList selectlist = selectModel->selectedIndexes();
    for(int i=0;i<selectlist.length();i++)
    {
        QModelIndex index = selectlist.at(i);
        _model->removeRow(index.row());
    }

    _model->submitAll();
}

void MyWidget::slotAddButton()
{
    _model->database().transaction();

    QSqlRecord record = _model->record();
    _model->insertRecord(-1,record);
}



