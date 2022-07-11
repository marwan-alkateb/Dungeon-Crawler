#ifndef PASSIVE_H
#define PASSIVE_H


class Passive
{
public:
    //notify soll aufgerufen werden ,wenn für dieses Passive-Objekt eine Aktion ausgelöst werden soll
    virtual void notify() = 0;
    virtual bool operator == (const Passive& rhs) const = 0;
    virtual int getPassiveRow() const = 0;
    virtual int getPassiveColumn() const = 0;
    virtual ~Passive(){}
};

#endif // PASSIVE_H
