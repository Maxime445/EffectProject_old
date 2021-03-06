#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QAudioDeviceInfo>
#include <QAudio>
#include <QAudioInput>
#include <QAudioOutput>
#include <QSettings>
#include <QMouseEvent>
#include <QSizePolicy>

#include "devices.h"
#include "effectbuffer.h"
#include "movable.h"
#include "outputtile.h"
#include "inputtile.h"

#define DEBUG 1


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
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

    int outSelectIndex;
    int inSelectIndex;

    QList<Effect>* EffectsChain; // Single chain of effects.

    QAudioInput* audioIn;
    QAudioOutput* audioOut;
    QAudioFormat format;
    //Should not only have one.
    EffectBuffer buffer;

    QWidget* pressedChild = 0;

  
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    bool dragAndDroppable(QMouseEvent *event);
    bool dragging = false;
    QPoint pressedLocation;


private slots:
    void effectAdded();
    void effectRemoved();

    void on_inputdevices_currentIndexChanged(int index);
    void on_streamButton_clicked();
    void on_outputdevices_currentIndexChanged(int index);
    void on_outputTileButton_pressed();
    void on_inputTileButton_pressed();
};

#endif // MAINWINDOW_H
