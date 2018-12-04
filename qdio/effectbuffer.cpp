#include "effectbuffer.h"


EffectBuffer::EffectBuffer()
{
    readPointer = buffer.constData();
    writePointer = buffer.data();
}

qint64 EffectBuffer::readData(char* data, qint64 maxlen)
{
    /*
     *  Keep separate markers on the read and write. Update each accordingly, and find a way to make it circular, if it's larger than x reset to 0.
    */

    int length = qMin(buffer.length(), (int) maxlen);

    if (readPointer > buffer.constData()+buffer.length()) {
        readPointer = buffer.constData();
    } else {
        readPointer += length;
    }

    memcpy(data, readPointer, length);
    //WARNING "reset" code. Check if this works.


    return length;
}

qint64 EffectBuffer::writeData(const char* data, qint64 maxlen)
{
    memcpy(buffer.data(), data, maxlen);
    return maxlen;
}
