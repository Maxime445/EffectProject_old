#include "movable.h"
#include <QPushButton>
#include <QRect>
#include <QLabel>
#include <QDebug>

Movable::Movable(QWidget *parentWindow) : QWidget(parentWindow)
{
    //Creates movable of default size to start with.
    qDebug() << "Movable initialisation";


    QPoint pt(100,100);
    QSize size(100, 200);
    QRect rect(pt, size);

    movableBox = new QGroupBox("Test", parentWindow);
    movableBox->setObjectName("MovableBox");
    movableBox->setTitle("Movable");
    movableBox->setGeometry(rect);

    layout = new QGridLayout(this->window());
    movableBox->setLayout(layout);

    movableBox->show();

    setEnabled(true);
}


void Movable::updateLayout(){
    movableBox->setLayout(layout);
}

