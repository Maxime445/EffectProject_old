#ifndef INPUTTILE_H
#define INPUTTILE_H

#include <QAudioDeviceInfo>
#include <QComboBox>

#include <movable.h>

class InputTile : public Movable
{
public:
    InputTile(QWidget* parentWindow);

    QComboBox* inputSelect;
    QLabel* test;
    void updateList(QList<QAudioDeviceInfo> newList); //CHANGEME this class is code-replicated.

private:
    QList<QAudioDeviceInfo> list;
};

#endif // INPUTTILE_H
