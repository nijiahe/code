#ifndef CHOOSEINTERFACE_H
#define CHOOSEINTERFACE_H

#include <QDialog>
#include <QComboBox>
#include <QPushButton>


class ChooseInterface : public QDialog
{
    Q_OBJECT
public:
    explicit ChooseInterface(QWidget *parent=0);

    QComboBox * _combobox;
    QPushButton * _button;
    QString _ipstr;
signals:

public slots:
    void slotButtonClieked();
};

#endif // CHOOSEINTERFACE_H
