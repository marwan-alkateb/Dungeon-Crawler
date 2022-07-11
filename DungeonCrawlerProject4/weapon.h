#ifndef WEAPON_H
#define WEAPON_H
#include <string>
#include "item.h"

class Weapon :public  Item  //verleiht dem Character einen Bonus auf das Attribut "Strength"
{

protected:
    int strBonus;

public:
    Weapon(const std::string& _name, int _strBonus);
    virtual void onEquip(Character* c) override;
    virtual void onDrop(Character* c, Tile* tile) override;
    int getStrBonus () const;

    virtual std::string getName() const override;
    ~Weapon(){}
};

#endif // WEAPON_H
