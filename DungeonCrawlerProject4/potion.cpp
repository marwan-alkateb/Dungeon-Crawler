#include "potion.h"

Potion::Potion(const std::string& _name, int _amount, int _hp) : Consumable(_name,_amount), hp{_hp}
{

}



void Potion::onEquip(Character* c)
{
        c->putInBackpack(this);
}



void Potion::onDrop(Character* c, Tile* tile)
{
    consume(c);
}



bool Potion::consume (Character* c)
{
        c->setStamina(+hp);
        amount--;
        if (amount == 0)
        {
            c->removeFromBackpack(this);
        }
        return true;
}

std::string Potion::getName() const
{
    return name;
}
