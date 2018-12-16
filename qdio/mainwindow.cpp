#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QCoreApplication::setApplicationName("qdio");
    QCoreApplication::setOrganizationName("QDIO MUSIC TECHNOLOGIES LTD.");
    //QCoreApplication::setOrganizationDomain()

    //Set up UI
    ui->setupUi(this);
    setupMenuBar();

#if DEBUG == 1
    /*
     * TEST CODE
     */
    qDebug() << "Running test code!";
    testCode();
#else

    /*
     * IMPLEMENTATION CODE
     */

    //Set Up Audio
    Devices devices;

    setupAudio();
    setupBuffer();

    setupDevicesSelect();

#endif
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
    input = QAudioDeviceInfo(QAudioDeviceInfo::availableDevices(QAudio::AudioInput).at(index));

    QAudioFormat inputFormat = input.nearestFormat(format);
    audioIn = new QAudioInput(input, inputFormat, this);
    qDebug() << "Input Device changed. Now set to: " << input.deviceName();
}

void MainWindow::on_outputdevices_currentIndexChanged(int index)
{
    output = QAudioDeviceInfo(QAudioDeviceInfo::availableDevices(QAudio::AudioOutput).at(index));
    QAudioFormat outputFormat = output.nearestFormat(format);
    audioOut = new QAudioOutput(output, outputFormat, this);
    qDebug() << "Output Device changed. Now set to: " << output.deviceName();
}

void MainWindow::on_streamButton_clicked()
{
    if (!input.isNull() && !output.isNull()){
        audioIn->reset();
        audioOut->reset();
        audioIn->start(&buffer);
        audioOut->start(&buffer);

    } else {
        qDebug() << "Input or output not set!";
    }


    /*
    //TODO add check to make sure everything is alright.

    audioIn.start(&buffer);
    audioOut.start(&buffer);


    ui->streamButton->setFlat(true);
    */
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

