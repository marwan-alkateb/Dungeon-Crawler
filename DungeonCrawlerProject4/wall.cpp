#include "wall.h"

Wall::Wall(char m_defaultIcon,  int m_column,int m_row)
    : Tile(m_defaultIcon,m_column,m_row)
{

}



Tile* Wall::onEnter(Tile*)
{
    return nullptr;
}



std::string Wall::getName() const
{
    return name;
}



Tile* Wall::onLeave (Tile*)
{
    throw std::runtime_error("onLeave Function is not supported for class Wall!");
    return nullptr;
}


bool Wall::checkIfObstacle() const
{
    return true;
}
