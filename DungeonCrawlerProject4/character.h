#ifndef CHARACTER_H
#define CHARACTER_H
#include "Controller.h"
#include "List.h"
#include <vector>
using namespace dllSpace;
class Item;
class Controller;
class Tile;

class Character
{
private:
    bool enemy{true};
    bool dead {false};
    const char icon;
    int strength;
    int stamina;
    int hitPoints;
    List<Item*> backPack;
    Tile* tile  {nullptr};
    Character() = delete;
    Controller* ctrl {nullptr};

    std::vector<std::string> contentNames;

public:
    Character(char _icon, int _strength, int _stamina);
    bool isDead() const;
    bool isEnemy() const;

    char move();

    char getIcon()      const;
    int getStrength()   const;
    int getStamina()    const;
    int getHitPoints()  const;
    int getColumn ()    const;
    int getRow ()       const;
    int getBackpackSize() const;
    std::string getName() const {return ctrl->getName();}
    Tile* getTile ()    const;

    void setStrength(int s)  ;
    void setStamina(int s)   ;
    void setHitPoints(int s) ;
    void setTile(Tile* m_tile);
    void setController (Controller* _ctrl);
    void setEnemy(bool x);

    std::vector<std::string>& getBackpackContent();
    void putInBackpack(Item* item);
    void dropFromBackpack(Item* item, Tile* tile);
    void dropByIndex (int i, Tile* tile);
    void removeFromBackpack(Item* item);

    ~Character();
};

#endif // CHARACTER_H
