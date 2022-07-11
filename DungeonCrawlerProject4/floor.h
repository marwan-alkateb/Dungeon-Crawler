#include "tile.h"

#ifndef FLOOR_H
#define FLOOR_H


class Floor : public Tile
{
private:
    const std::string name {"Floor"};

public:
    Floor(char m_defaultIcon, int m_column, int m_row);
    virtual void setCharacter (Character* c) override;
    void grantItem (Character* c);
    virtual Tile* onEnter(Tile *fromTile) override;
    virtual Tile* onLeave(Tile *destTile) override;
    std::string getName() const override;
};

#endif // FLOOR_H
