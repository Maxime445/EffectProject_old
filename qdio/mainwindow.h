#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QAudioDeviceInfo>
#include <QAudio>
#include <QAudioInput>
#include <QAudioOutput>
#include <QSettings>

#include "devices.h"
#include "effectbuffer.h"

#define DEBUG 1


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QSettings settings;

private:
#if DEBUG == 1
    void testCode();
    QAudioDeviceInfo input;
    QAudioDeviceInfo output;

#endif
    Devices devices;

    Ui::MainWindow *ui;
    void setupMenuBar();
    void setupAudio();
    void setupBuffer();
    void setupDevicesSelect();

    QAction *toggleSettingsButton;
    QAction *toggleRecordingButton;
    QAction *toggleEffectsCreatorButton;
    QAction *toggleEffectsNavigatorButton;
    void toggleSettings();
    void toggleRecording();
    void toggleEffectsCreator();
    void toggleEffectsNavigator();

    QAudioInput* audioIn;
    QAudioOutput* audioOut;
    QAudioFormat format;
    EffectBuffer buffer;

protected:
private slots:
    void on_inputdevices_currentIndexChanged(int index);
    void on_streamButton_clicked();
    void on_outputdevices_currentIndexChanged(int index);
};

#endif // MAINWINDOW_H
