#ifndef ATTACKCONTROLLER_H
#define ATTACKCONTROLLER_H
#include "Controller.h"
#include <string>
#include "astaralgorithm.h"
#include "character.h"
#include "level.h"
#include "tile.h"
#include "asa.h"

using namespace asa;

class AttackController : public Controller
{
private:
    Level* level;
    Character* player;
public:
    AttackController(Level* l, Character* c);
    std::list<Point> findPath(std::vector<std::vector<char>>& v, int start_x, int start_y, int end_x, int end_y);
    virtual int move() override;
    std::string getName() const override;
};

#endif // ATTACKCONTROLLER_H
