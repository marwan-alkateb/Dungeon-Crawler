#ifndef ITEM_H
#define ITEM_H
#include <string>
#include "character.h"

class Item
{

protected:
    std::string name;
    char icon {'*'};
public:
    Item() {}    //Item class cannot be abstract because we need to instantiate Items in lists
    //Item(const Item&) noexcept;
    //Item(Item&& item) noexcept;
    virtual void onEquip(Character* c) = 0;
    virtual void onDrop(Character* c, Tile* tile) = 0;
    //virtual std::string getName() const;
    virtual char getIcon() const {return icon;}
    virtual std::string getName() const {return "defaultName";}
    virtual bool isConsumeable() const {return false;}
    virtual int getAmount() const {return 1;}
    virtual ~Item(){}
};

#endif // ITEM_H
