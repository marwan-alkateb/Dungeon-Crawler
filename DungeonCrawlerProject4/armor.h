#ifndef ARMOR_H
#define ARMOR_H
#include "item.h"



class Armor : public Item   //verleiht dem Character einen Bonus auf das Attribut "Stamina"
{
private:
    const int staBonus;
public:
    Armor() = delete;
    Armor(const std::string& _name, int _staBonus);
    virtual void onEquip(Character* c) override;
    virtual void onDrop(Character* c, Tile* tile) override;
    int getStaBonus () const;
    virtual std::string getName() const override;
};

#endif // ARMOR_H
