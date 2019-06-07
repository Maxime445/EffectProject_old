#ifndef MOVABLE_H
#define MOVABLE_H

#include <QObject>
#include <QWidget>
#include <QMouseEvent>
#include <QDrag>
#include <QMimeData>
#include <QDropEvent>
#include <QApplication>
#include <QHBoxLayout>
#include <QEvent>
#include <link.h>
#include <QLabel>
#include <QGroupBox>
#include <QGridLayout>

class Movable : public QWidget
{
    Q_OBJECT

public:
    Movable(QWidget* parentWindow = nullptr);

protected:
    void updateLayout();

    QGroupBox* movableBox;
    QGridLayout* layout;


private:

    bool dragging = false;
    QPoint dragStartPosition;
    QList<Link> links;

};

#endif // MOVABLE_H
