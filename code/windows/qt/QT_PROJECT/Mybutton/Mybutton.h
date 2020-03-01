#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QWidget>


class Mybutton : public QWidget
{
    Q_OBJECT
public:
    explicit Mybutton(QWidget *parent = 0);
    explicit Mybutton(const QString &text,QWidget * parent =0);
    void paintEvent(QPaintEvent *);

    void mousePressEvent(QMouseEvent *) override;
    void mouseReleaseEvent(QMouseEvent *) override;



    QRect _rect;
    QString _text;

    bool _IsPressed=false;
signals://#define signals public
    void clicked();

public slots:
    void slotMybuttonClicked();
};

#endif // MYBUTTON_H
