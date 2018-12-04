#ifndef DEVICES_H
#define DEVICES_H

#include <QList>
#include <QAudioDeviceInfo>
#include <QSettings>

#define NUM_CIRCLE_BUFFER_ELEMENTS 50

class Devices
{
public:
    Devices();
    void setInputDevice(QAudioDeviceInfo device);
    void setOutputDevice(QAudioDeviceInfo device);
    QList<QAudioDeviceInfo>* getInputDevices();
    QList<QAudioDeviceInfo>* getOutputDevices();
    QAudioDeviceInfo getOutputDevice();
    QAudioDeviceInfo getInputDevice();
    QAudioFormat getInputFormat();
    QAudioFormat getOutputFormat();

private:
    QList<QAudioDeviceInfo> inputDevices;
    QList<QAudioDeviceInfo> outputDevices;
    QAudioDeviceInfo output;
    QAudioDeviceInfo input;
    QAudioFormat inputFormat;
    QAudioFormat outputFormat;
    //QSettings settings;



};

#endif // DEVICES_H
