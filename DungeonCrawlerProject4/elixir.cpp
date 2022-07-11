#include "elixir.h"

Elixir::Elixir(const std::string& _name, int _amount, int _hp) : Consumable(_name,_amount), hp{_hp}
{

}



void Elixir::onEquip(Character* c)
{
        c->putInBackpack(this);
}



void Elixir::onDrop(Character* c, Tile* tile)
{
    consume(c);
}



bool Elixir::consume (Character* c)
{
        c->setStamina(+hp);
        amount--;
        if (amount == 0)
        {
            c->removeFromBackpack(this);
        }
        return true;
}


std::string Elixir::getName() const
{
    return name;
}
