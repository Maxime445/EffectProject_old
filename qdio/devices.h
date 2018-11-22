#ifndef DEVICES_H
#define DEVICES_H

#include <QList>
#include <QAudioDeviceInfo>
#include <QSettings>

class devices
{
public:
    devices();
    void setInputDevice(QAudioDeviceInfo device);
    void setOutputDevice(QAudioDeviceInfo device);

private:
    QList<QAudioDeviceInfo> InputDevices;
    QList<QAudioDeviceInfo> OutputDevices;
    QAudioDeviceInfo Output;
    QAudioDeviceInfo Input;
    QSettings settings;

};

#endif // DEVICES_H
