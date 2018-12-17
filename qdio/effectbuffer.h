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
    QByteArray buffer;
    qint64 bufferUsed;
    qint64 bufferCurrent;

    qint64 validElementStart;
    qint64 validElementEnd;

//#define TESTMODE 1
#ifdef TESTMODE
    QByteArray testBuffer;
#endif

public slots:
};

#endif // EFFECTBUFFER_H
