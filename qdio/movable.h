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

class Movable : public QWidget
{
    Q_OBJECT

public:
    Movable(QWidget* parentWindow = 0);

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;



private:
    bool dragging = false;
    QPoint dragStartPosition;
    QList<Link> links;

};

#endif // MOVABLE_H
