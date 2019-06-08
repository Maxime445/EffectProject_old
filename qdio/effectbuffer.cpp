#include "effectbuffer.h"


//TODO sort out conversions!!!
//TODO sort out multiple instances. Including switching streams etc.
EffectBuffer::EffectBuffer()
{
    buffer2 = QByteArray(50000,0xFF);
    buffer = QByteArray();

    validElementStart = 0;
    validElementEnd = 0;


    connect(this, &EffectBuffer::bytesWritten, this, &EffectBuffer::applyEffects);
}

qint64 EffectBuffer::readData(char* data, qint64 maxlen){
    int readLength = qMin(static_cast<int>(maxlen), buffer.length());
    qDebug() << "Maxlen: " << maxlen << ", readLength: " << readLength;
    //  can chopped data be const? linear time -> constant time (?)

    memcpy(data, buffer.data(), static_cast<size_t>(readLength));
    buffer.remove(0, readLength);

    return readLength;
}

qint64 EffectBuffer::writeData(const char* data, qint64 maxlen){
    if(maxlen > (buffer.capacity() + buffer.size())){
        //  Increase buffer capacity to new maximum.
        qint64 newCap = buffer.size() + maxlen;
        qDebug() << "Extending size to: " << newCap;
        buffer.reserve(newCap);
    }

    buffer.append(data, static_cast<int>(maxlen));
    //qDebug() << buffer.contains(data);
    return maxlen;
}
#ifdef circularbuffer

qint64 EffectBuffer::readData(char* data, qint64 maxlen)
{
    //WARNING check whether readData and writeData are safe to access and modify common variables.
    qDebug() << "ReadData: Start: " << validElementStart << " End: " << validElementEnd;
    if (
            (validElementEnd < validElementStart) &&
            (maxlen > buffer2.size() - validElementStart)
            ){
        // Cutoff and circular loop scenario
        qDebug() << "Read with loopback.";
        qint64 readEnd = qMin(validElementEnd, validElementStart + maxlen - buffer2.size());
        qint64 readStart = validElementStart;
        qint64 length1 = buffer2.size() - readStart;
        qint64 length2 = readEnd;

        //TODO would it be better to use QByteArray's own methods to do this? probably.
        memcpy(data, buffer2.constData() + readStart, length1); //WARNING is this reference syntax ok?
        memcpy(data + length1, buffer2.constData(), length2);

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

        //TODO same as above.
        memcpy(data, buffer2.constData() + readStart, length);

        //qDebug() << "  r: " << readEnd;
        validElementStart = readEnd;
        //validElementEnd is either equal to validElementStart, or greater and thus untouched. Stays the same in both cases.

        return length;
    }
}


qint64 EffectBuffer::writeData(const char* data, qint64 maxlen)
{
    //WARNING - add check to see if valid, unread data is overwritten. This hopefully should not be the case.
    qDebug() <<  "WriteData: Start: " << validElementStart << " End: " << validElementEnd;
    if (maxlen >= (buffer2.size() - validElementEnd)){
        // Cutoff and loop scenario
        qint64 writeStart = validElementEnd;
        qint64 writeEnd = writeStart + maxlen - buffer2.size();
        //if (writeEnd >= validElementStart) qWarning() << "Warning: Valid data has been overwritten!";
        qint64 length1 = buffer2.size() - writeStart;
        qint64 length2 = writeEnd;

        //TODO same as above.
        memcpy(buffer2.data() + writeStart, data, length1);
        memcpy(buffer2.data(), data + length1, length2);

        //qDebug() << "  w: " << writeEnd;
        validElementEnd = writeEnd;

        return length1 + length2;

    } else {
        // Normal write scenario
        qint64 writeStart = validElementEnd;
        qint64 writeEnd = writeStart + maxlen;
        //if (writeEnd >= validElementStart) qWarning() << "Warning: Valid data has been overwritten!";
        qint64 length = writeEnd - writeStart;

        //TODO same as above.
        memcpy(buffer2.data() + writeStart, data, length);

        //qDebug() << "  w: " << writeEnd;
        validElementEnd = writeEnd;

        return maxlen;
    }
}
#endif



void EffectBuffer::applyEffects(qint64 bytes){
    int applied = validElementEnd - bytes;
    //CHANGEME loopback compatibility
    //loop through bytes
    while (applied <= bytes){
        //loop through effects
        buffer2[applied] = buffer2.at(applied);
        applied++;
    }
}

