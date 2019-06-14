#include "outputtile.h"
#include <QDebug>
#include <mainwindow.h>

OutputTile::OutputTile(QWidget *parentWindow) : Movable(parentWindow)
{
    qDebug() << "Output tile initialisation";

    outputSelect = new QComboBox(parentWindow);
    test = new QLabel("out", parentWindow);
    layout->addWidget(test);
    layout->addWidget(outputSelect);
    QList<QAudioDeviceInfo> list;

    QObject::connect(this, SIGNAL(&OutputTile::effectAdded),
                        parentWindow, SLOT(&MainWindow::effectAdded));


    output = Effect(output = true);
    effectAdded(output);
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

Effect OutputTile::getOutput(){
    return output;
}
