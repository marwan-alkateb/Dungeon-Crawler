#ifndef SWITCH_H
#define SWITCH_H

#include "tile.h"
#include "active.h"
#include "character.h"
// #include "door.h"

class Switch : public Active , public Tile
{
private:
    const std::string name {"Switch"};
    const char switchOn;
    const char switchOff;
    bool switchIsOn;

public:
    Switch(char m_switchOff,char m_switchOn, int m_column, int m_row);

    virtual void attach (Passive* passive) override;
    virtual void detach (Passive* passive)override;
    virtual void notify () override;
    virtual void activate() override;

    virtual Tile* onLeave (Tile* destTile) override;
    virtual Tile* onEnter (Tile* fromTile) override;


    virtual std::string getName() const override;
    virtual ~Switch();
};

#endif // SWITCH_H
