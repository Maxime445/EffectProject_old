#include "devices.h"
//test bigpenis
// l a r g g   p e n i s


//"settings" unimplemented
Devices::Devices()
{
    // Devices List
    inputDevices = QAudioDeviceInfo::availableDevices(QAudio::Mode::AudioInput);
    outputDevices = QAudioDeviceInfo::availableDevices(QAudio::Mode::AudioOutput);

    // Default Devices

    // Without using settings
    setInputDevice(QAudioDeviceInfo::defaultInputDevice());
    setOutputDevice(QAudioDeviceInfo::defaultOutputDevice());

    //TODO Add real format preferences, using settings
    inputFormat = input.preferredFormat();
    outputFormat = output.preferredFormat();

    outputFormat.setChannelCount(1);
    inputFormat.setChannelCount(1);
    outputFormat.setSampleRate(inputFormat.sampleRate());
    inputFormat.setCodec("audio/pcm");
    outputFormat.setCodec("audio/pcm");



    // Using Settings
    /*QSettings settings; //PROBABLY SHOULD NOT BE SETTING UP SETTINGS OVER HERE////////////
    if (settings.value("Default Input Device").isValid()){
       input = settings.value("Default Input Device").value<QAudioDeviceInfo>();
    } else {
       setInputDevice(QAudioDeviceInfo::defaultInputDevice());
    }

    if (settings.value("Default Output Device").isValid()){
       output = settings.value("Default Output Device").value<QAudioDeviceInfo>();
    } else {
       setOutputDevice(QAudioDeviceInfo::defaultOutputDevice());
    }

    //decide audio formats.
    //(Verify compatability of defaults well.)

    if (settings.value("Input Format").isValid()){
        inputFormat = settings.value("Input Format").value<QAudioFormat>();
    } else {
        inputFormat = input.preferredFormat();
    }

    if (settings.value("Output Format").isValid()){
        outputFormat = settings.value("Output Format").value<QAudioFormat>();
    } else {
        outputFormat = output.preferredFormat();
    }
    */

}

QAudioFormat Devices::getInputFormat(){
    return inputFormat;
}

QAudioFormat Devices::getOutputFormat(){
    return outputFormat;
}

QAudioDeviceInfo Devices::getInputDevice(){
    return input;
}

QAudioDeviceInfo Devices::getOutputDevice(){
    return output;
}

void Devices::setInputDevice(QAudioDeviceInfo device){
    input = device;
    // Set settings up:
    //settings.setValue("Default Input Device", )
}

void Devices::setOutputDevice(QAudioDeviceInfo device){
    output = device;
    // Set settings up:
    //settings.setValue("Default Output Device", )
}

QList<QAudioDeviceInfo>* Devices::getInputDevices(){
    return &inputDevices;
}

QList<QAudioDeviceInfo>* Devices::getOutputDevices(){
    return &outputDevices;
}

