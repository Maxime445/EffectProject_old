#include "outputtile.h"
#include <QDebug>

OutputTile::OutputTile(QWidget *parentWindow) : Movable(parentWindow)
{
    qDebug() << "Output tile initialisation";

    outputSelect = new QComboBox(parentWindow);
    test = new QLabel("test", parentWindow);
    layout->addWidget(test);
    layout->addWidget(outputSelect);
    QList<QAudioDeviceInfo> list;
}

void OutputTile::updateList(const QList<QAudioDeviceInfo> newList){
    //TODO trigger slot updateList() on output devices signal.
    if (!list.isEmpty()){
        list.clear();
    }


    QList<QAudioDeviceInfo>::const_iterator i;
    for (i = newList.begin(); i != newList.end(); ++i){
        //WARNING No existing check implemented. Just replacement
        list.append(*i);
        outputSelect->addItem(i->deviceName());
        //ui->inputdevices->addItem(i->deviceName());
    }

    if (!list.isEmpty()){
        outputSelect->show();
    }
}
