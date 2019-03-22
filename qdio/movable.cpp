#include "movable.h"
#include <QPushButton>
#include <QRect>
#include <QLabel>
#include <QDebug>

Movable::Movable(QWidget *parentWindow) : QWidget(parentWindow)
{
    QLabel* test = new QLabel("test", this);

    parentWindow->layout()->addWidget(test);
    test->setAlignment(Qt::AlignmentFlag::AlignHCenter | Qt::AlignmentFlag::AlignVCenter);
    test->show();

    setEnabled(true);
}

void Movable::mousePressEvent(QMouseEvent* event){
    //event->setAccepted(true);
    qDebug() << "Mouse press Movable";
    if (event->button() == Qt::LeftButton){
        dragStartPosition = event->pos();
        dragging = true;
        qDebug() << "Started drag at: " << dragStartPosition;
    }
}



void Movable::mouseMoveEvent(QMouseEvent* event){
    qDebug() << "Mouse move Movable";
    if (dragging){
        QWidget* parentWindow = this->parentWidget();
        qDebug() << parentWindow->windowIconText();
    }
}

void Movable::mouseReleaseEvent(QMouseEvent* event){
    qDebug() << "Mouse release Movable";
}

