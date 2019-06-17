#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QDesktopWidget>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QCoreApplication::setApplicationName("QDIO Effects Creator");
    QCoreApplication::setOrganizationName("QDIO MUSIC TECHNOLOGIES LTD.");

    //Set up UI command
    ui->setupUi(this);
    //Set up "Menu Bar" - buttons for windows
    setupMenuBar();



/*  //"Movable" test code... can delete.
 *
    Movable* testMovable = new Movable(this);
    //TODO work on proper layout of these custom widgets.

    this->layout()->addWidget(testMovable);
    testMovable->setObjectName("testMovable");
    testMovable->show();
*/

    //"Test Code" function -
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

///
/// \brief MainWindow::setupDevicesSelect
/// Create two list-menus, for input and output, and populate them with
/// QAudioDeviceInfo::availableDevices.
/// To be replaced with more complex input/output system.
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


///
/// \brief MainWindow::toggleSettings
/// Toggle "Settings" panel appearance
void MainWindow::toggleSettings(){
    if(ui->settings->isVisible()){
        ui->settings->hide();
    } else {
        ui->settings->show();
    }
}


///
/// \brief MainWindow::toggleRecording
/// Toggle "Recording" panel appearance
void MainWindow::toggleRecording(){
    if(ui->recording->isVisible()){
        ui->recording->hide();
    } else {
        ui->recording->show();
    }
}


///
/// \brief MainWindow::toggleEffectsCreator
/// Toggle "Effects Creator" panel appearance
void MainWindow::toggleEffectsCreator(){
    if(ui->creator->isVisible()){
        ui->creator->hide();
    } else {
        ui->creator->show();
    }
}

///
/// \brief MainWindow::toggleEffectsNavigator
/// Toggle "Effects Navigator" panel appearance
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
    // Configure default sample format
    format.setSampleRate(44000);
    format.setChannelCount(1);
    format.setSampleSize(1);
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleSize(QAudioFormat::UnSignedInt);

    // "Set up devices select
    setupDevicesSelect();

    buffer.open(QIODevice::ReadWrite);
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    if (dragAndDroppable(event))
        if  (childAt(event->pos())->objectName() == "horizontalLayoutWidget") {dragging = false;}
    {
        pressedChild = childAt(event->pos()); //TODO add filter for selected child widget
        pressedLocation = pressedChild->pos() - event->pos();
        qDebug() << "Mouse press: " << pressedChild->objectName();
    }

};


void MainWindow::mouseMoveEvent(QMouseEvent* event) {
     if (dragging) pressedChild->move(event->pos() + pressedLocation);
}



void MainWindow::mouseReleaseEvent(QMouseEvent *event) {
    pressedChild = 0;
    pressedLocation = QPoint(0,0);
    dragging = false;
}

///
/// \brief MainWindow::dragAndDroppable
/// \param event QMouseEvent passed from mousePress, mouseMove, mouseRelease, etc.
/// \return whether or not the position of mouse should incur a drag and drop
/// Checks the widget underneath mouse cursor position.
/// Incomplete - should add filters for all types
///
bool MainWindow::dragAndDroppable(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton){
        if (childAt(event->pos())->objectName() == "centralWidget"){
            qDebug() << "Central Widget selected.";
            dragging = false;
            return 0;
        }

        dragging = true;
        return 1;
    } else {
        dragging = false;
        return 0;
    }
}

///
/// \brief MainWindow::effectAdded
/// Slot for added "movable" effect created. Signal called in Movable class in constructor.
void MainWindow::effectAdded()
{
    //TODO Add effect to chain
    qDebug() << "Effect added.";
}

///
/// \brief MainWindow::effectRemoved
/// Slot for added "movable" effect removed. Signal called in Movable class in destructor.
void MainWindow::effectRemoved()
{
    //TODO Remove effect to chain

}

void MainWindow::on_pushButton_pressed()
{
    // Create new output tile
    OutputTile *outputTile = new OutputTile(this->centralWidget());
    //Probably want to move "adding to central widget" and placement actions here rather than in the class.

    outputTile->updateList(QAudioDeviceInfo::availableDevices(QAudio::AudioInput));
}



void MainWindow::on_pushButton_2_pressed()
{
    //Code replication from pushButton 1. (OutputTile)
    // Create new output tile
    InputTile *inputTile = new InputTile(this->centralWidget());

    //Probably want to move "adding to central widget" and placement actions here rather than in the class.
    inputTile->updateList(QAudioDeviceInfo::availableDevices(QAudio::AudioInput));
}


