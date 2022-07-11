#include "character.h"
#include "tile.h"
#include "item.h"
#include "potion.h"
#include "elixir.h"

Character::Character(char _icon, int _strength, int _stamina) : icon{_icon}, strength{_strength}, stamina{_stamina}
{
    hitPoints = 20 + (stamina * 5);
}



char Character::getIcon() const
{
    return icon;
}


bool Character::isEnemy() const
{
    return enemy;
}



void Character::setTile(Tile* _tile)
{
    tile = _tile;                       // move to the specified tile
}



Tile* Character::getTile () const
{
    return tile;
}



int Character::getColumn () const
{
    return tile->getColumn();
}



int Character::getRow () const
{
    return tile->getRow();
}



char Character::move()
{
    return ctrl->move();
}


void Character::setController (Controller* _ctrl)
{
    ctrl = _ctrl;
}

void Character::setEnemy(bool x)
{
    enemy = x;
}


int Character::getStrength()   const
{
    return strength;
}



int Character::getStamina()    const
{
    return stamina;
}



int Character::getHitPoints()  const
{
    return hitPoints;
}



bool Character::isDead() const
{
    return dead;
}


void Character::setStrength(int s)      //s can be positive/negative
{
    strength += s;
}



void Character::setStamina(int s)       //s can be positive/negative
{
    stamina += s;
    hitPoints = 20 + (stamina * 5);
}



void Character::setHitPoints(int s)
{
    hitPoints += s;
    if (hitPoints<1)
    {
        dead = true;
    }
}


void Character::putInBackpack(Item* item)
{
    backPack.push_back(item);
}



void Character::dropFromBackpack(Item* item, Tile* tile)
{
    if (item->getName() == "Potion"  || item->getName() == "Elixir")
    {
        Consumable* i = dynamic_cast<Consumable*>(item);
        i->consume(this);
    }
    else
    {
        item->onDrop(this,tile);
    }
}



void Character::dropByIndex (int i, Tile* tile)
{
    auto itr = backPack.begin();
    while(i>1)
    {
        i--;
        itr++;
    }

    Item* item = dynamic_cast<Item*>(*itr);
    item->onDrop(this,tile);

}



void Character::removeFromBackpack(Item* item)
{
    backPack.remove(item);
}


std::vector<std::string>& Character::getBackpackContent()
{
    contentNames.clear();
        for(auto itr = backPack.begin(); itr != backPack.end(); ++itr)
        {
            Item* i = dynamic_cast<Item*>(*itr);
            contentNames.emplace_back(i->getName() += i->isConsumeable() ? " - Amount: " + std::to_string(i->getAmount()):"");
        }
        return contentNames;
}


int Character::getBackpackSize() const
{
    return backPack.size();
}



Character::~Character()
{
//    for(auto itr = backPack.begin(); itr != backPack.end(); ++itr)
//    {
//        delete *itr;
//        backPack.erase(itr);
//    }

    if(tile != nullptr) tile = nullptr;
    if(ctrl != nullptr) delete ctrl; ctrl = nullptr;
}

