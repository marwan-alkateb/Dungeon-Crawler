#include "tile.h"
#include "character.h"



Tile::Tile(char _defaultIcon,  int _column, int _row) :
      defaultIcon{_defaultIcon} ,
      currentIcon{_defaultIcon},
      column{_column},
      row{_row}
{

}



int Tile::getRow() const
{
    return row;
}



int Tile::getColumn() const
{
    return column;
}



bool Tile::operator == (const Tile& rhs) const
{
    return this->getRow() == rhs.getRow() && this->getColumn() == rhs.getColumn();
}



char Tile::getIcon() const
{
    return currentIcon;
}



bool Tile::hasCharacter() const
{
    return !(character == nullptr);
}



void Tile::setIcon()
{
    if (hasCharacter())
        currentIcon = character->getIcon();
    else if (item != nullptr)
        currentIcon = item->getIcon();
    else
        currentIcon = defaultIcon;
}



void Tile::setCharacter (Character* c)
{
    character = c;
}



bool Tile::moveTo (Tile* destTile)
{
    Tile* dest = destTile->onEnter(this);

        if(dest == nullptr){
           return false;
        }

        dest->setCharacter(character);
        dest->setIcon();
        character->setTile(dest);
        dest = nullptr;
        character = nullptr;
        onLeave(this);

    return true;
}



bool Tile::initializeCharacter (Character* c)
{
        character = c;
        c->setTile(this);
        setIcon();
        return true;
}



void Tile::setDestination (Tile* t)
{

}



std::string Tile::getName() const
{
    return "Default";
}



void Tile::takeItem(Item* _item)
{
    item = _item;
    setIcon();
}



bool Tile::checkIfObstacle() const
{
    return false;
}



int Tile::getPlayerHP() const
{
    if(character != nullptr)
    {
        return character->getHitPoints();
    }
    return 0;
}



Tile::~Tile()
{
    if(item != nullptr)
    {
        delete item;
    }
}
