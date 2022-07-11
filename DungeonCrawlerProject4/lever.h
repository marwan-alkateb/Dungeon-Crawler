#ifndef LEVER_H
#define LEVER_H
#include "tile.h"
#include "active.h"
#include "character.h"

class Lever : public Active, public Tile
{
private:
    const std::string name {"Lever"};

public:
    Lever(char _lever, int _column, int _row);
    virtual void attach (Passive* passive) override;
    virtual void detach (Passive* passive)override;
    virtual void notify () override;
    virtual void activate() override;

    virtual Tile* onLeave (Tile* destTile) override;
    virtual Tile* onEnter (Tile* fromTile) override;


    virtual std::string getName() const override;

    virtual ~Lever();
};

#endif // LEVER_H
