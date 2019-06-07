#ifndef OUTPUTTILE_H
#define OUTPUTTILE_H

//#include <QObject>
//#include <QWidget>
#include <QAudioDeviceInfo>
#include <QComboBox>

#include <movable.h>

class OutputTile : public Movable
{
public:
    OutputTile(QWidget* parentWindow);

    QComboBox* outputSelect;
    QLabel* test;
    void updateList(QList<QAudioDeviceInfo> newList);

private:
     QList<QAudioDeviceInfo> list;
};

#endif // OUTPUTTILE_H
