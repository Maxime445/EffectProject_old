#include "devices.h"


devices::devices()
{
   //Devices List
   InputDevices = QAudioDeviceInfo::availableDevices(QAudio::Mode::AudioInput);
   OutputDevices = QAudioDeviceInfo::availableDevices(QAudio::Mode::AudioOutput);

   //Default Devices
   QSettings settings;
   if (settings.value("Default Input Device").isValid()){
       Input = settings.value("Default Input Device").value<QAudioDeviceInfo>();
   } else {
       setInputDevice(QAudioDeviceInfo::defaultInputDevice());
   }

   if (settings.value("Default Output Device").isValid()){
       Output = settings.value("Default Output Device").value<QAudioDeviceInfo>();
   } else {
       setOutputDevice(QAudioDeviceInfo::defaultOutputDevice());
   }

   //Verify compatability of defaults well.

}

void devices::setInputDevice(QAudioDeviceInfo device){
    Input = device;
    // Set settings up:
    //settings.setValue("Default Input Device", )
}

void devices::setOutputDevice(QAudioDeviceInfo device){
    Output = device;
    // Set settings up:
    //settings.setValue("Default Output Device", )
}


