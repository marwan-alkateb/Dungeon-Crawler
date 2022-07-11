#include "switch.h"


Switch::Switch(char m_switchOff,char m_switchOn, int m_column,int m_row)
    : Tile(m_switchOff,m_column, m_row) ,
      switchOn{m_switchOn} ,
      switchOff{m_switchOff} ,
      switchIsOn{false}
{
    //passiveObjects.reserve(10);
}



void Switch::attach (Passive* passive)
{
    passiveObjects.emplace_back(passive);
}



void Switch::detach (Passive* passive)
{
    passiveObjects.erase(std::remove_if(passiveObjects.begin(), passiveObjects.end(),
    [&] (Passive* pass) {return *passive == *pass;}));  //const std::shared_ptr<Passive>*
}



void Switch::activate ()
{
    switchIsOn ? switchIsOn = false : switchIsOn = true;
    for(auto p : passiveObjects)
    {
        p->notify();
    }
}




Tile* Switch::onEnter (Tile* fromTile)
{
    if ( character == nullptr)
    {
        notify();
        return this;
    }

    return nullptr;
}



Tile* Switch::onLeave (Tile* destTile)
{
    switchIsOn ? currentIcon = switchOn : currentIcon = switchOff;
    return this;
}



void Switch::notify ()
{
    activate();
}


std::string Switch::getName() const
{
    return name;
}



Switch::~Switch()
{
    //we should detach all objects in passiveObjects vector

}
