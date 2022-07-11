#include "trap.h"


Trap::Trap(char _trapIsOn_Icon, char _trapIsOff_Icon,  int _column, int _row) :
    Tile(_trapIsOn_Icon,_column,_row), trapIsOn_Icon{_trapIsOn_Icon}, trapIsOff_Icon{_trapIsOff_Icon}
{

}


void Trap::setIcon()
{
    if (hasCharacter())
        currentIcon = character->getIcon();
    else
        trapIsOn? currentIcon = trapIsOn_Icon : currentIcon = trapIsOff_Icon;
}


void Trap::setCharacter (Character* c)
{
    character = c;
    if (trapIsOn)
    {
        character->setHitPoints(-20);
        trapIsOn = false;
    }
}


Tile* Trap::onEnter(Tile *fromTile)
{
    return character == nullptr ? this : nullptr;
}



Tile* Trap::onLeave(Tile *destTile)
{
    std::string msg = destTile->getName() + std::to_string(destTile->getColumn()) + std::to_string(destTile->getRow()) + " wird betreten";
    logger.log(logging::Logger::Level::INFO,msg);
    setIcon();
    return this;
}




std::string Trap::getName() const
{
    return name;
}
