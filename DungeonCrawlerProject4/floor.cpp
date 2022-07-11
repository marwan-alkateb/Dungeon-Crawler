#include "floor.h"

Floor::Floor(char _defaultIcon, int _column,int _row)
    : Tile(_defaultIcon,_column,_row)
{

}



Tile* Floor::onEnter(Tile *fromTile)
{
    // New Tile is empty
    if(character == nullptr)
        return this;
    // Clash between friend and enemy
    else if(character->isEnemy() != fromTile->character->isEnemy())
    {
        character->setHitPoints(- fromTile->getPlayerHP());
        if(character->isDead()){
            character->setTile(nullptr);
            character = nullptr;
            return this;
        }
        return nullptr;
    }
    // For the case: enemy/enemy or Friend/Friend
    return nullptr;
}



Tile* Floor::onLeave(Tile *destTile)
{
    setIcon();
    return this;
}



void Floor::setCharacter (Character* c)
{
    character = c;
    if (item != nullptr)
        grantItem(c);
}



void Floor::grantItem (Character* c)
{
    item->onEquip(c);
    setIcon();
    item = nullptr;
}



std::string Floor::getName() const
{
    return name;
}
