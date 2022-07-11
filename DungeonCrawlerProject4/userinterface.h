/*
 * UserInterface ist die Benutzerschnittstelle.
 * Hier wird zunächst die Ausgabe als ncurses Interface implementiert.
 * Die Eingabe kann momentan noch in Character implementiert werden.
 * Ziel des Praktikums ist es, die gesamte Ein- und Ausgabe in dieser Klasse zu haben,
 * um eine klare Trennung zwischen dem eigentlichen Spiel und der Benutzerinteraktion zu erreichen.
 */

#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include "ncurses.h"
#include "Controller.h"
#include <iostream>
#include <string>
#include <vector>

class Level;
class Tile;
class Character;

class UserInterface //: public Controller
{
private:
    constexpr static char   character     = '@';
    constexpr static char   wall          = '#';
    constexpr static char   floor         = ' ';
    constexpr static char   portal        = 'O';
    constexpr static char   switch_on     = '!';
    constexpr static char   switch_off    = '?';
    constexpr static char   door_opened   = '/';
    constexpr static char   door_closed   = 'X';
    constexpr static char   lever         = 'L';
    constexpr static char   trap          = 'T';

    constexpr static int    menuColumn  {30};
    constexpr static int    boardColumn {1};
    constexpr static int    boardRow    {1};


public:
    char getCharacter() const;
    char getWall() const;
    char getFloor() const;
    char getPortal() const;
    char getSwitchOn() const;
    char getSwitchOff() const;
    char getDoorOpened() const;
    char getDoorClosed() const;
    char getLever()     const;
    char getTrap()      const;
    //virtual int move() override;

    UserInterface();
    virtual ~UserInterface();
    void draw (Level*);
    void drawPlayerAttributes (Character* activeCharacter);
    void drawPlayersAttributes (std::vector<Character*>& v);
    void drawPlayerMenu ();
    void drawPlayerInventory (Character* activeCharacter);
    void gameOver();

};

#endif // USERINTERFACE_H
