/*
 * Level ist die Karte bzw. das Spielfeld des Dungeon Crawlers.
 * Die Karte besteht im Wesentlichen aus einem dynamisch erzeugten,
 * zweidimensionalem Array aus Kacheln (bzw. Zeiger auf Kacheln)
 */

#ifndef LEVEL_H
#define LEVEL_H
#include <vector>
#include <iostream>

class Tile;
class Character;
class UserInterface;

class Level
{
private:
    int width;
    int height;
    Tile*** tiles;  // = new Tile**[width]; // initialized in the Constructor
    Level(const Level& level) = delete;
    Level() = delete;


public:
    std::vector<Character*> characters;
    Level(int m_width, int m_height, UserInterface* m_ui);
    Level(UserInterface* m_ui, const std::string&); //Constructing File Based Levels
    ~Level();
    int getHeight() const;
    int getWidth() const;

    Tile* getTile (int col, int row);
    const Tile* getTile (int col, int row) const;
    void placeCharacter (Character* c, int col , int row);
    std::vector<Character*> getCharactersVector() const;

};

#endif // LEVEL_H
