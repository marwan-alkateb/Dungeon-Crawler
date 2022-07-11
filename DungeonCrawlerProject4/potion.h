#ifndef POTION_H
#define POTION_H
#include "consumable.h"

class Potion : public Consumable
{
private:
    int hp;
public:
    Potion(const std::string& _name, int _amount, int _hp);
    virtual void onEquip(Character* c) override;
    virtual void onDrop(Character* c, Tile* tile) override;
    virtual bool consume (Character* c) override;
    virtual std::string getName() const override;
};

#endif // POTION_H
