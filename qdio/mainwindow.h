#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAudioDeviceInfo>
#include <QAudio>
#include <QAudioInput>
#include <QAudioOutput>
#include <QSettings>

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
    Ui::MainWindow *ui;
    void setupMenuBar();

    QAction *toggleSettingsButton;
    QAction *toggleRecordingButton;
    QAction *toggleEffectsCreatorButton;
    QAction *toggleEffectsNavigatorButton;
    void toggleSettings();
    void toggleRecording();
    void toggleEffectsCreator();
    void toggleEffectsNavigator();


protected:
};

#endif // MAINWINDOW_H
