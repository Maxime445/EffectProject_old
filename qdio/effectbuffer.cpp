#include "effectbuffer.h"



EffectBuffer::EffectBuffer()
{
    buffer = QByteArray(30000,0xFF); //16384 is tested maxlen.

#ifdef TESTMODE
    //test buffer data: sin wave
    testBuffer = QByteArray(30000, 0xFF);
    for (uint i = 0; i < buffer.size(); i++){
        testBuffer[i] = qSin(((double) i) / 10) * 0xff;
    }
#endif


    readPointer = buffer.data();
    writePointer = buffer.data();
    writePointerElement = 0;
    readPointerElement = 0;
    /*
    qDebug() << "buffer data as read by readPointer: " << *readPointer;

    int8_t data[12] = {'r','e','t','a','r','d'};
    memcpy(writePointer, data, 6);
    qDebug() << "buffer data after operation: " << *readPointer;
    */
}

qint64 EffectBuffer::readData(char* data, qint64 maxlen)
{
    if (maxlen >= (buffer.size() - readPointerElement)){
        //read, with cutoff and circular loop.
        size_t overflow = (maxlen+readPointerElement) - buffer.size();
        memcpy(data, readPointer, (buffer.size() - readPointerElement));
        readPointer = buffer.data();
        mempcpy(data, readPointer, overflow);
        readPointer = &(readPointer[overflow]);
        readPointerElement = overflow;
    } else {
        //read normally.
        memcpy(data, readPointer, maxlen);
        readPointer = &(readPointer[maxlen]);
        readPointerElement += maxlen;
        qDebug() << "Pointer end at " << readPointerElement;
    }
    return maxlen;
}



#ifdef TESTMODE
qint64 EffectBuffer::writeData(const char* data, qint64 maxlen)
{

    //WARNING: "data" simply replaced by "testBuffer". data may not always be the same, while testBuffer will be.
    //WARNING: no "written to" check?
    if ((int)maxlen >= (buffer.size() - writePointerElement)){
        //write with cutoff and circular loop
        size_t overflow = (maxlen + writePointerElement) - buffer.size();
        memcpy(writePointer, testBuffer, (buffer.size() - writePointerElement));
        writePointer = buffer.data();
        mempcpy(writePointer, testBuffer, overflow);
        writePointer = &(writePointer[overflow]);
        validElementStart = writePointerElement;
        writePointerElement = overflow;
        validElementEnd = writePointerElement;
    } else {
        memcpy(writePointer, testBuffer, maxlen);
        writePointer = &(writePointer[maxlen]);
        validElementStart = writePointerElement;
        writePointerElement += maxlen;
        validElementEnd = writePointerElement;

    }
    return maxlen;
}
#else
qint64 EffectBuffer::writeData(const char* data, qint64 maxlen)
{
    //WARNING: no "written to" check?
    if ((int)maxlen >= (buffer.size() - writePointerElement)){
        //write with cutoff and circular loop
        size_t overflow = (maxlen + writePointerElement) - buffer.size();
        memcpy(writePointer, data, (buffer.size() - writePointerElement));
        writePointer = buffer.data();
        mempcpy(writePointer, data, overflow);
        writePointer = &(writePointer[overflow]);
        validElementStart = writePointerElement;
        writePointerElement = overflow;
        validElementEnd = writePointerElement;
    } else {
        memcpy(writePointer, data, maxlen);
        writePointer = &(writePointer[maxlen]);
        validElementStart = writePointerElement;
        writePointerElement += maxlen;
        validElementEnd = writePointerElement;

    }
    return maxlen;
}
#endif
