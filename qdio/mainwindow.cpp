#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QDesktopWidget>

/*
 *  TODO:
 * -Connections between effects
 * -Create Fundamental operations effects
 * -Combine Effects into more effects
 * -Input/Output audio, etc
 * -Buffer implementation/audio implementation
 * -Tools, etc. E.G: Recording, Recordings
*/

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QCoreApplication::setApplicationName("QDIO Effects Creator");
    QCoreApplication::setOrganizationName("QDIO MUSIC TECHNOLOGIES LTD.");
    //QCoreApplication::setOrganizationDomain()

    //Set up UI
    ui->setupUi(this);

    setupMenuBar();



/*
    Movable* testMovable = new Movable(this);
    //TODO work on proper layout of these custom widgets.

    this->layout()->addWidget(testMovable);
    testMovable->setObjectName("testMovable");
    testMovable->show();
*/
    qDebug() << "Running test code!";
    testCode();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupAudio(){
    //TODO write existence check and necessary actions.

    QAudioInput audioIn(devices.getInputDevice(), devices.getInputFormat());
    QAudioOutput audioOut(devices.getOutputDevice(), devices.getOutputFormat()); //CHANGEME
}

void MainWindow::setupBuffer(){
    EffectBuffer buffer{};
    buffer.open(QIODevice::ReadWrite);
}

void MainWindow::setupMenuBar(){

    toggleSettingsButton = new QAction("Settings");
    ui->mainToolBar->addAction(toggleSettingsButton);
    connect(toggleSettingsButton, &QAction::triggered, this, &MainWindow::toggleSettings);

    toggleRecordingButton = new QAction("Recording");
    ui->mainToolBar->addAction(toggleRecordingButton);
    connect(toggleRecordingButton, &QAction::triggered, this, &MainWindow::toggleRecording);

    toggleEffectsCreatorButton = new QAction("Creator Toolbox");
    ui->mainToolBar->addAction(toggleEffectsCreatorButton);
    connect(toggleEffectsCreatorButton, &QAction::triggered, this, &MainWindow::toggleEffectsCreator);

    toggleEffectsNavigatorButton = new QAction("Effects Navigator");
    ui->mainToolBar->addAction(toggleEffectsNavigatorButton);
    connect(toggleEffectsNavigatorButton, &QAction::triggered, this, &MainWindow::toggleEffectsNavigator);
}

void MainWindow::setupDevicesSelect(){
    QList<QAudioDeviceInfo> inList(QAudioDeviceInfo::availableDevices(QAudio::AudioInput));
    QList<QAudioDeviceInfo>::iterator i;
    for (i = inList.begin(); i != inList.end(); ++i){
        ui->inputdevices->addItem(i->deviceName());
    }

    QList<QAudioDeviceInfo> outList(QAudioDeviceInfo::availableDevices(QAudio::AudioOutput));
    for (i = outList.begin(); i != outList.end(); i++){
        ui->outputdevices->addItem(i->deviceName());
    }
}

void MainWindow::toggleSettings(){
    if(ui->settings->isVisible()){
        ui->settings->hide();
    } else {
        ui->settings->show();
    }
}
void MainWindow::toggleRecording(){
    if(ui->recording->isVisible()){
        ui->recording->hide();
    } else {
        ui->recording->show();
    }
}
void MainWindow::toggleEffectsCreator(){
    if(ui->creator->isVisible()){
        ui->creator->hide();
    } else {
        ui->creator->show();
    }
}
void MainWindow::toggleEffectsNavigator(){
    if(ui->navigator->isVisible()){
        ui->navigator->hide();
    } else {
        ui->navigator->show();
    }
}

void MainWindow::on_inputdevices_currentIndexChanged(int index)
{
    inSelectIndex = index;
    /*
    input = QAudioDeviceInfo(QAudioDeviceInfo::availableDevices(QAudio::AudioInput).at(index));
    QAudioFormat inputFormat = input.nearestFormat(format);
    audioIn = new QAudioInput(input, inputFormat, this);
    qDebug() << "Input Device changed. Now set to: " << input.deviceName();*/
}

void MainWindow::on_outputdevices_currentIndexChanged(int index)
{
    outSelectIndex = index;
    /*
    output = QAudioDeviceInfo(QAudioDeviceInfo::availableDevices(QAudio::AudioOutput).at(index));
    QAudioFormat outputFormat = output.nearestFormat(format);
    audioOut = new QAudioOutput(output, outputFormat, this);
    qDebug() << "Output Device changed. Now set to: " << output.deviceName();*/
}

void MainWindow::on_streamButton_clicked()
{

    input = QAudioDeviceInfo(QAudioDeviceInfo::availableDevices(QAudio::AudioInput).at(inSelectIndex));
    output = QAudioDeviceInfo(QAudioDeviceInfo::availableDevices(QAudio::AudioOutput).at(outSelectIndex));

    audioIn = new QAudioInput(input, input.nearestFormat(format), this);
    audioOut = new QAudioOutput(output, output.nearestFormat(format), this);

    audioIn->reset();
    audioOut->reset();
    audioIn->start(&buffer);
    audioOut->start(&buffer);

}

void MainWindow::testCode()
{
    format.setSampleRate(44000);
    format.setChannelCount(1);
    format.setSampleSize(1);
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleSize(QAudioFormat::UnSignedInt);

    setupDevicesSelect();

    buffer.open(QIODevice::ReadWrite);
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    pressedChild = childAt(event->pos());

    if (pressedChild == this->centralWidget()) {
        pressedChild = 0;
        qDebug() << "Pressed central widget";
        //CHANGEME this does not work. Selection of the mainwindow crashes the program when moved/released.
        event->setAccepted(false);
        return;
    }
    qDebug() << "Mouse press: " << pressedChild->objectName();

};

void MainWindow::mouseMoveEvent(QMouseEvent* event) {
    pressedChild->move(event->pos());
}
void MainWindow::mouseReleaseEvent(QMouseEvent *event) {
    qDebug() << "Mouse release MainWindow";
    pressedChild = 0;
};

void MainWindow::on_pushButton_pressed()
{
    // Create new output tile
    OutputTile *outputTile = new OutputTile(this->centralWidget());

    //Probably want to move "adding to central widget" and placement actions here rather than in the class.


    outputTile->updateList(QAudioDeviceInfo::availableDevices(QAudio::AudioInput));


}
