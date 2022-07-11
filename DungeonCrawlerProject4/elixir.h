#ifndef ELIXIR_H
#define ELIXIR_H
#include "consumable.h"

class Elixir : public Consumable
{
protected:
    int hp;
public:
    Elixir(const std::string& name,int amount , int hp);
    virtual void onEquip(Character* c) override;
    virtual void onDrop(Character* c, Tile* tile) override;
    virtual bool consume (Character* c) override;
    virtual std::string getName() const override;
};

#endif // ELIXIR_H
