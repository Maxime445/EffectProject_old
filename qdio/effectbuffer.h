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

    const char* readPointer;
    int readPointerElement;

    int validElementStart;
    int validElementEnd;
    int validLoop; // 1 if validStart comes after validEnd because of loop.

    char* writePointer;
    int writePointerElement;

//#define TESTMODE 1
#ifdef TESTMODE
    QByteArray testBuffer;
#endif

public slots:
};

#endif // EFFECTBUFFER_H
