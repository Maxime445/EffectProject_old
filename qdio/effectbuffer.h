#ifndef EFFECTBUFFER_H
#define EFFECTBUFFER_H

#include <QObject>
#include <QIODevice>
#include <QDebug>
#include <QtMath>

class EffectBuffer : public QIODevice
{
public:
    EffectBuffer();
    qint64 readData(char* data, qint64 maxlen);
    qint64 writeData(const char* data, qint64 maxlen);


private:
    //DEBUG buffer2 is old buffer. Implemented as a circular buffer. buffer implemented using append() and chopped().
    QByteArray buffer;
    QByteArray buffer2;
    qint64 bufferUsed;
    qint64 bufferCurrent;

    qint64 validElementStart;
    qint64 validElementEnd;

    //void applyEffects(qint64 bytes);



//#define TESTMODE 1
#ifdef TESTMODE
    QByteArray testBuffer;
#endif

public slots:
    void applyEffects(qint64 bytes);
/*
signals:
    void bytesWritten(qint64 bytes);*/
};

#endif // EFFECTBUFFER_H
