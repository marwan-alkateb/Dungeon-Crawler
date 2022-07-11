/*
 * Tile stellt eine Kachel dar, also ein Feld der Spielwelt.
 * Aktuell gibt es nur drei verschiedene Typen von Kacheln:
 * „Boden“, „Wand“ und „Portal“.
 */

#ifndef TILE_H
#define TILE_H
#include <iostream>
#include <algorithm>
#include <memory>
#include <string>
#include "ncurses.h"
#include "logger.h"
#include "List.h"
#include "item.h"
using namespace dllSpace;
using namespace std;

class Character;


class Tile
{
protected:
    bool obstacle;
    Item* item {nullptr};
    logging::Logger& logger = logging::Logger::Get("foo.txt");
    char defaultIcon ,currentIcon;
    const int  column, row;
    Tile* destination;


public:
    Character* character {nullptr};
    Tile(char _defaultIcon, int _column, int _row);
    virtual ~Tile();
    virtual bool operator == (const Tile& rhs) const;
    virtual void setDestination(Tile* t);
    virtual int getRow() const;
    virtual int getColumn() const;
    virtual char getIcon() const;
    virtual std::string getName() const;

    virtual void takeItem(Item*);
    //virtual void removeItem(Item*);

    virtual void setIcon();
    virtual bool hasCharacter() const;
    virtual bool moveTo (Tile* destTile);
    virtual Tile* onEnter (Tile* fromTile) = 0;
    virtual Tile* onLeave (Tile* destTile) = 0;
    virtual void setCharacter (Character* c);
    virtual bool initializeCharacter(Character* c);
    virtual bool checkIfObstacle() const;
    virtual int getPlayerHP()const;
};

#endif // TILE_H
