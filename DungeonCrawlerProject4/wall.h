#include "tile.h"

#ifndef WALL_H
#define WALL_H


class Wall : public Tile
{
private:
    const std::string name {"Wall"};
    Tile* onLeave (Tile*) override;

public:
    Wall(char m_defaultIcon,  int m_column,int m_row);
    Tile* onEnter(Tile*) override;
    std::string getName() const;
    bool checkIfObstacle() const override;
};

#endif // WALL_H
