#ifndef DOOR_H
#define DOOR_H
#include "tile.h"
#include "passive.h"

class Door : public Passive, public Tile
{
private:
    const std::string name {"Door"};
    char doorOpened;
    char doorClosed;
    bool doorIsOpened;
public:
    Door(char m_doorOpened, char m_doorClosed,  int m_column, int m_row);
    virtual bool operator == (const Passive& rhs) const override;
    void notify() override;
    Tile* onEnter(Tile *fromTile) override;
    Tile* onLeave(Tile *destTile) override;
    std::string getName() const override;
    virtual int getPassiveRow() const override;
    virtual int getPassiveColumn() const override;
    virtual bool checkIfObstacle() const override;
};

#endif // DOOR_H
