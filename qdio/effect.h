#ifndef EFFECT_H
#define EFFECT_H

#include <QObject>

class Effect
{
public:
    Effect(bool input = false, bool output = false);

private:
    //One of the properties of Effect class is the actual mathematical transformation applied. //TODO how?
    bool input;
    bool output;

};

#endif // EFFECT_H
