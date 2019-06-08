#include "inputtile.h"
#include <QDebug>

InputTile::InputTile(QWidget* parentWindow) : Movable(parentWindow)
{
    qDebug() << "Input tile initialisation";

    inputSelect = new QComboBox(parentWindow);
    test = new QLabel("in", parentWindow);


    layout->addWidget(test);
    layout->addWidget(inputSelect);
    QList<QAudioDeviceInfo> list;
}

void InputTile::updateList(const QList<QAudioDeviceInfo> newList){
    //TODO same as in output tile. Trigger updateList() on output devices signal.
    if (!list.isEmpty()){
        list.clear();
    }

    QList<QAudioDeviceInfo>::const_iterator i;
    for (i = newList.begin(); i != newList.end(); ++i){
        //WARNING No existing check implemented. Just replacement
        list.append(*i);
        inputSelect->addItem(i->deviceName());
        //ui->inputdevices->addItem(i->deviceName());
    }

    if (!list.isEmpty()){
        inputSelect->show();
    }
}
