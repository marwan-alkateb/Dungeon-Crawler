#include "weapon.h"
#include "tile.h"

Weapon::Weapon(const std::string& _name, int _strBonus) : strBonus(_strBonus)
{
    name = _name;
}



void Weapon::onEquip(Character* c)
{
    c->putInBackpack(this);
    c->setStrength(+strBonus);
}



void Weapon::onDrop(Character* c, Tile* tile)
{
    if(tile->getName() == "Floor")
    {
        c->removeFromBackpack(this);
        tile->takeItem(this);
        c->setStrength(-strBonus);
    }
}



int Weapon::getStrBonus () const
{
    return strBonus;
}


std::string Weapon::getName() const
{
    return name;
}


