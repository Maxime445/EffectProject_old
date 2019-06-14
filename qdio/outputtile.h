#ifndef OUTPUTTILE_H
#define OUTPUTTILE_H

//#include <QObject>
//#include <QWidget>
#include <QAudioDeviceInfo>
#include <QComboBox>

#include <movable.h>
#include <effect.h>

class OutputTile : public Movable
{
    Q_OBJECT

public:
    OutputTile(QWidget* parentWindow);
    //~OutputTile();

    QComboBox* outputSelect;
    QLabel* test;
    void updateList(QList<QAudioDeviceInfo> newList);
    Effect getOutput();

signals:
    void effectAdded(Effect effect);
    void effectRemoved(Effect effect);

private:
     QList<QAudioDeviceInfo> list;
     Effect output;


private slots:
    //void on_outputSelect_currentIndexChanged(int index);
};

#endif // OUTPUTTILE_H
