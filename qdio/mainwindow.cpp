#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QCoreApplication::setApplicationName("qdio");
    QCoreApplication::setOrganizationName("QDIO MUSIC TECHNOLOGIES LTD.");
    //QCoreApplication::setOrganizationDomain()

    //Setup
    ui->setupUi(this);

    setupMenuBar();
}

MainWindow::~MainWindow()
{
    delete ui;
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
