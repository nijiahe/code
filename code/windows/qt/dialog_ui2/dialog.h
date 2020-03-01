#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include<QString>
namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private:
    Ui::Dialog *ui;
    int x;
    int y;
};

#endif // DIALOG_H
