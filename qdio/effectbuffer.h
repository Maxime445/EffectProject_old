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

    void applyEffects(qint64 bytes);

//Effects
    static void multiplyF(int x);
    static void (*multiply) (int x);
    static void maxF(int x);
    static void (*max) (int x);

//#define TESTMODE 1
#ifdef TESTMODE
    QByteArray testBuffer;
#endif

public slots:
    void bytesWritten(qint64 bytes);
};

#endif // EFFECTBUFFER_H
