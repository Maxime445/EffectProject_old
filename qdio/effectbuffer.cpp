#include "effectbuffer.h"



EffectBuffer::EffectBuffer()
{
    buffer = QByteArray(50000,0xFF);

    validElementStart = 0;
    validElementEnd = 0;

    connect(this, &EffectBuffer::bytesWritten, this, &EffectBuffer::applyEffects);

    //Effects
    multiply = &multiplyF;
    max = &maxF;
}

qint64 EffectBuffer::readData(char* data, qint64 maxlen)
{
    //WARNING check whether readData and writeData are safe to access and modify common variables.
    qDebug() << "ReadData: Start: " << validElementStart << " End: " << validElementEnd;
    if (
            (validElementEnd < validElementStart) &&
            (maxlen > buffer.size() - validElementStart)
            ){
        // Cutoff and circular loop scenario
        qDebug() << "Read with loopback.";
        qint64 readEnd = qMin(validElementEnd, validElementStart + maxlen - buffer.size());
        qint64 readStart = validElementStart;
        qint64 length1 = buffer.size() - readStart;
        qint64 length2 = readEnd;

        memcpy(data, buffer.constData() + readStart, length1); //WARNING is this reference syntax ok?
        memcpy(data + length1, buffer.constData(), length2);

        //qDebug() << "  r: " << length2;
        validElementStart = length2;
        //validElementEnd is either equal to validElementStart, or greater and thus untouched. Stays the same in both cases.

        return length1 + length2;
    } else {
        // Normal read scenario
        qDebug() << "Normal Read.";
        qint64 readEnd = qMin(validElementEnd, validElementStart + maxlen);
        qint64 readStart = validElementStart; // Should really be equal to validElementStart.
        qint64 length = readEnd - readStart;

        memcpy(data, buffer.constData() + readStart, length);

        //qDebug() << "  r: " << readEnd;
        validElementStart = readEnd;
        //validElementEnd is either equal to validElementStart, or greater and thus untouched. Stays the same in both cases.

        return length;
    }
}



#ifdef TESTMODE
#else
qint64 EffectBuffer::writeData(const char* data, qint64 maxlen)
{
    //WARNING - add check to see if valid, unread data is overwritten. This hopefully should not be the case.
    qDebug() <<  "WriteData: Start: " << validElementStart << " End: " << validElementEnd;
    if (maxlen >= (buffer.size() - validElementEnd)){
        // Cutoff and loop scenario
        qint64 writeStart = validElementEnd;
        qint64 writeEnd = writeStart + maxlen - buffer.size();
        //if (writeEnd >= validElementStart) qWarning() << "Warning: Valid data has been overwritten!";
        qint64 length1 = buffer.size() - writeStart;
        qint64 length2 = writeEnd;

        memcpy(buffer.data() + writeStart, data, length1);
        memcpy(buffer.data(), data + length1, length2);

        //qDebug() << "  w: " << writeEnd;
        validElementEnd = writeEnd;

        return length1 + length2;

    } else {
        // Normal write scenario
        qint64 writeStart = validElementEnd;
        qint64 writeEnd = writeStart + maxlen;
        //if (writeEnd >= validElementStart) qWarning() << "Warning: Valid data has been overwritten!";
        qint64 length = writeEnd - writeStart;

        memcpy(buffer.data() + writeStart, data, length);

        //qDebug() << "  w: " << writeEnd;
        validElementEnd = writeEnd;

        return maxlen;
    }
}
#endif

void EffectBuffer::applyEffects(qint64 bytes){
    qint64 applied = validElementEnd - bytes;
    //CHANGEME loopback compatibility
    //loop through bytes
    while (applied <= bytes){
        //loop through effects
    }
}

