#include "portal.h"

Portal::Portal(char m_defaultIcon, int m_column, int m_row,  Tile* m_destination)
    : Tile(m_defaultIcon, m_column, m_row), destination{m_destination}
{

}



Tile* Portal::getDestination() const
{
    return destination;
}



void Portal::setDestination(Tile* t)
{
    if(destination == nullptr)
    {
        destination = t;
    }
}



Portal::~Portal()
{
    //It's essential to null the destination to avoid a circular reference between portals
    destination = nullptr;
}




Tile* Portal::onEnter(Tile *fromTile)
{
    return destination;
}



Tile* Portal::onLeave(Tile *destTile)
{
    std::string msg = destTile->getName() + std::to_string(destTile->getColumn()) + std::to_string(destTile->getRow()) + " wird betreten";
    logger.log(logging::Logger::Level::INFO,msg);
    currentIcon = defaultIcon;
    return this;
}


std::string Portal::getName() const
{
    return name;
}
