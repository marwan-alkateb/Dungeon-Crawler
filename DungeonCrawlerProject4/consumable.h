#ifndef CONSUMABLE_H
#define CONSUMABLE_H
#include <string>
#include "item.h"

class Consumable : public Item
{

protected:
    int amount;         //_amount ist die Anzahl von Fläschen

public:
    Consumable(const std::string& _name, int _amount);  //_amount ist die Anzahl von Fläschen
    virtual bool consume (Character* c) = 0;
    virtual int getAmount () const override {return amount;}
    bool isConsumeable() const override {return true;}

};

#endif // CONSUMABLE_H
