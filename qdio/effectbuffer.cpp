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


    validElementStart = 0;
    validElementEnd = 0;
    /*
    qDebug() << "buffer data as read by readPointer: " << *readPointer;

    int8_t data[12] = {'r','e','t','a','r','d'};
    memcpy(writePointer, data, 6);
    qDebug() << "buffer data after operation: " << *readPointer;
    */
}

qint64 EffectBuffer::readData(char* data, qint64 maxlen)
{
    //WARNING check whether readData and writeData are safe to access and modify common variables.
    if (maxlen >= (buffer.size() - validElementStart)){
        // Cutoff and circular loop scenario
        qint64 readEnd = qMin(validElementEnd, validElementStart + maxlen - buffer.size());
        qint64 readStart = validElementStart;
        qint64 length1 = buffer.size() - readStart;
        qint64 length2 = readEnd;

        memcpy(data, buffer.constData() + readStart, length1); //WARNING is this reference syntax ok?
        memcpy(data, buffer.constData(), length2);

        validElementStart = length2;
        //validElementEnd is either equal to validElementStart, or greater and thus untouched. Stays the same in both cases.

        return length1 + length2;
    } else {
        // Normal read scenario
        qint64 readEnd = qMin(validElementEnd, validElementStart + maxlen);
        qint64 readStart = validElementStart; // Should really be equal to validElementStart.
        qint64 length = readEnd - readStart;

        memcpy(data, buffer.constData() + readStart, length);

        validElementStart = readStart + length;
        //validElementEnd is either equal to validElementStart, or greater and thus untouched. Stays the same in both cases.

        return length;
    }
}



#ifdef TESTMODE
#else
qint64 EffectBuffer::writeData(const char* data, qint64 maxlen)
{
    //WARNING - add check to see if valid, unread data is overwritten. This hopefully should not be the case.
    if ((int)maxlen >= (buffer.size() - validElementEnd)){
        // Cutoff and loop scenario
        qint64 writeStart = validElementEnd;
        qint64 writeEnd = writeStart + maxlen - buffer.size();
        if (writeEnd >= validElementStart) qWarning() << "Warning: Valid data has been overwritten!";
        qint64 length1 = buffer.size() - writeStart;
        qint64 length2 = writeEnd;

        memcpy(buffer.data() + writeStart, data, length1);
        memcpy(buffer.data(), data + length1, length2);

        validElementEnd = writeEnd;

        return length1 + length2;

    } else {
        // Normal write scenario
        qint64 writeStart = validElementEnd;
        qint64 writeEnd = writeStart + maxlen;
        if (writeEnd >= validElementStart) qWarning() << "Warning: Valid data has been overwritten!";
        qint64 length = writeEnd - writeStart;

        memcpy(buffer.data() + writeStart, data, length);

        validElementEnd = writeEnd;

        return maxlen;
    }
}
#endif
