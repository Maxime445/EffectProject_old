#ifndef LINK_H
#define LINK_H

#include <QObject>
#include <QWidget>

class Link : public QWidget
{
    Q_OBJECT
public:
    explicit Link(QWidget *parent = nullptr);



signals:
    //Movable connect(Link link); //Signal emitted when connection is made. (possibly called from movable)

public slots:
    //Movable connected(Link link); //Slot called when connection is made. (test / open buffer)
};

#endif // LINK_H
