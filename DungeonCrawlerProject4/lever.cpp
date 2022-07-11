#include "lever.h"

Lever::Lever(char _lever, int _column,int _row)
    : Tile(_lever,_column, _row)
{

}



void Lever::attach (Passive* passive)
{
    passiveObjects.emplace_back(passive);
}



void Lever::detach (Passive* passive)
{
    passiveObjects.erase(std::remove_if(passiveObjects.begin(), passiveObjects.end(),
    [&] (Passive* pass) {return *passive == *pass;}));  //const std::shared_ptr<Passive>*
}



void Lever::activate ()
{
    for(auto p : passiveObjects)
    {
        p->notify();
    }
}




Tile* Lever::onEnter (Tile* fromTile)
{
    notify();
    setIcon();
    return this;
}



Tile* Lever::onLeave (Tile* destTile)
{
//    std::string msg = destTile->getName() + std::to_string(destTile->getColumn()) + std::to_string(destTile->getRow()) + " wird betreten";
//    logger.log(logging::Logger::Level::INFO,msg);
    setIcon();
    return this;
}



void Lever::notify ()
{
    activate();
}


std::string Lever::getName() const
{
    return name;
}



Lever::~Lever()
{
    //we should detach all objects in passiveObjects vector

}
