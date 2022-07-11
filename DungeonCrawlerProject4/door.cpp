#include "door.h"
#include "character.h"


Door::Door(char m_doorOpened, char m_doorClosed, int m_column,int m_row)
    : Tile(m_doorClosed,m_column,m_row) ,
      doorOpened{m_doorOpened},
      doorClosed{m_doorClosed},
      doorIsOpened{false}
{
}



bool Door::operator == (const Passive& rhs) const
{
    return this->getRow() == rhs.getPassiveRow() && this->getColumn() == rhs.getPassiveColumn();
}





Tile* Door::onEnter(Tile *fromTile)
{
    if(doorIsOpened && character == nullptr)
        return this;
    else
        obstacle = true;
        return nullptr;
}



Tile* Door::onLeave(Tile *destTile)
{
//    std::string msg = destTile->getName() + std::to_string(destTile->getColumn()) + std::to_string(destTile->getRow()) + " wird betreten";
//    logger.log(logging::Logger::Level::INFO,msg);
    doorIsOpened ? currentIcon = doorOpened : currentIcon = doorClosed;
    return this;
}


void Door::notify()
{
    if(doorIsOpened)
    {
        doorIsOpened = false;
        obstacle = true;
        currentIcon = doorClosed;
    }
    else
    {
        doorIsOpened = true;
        obstacle = false;
        currentIcon = doorOpened;
    }
}



std::string Door::getName() const
{
    return name;
}



int Door::getPassiveRow() const
{
    return getRow();
}



int Door::getPassiveColumn() const
{
    return getColumn();
}



bool Door::checkIfObstacle() const
{
    return obstacle;
}
