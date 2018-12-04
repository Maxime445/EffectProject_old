#ifndef EFFECTBUFFER_H
#define EFFECTBUFFER_H

#include <QObject>
#include <QIODevice>

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
    char* writePointer;


public slots:
};

#endif // EFFECTBUFFER_H
