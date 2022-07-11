#include "armor.h"
#include "tile.h"

Armor::Armor(const std::string& _name, int _staBonus) : staBonus{_staBonus}
{
    name = _name;
}

void Armor::onEquip(Character* c)
{
    c->putInBackpack(this);
    c->setStamina(+staBonus);
}



void Armor::onDrop(Character* c, Tile* tile)
{
    if(tile->getName() == "Floor")
    {
        c->removeFromBackpack(this);
        tile->takeItem(this);
        c->setStamina(-staBonus);
    }
}



int Armor::getStaBonus () const
{
    return staBonus;
}


std::string Armor::getName() const
{
    return name;
}
