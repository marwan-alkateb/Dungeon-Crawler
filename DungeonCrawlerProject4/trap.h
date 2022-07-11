#ifndef TRAP_H
#define TRAP_H
#include "tile.h"

class Trap : public Tile
{
private:
    const std::string name {"Trap"};
    char trapIsOn_Icon;
    char trapIsOff_Icon;
    bool trapIsOn{true};
public:
    Trap(char _trapIsOn_Icon, char _trapIsOff_Icon,  int _column, int _row);
    Tile* onEnter(Tile *fromTile) override;
    Tile* onLeave(Tile *destTile) override;
    std::string getName() const override;
    void setIcon() override;
    void setCharacter (Character* c) override;
};

#endif // TRAP_H
