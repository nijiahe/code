#include "Mywidget.h"

Mywidget::Mywidget(QWidget *parent) : QWidget(parent)
{
    QMediaPlayer * media = new QMediaPlayer;
    media->setMedia(QUrl::fromLocalFile("D:/shawu.avi"));
    media->play();
    media->setParent(this);
}
