#include "tile.h"
#ifndef PORTAL_H
#define PORTAL_H


class Portal : public Tile
{
private:
    Tile* destination {nullptr};        //speichert das Zielportal
    std::string name {"Portal"};
public:

    Portal(char m_defaultIcon,  int m_column, int m_row,Tile* m_destination);
    ~Portal();
    Tile* getDestination() const;
    void setDestination(Tile* t) override;
    virtual Tile* onEnter(Tile *fromTile) override;
    virtual Tile* onLeave(Tile *destTile) override;
    std::string getName() const override;
};

#endif // PORTAL_H
